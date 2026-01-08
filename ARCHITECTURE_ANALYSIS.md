# CheckUninitVar 模块架构分析

## 1. 模块概述

**CheckUninitVar** 是 cppcheck 中用于检查**未初始化变量使用**的检查器模块。

主要职责：
- 检测在代码中使用未初始化的变量
- 支持普通变量、指针、数组、结构体成员的检查
- 支持跨函数的 CTU (Cross-Translation Unit) 分析

---

## 2. 架构分层结构

```
┌─────────────────────────────────────────────┐
│         Entry Points (公共接口)              │
├─────────────────────────────────────────────┤
│ • runChecks()          [静态入口]           │
│ • getFileInfo()        [跨文件信息提取]    │
│ • analyseWholeProgram() [全程序分析]       │
└─────────────────────────────────────────────┘
           ↓
┌─────────────────────────────────────────────┐
│       主检查方法 (Main Check Methods)        │
├─────────────────────────────────────────────┤
│ • check()              [基础检查]           │
│ • valueFlowUninit()    [值流检查]           │
└─────────────────────────────────────────────┘
           ↓
┌─────────────────────────────────────────────┐
│     作用域和结构体检查 (Scope Analysis)      │
├─────────────────────────────────────────────┤
│ • checkScope()         [遍历作用域]        │
│ • checkStruct()        [结构体成员检查]    │
└─────────────────────────────────────────────┘
           ↓
┌─────────────────────────────────────────────┐
│   变量使用检查 (Variable Usage Analysis)     │
├─────────────────────────────────────────────┤
│ • checkScopeForVariable() [核心递归检查]    │
│ • checkIfForWhileHead()   [条件语句检查]   │
│ • checkLoopBody()         [循环体检查]      │
│ • checkLoopBodyRecursive() [递归循环检查]   │
│ • checkRhs()              [赋值右侧检查]    │
│ • checkExpr()             [表达式检查]      │
└─────────────────────────────────────────────┘
           ↓
┌─────────────────────────────────────────────┐
│    判定方法 (Decision Methods)               │
├─────────────────────────────────────────────┤
│ • isVariableUsage()       [变量使用判定]    │
│ • isFunctionParUsage()    [函数参数判定]    │
│ • isMemberVariableAssignment()   [成员赋值] │
│ • isMemberVariableUsage() [成员使用]        │
│ • isVariableUsed()        [变量是否被用]    │
└─────────────────────────────────────────────┘
           ↓
┌─────────────────────────────────────────────┐
│      错误报告 (Error Reporting)              │
├─────────────────────────────────────────────┤
│ • uninitvarError()          [变量未初始化]   │
│ • uninitdataError()         [数据未初始化]   │
│ • uninitStructMemberError() [成员未初始化]   │
└─────────────────────────────────────────────┘
```

---

## 3. 核心调用流程

### 3.1 主检查流程

```
runChecks()
│
├─→ valueFlowUninit()      [新的值流分析方法]
│   ├─→ getExprUsage()     [判断表达式如何被使用]
│   └─→ uninitvarError()   [报告错误]
│
└─→ check()                [传统AST遍历方法]
    ├─→ checkScope()       [遍历所有可执行作用域]
    │   └─→ checkScopeForVariable()  [针对每个变量的核心检查]
    │       ├─→ checkIfForWhileHead()
    │       ├─→ checkLoopBody()
    │       │   └─→ checkLoopBodyRecursive()
    │       │       ├─→ isVariableUsage()
    │       │       └─→ isMemberVariableUsage()
    │       ├─→ checkRhs()
    │       │   └─→ isVariableUsage()
    │       └─→ checkExpr()
    │
    └─→ checkStruct()      [检查未初始化的结构体]
        └─→ checkScopeForVariable()
```

### 3.2 变量使用判定流程

```
isVariableUsage(Token*, bool pointer, Alloc alloc)
│
├─→ 获取AST父节点信息
├─→ 判断是否需要解引用
├─→ 检查安全的操作（强制转换、void转换等）
├─→ 判断是否被当作函数参数使用
│   └─→ isFunctionParUsage()
│       └─→ 获取参数信息
│       └─→ 检查库函数信息
├─→ 判断是否在赋值表达式左侧
└─→ 返回使用的Token或nullptr
```

---

## 4. 关键数据结构

### 4.1 Alloc 枚举
```cpp
enum Alloc {
    NO_ALLOC,       // 非指针或普通变量
    NO_CTOR_CALL,   // 分配但无构造函数
    CTOR_CALL,      // 有构造函数的分配
    ARRAY           // 数组类型
};
```

### 4.2 VariableValue 结构
```cpp
struct VariableValue {
    MathLib::bigint value;  // 已知的值
    bool notEqual{};        // 是否是不等于关系
};
```
用于条件分析时跟踪变量的已知值。

### 4.3 MyFileInfo 类
```cpp
class MyFileInfo : public Check::FileInfo {
    std::list<CTU::FileInfo::UnsafeUsage> unsafeUsage;
};
```
用于跨文件检查时的信息保存。

---

## 5. 主要函数详解

### 5.1 check() - 主检查方法
```
职责：遍历所有可执行作用域，逐个检查变量
返回：void

流程：
1. 获取符号数据库（Symbol Database）
2. 收集数组类型定义
3. 对每个可执行作用域调用 checkScope()
```

### 5.2 checkScope(scope, arrayTypeDefs) - 作用域检查
```
职责：检查一个作用域内的所有变量
参数：
  - scope: 要检查的作用域
  - arrayTypeDefs: 数组类型定义集合

流程：
1. 遍历作用域中的所有变量
2. 过滤掉：静态变量、外部变量、引用、特殊类型
3. 对初始化变量检查右侧：checkRhs()
4. 对数组变量检查：checkScopeForVariable()
5. 对结构体变量检查：checkStruct()
```

### 5.3 checkScopeForVariable() - 核心递归检查
```
职责：跟踪变量在作用域中的使用情况
参数：
  - tok: 起始token
  - var: 要检查的变量
  - possibleInit: 输出参数，是否可能初始化
  - noreturn: 输出参数，是否无返回
  - alloc: 分配类型
  - membervar: 成员变量名（如果检查成员）
  - variableValue: 已知变量值映射

核心逻辑：
1. 处理作用域结束 (}) → 检查是否无返回
2. 处理内层作用域 ({) → 递归调用
3. 跟踪其他变量值 (x = value) → 用于条件分析
4. 处理条件语句 (if/else) → 分支分析
5. 处理循环 (for/while/do) → 循环体检查
6. 处理变量使用 → 报告错误或标记初始化
```

### 5.4 checkLoopBody() / checkLoopBodyRecursive() - 循环检查
```
checkLoopBody()
  └─→ checkLoopBodyRecursive()
      ├─→ 处理嵌套循环
      ├─→ 检测 switch 分支
      ├─→ 追踪变量赋值
      ├─→ 检测条件使用
      └─→ 处理 return 语句
```

### 5.5 isVariableUsage() - 使用判定（关键方法）
```
职责：判断变量在某个位置是否被"使用"（而不是初始化）

返回值：
  - nullptr：变量未被使用（安全）
  - Token*：使用的token位置（不安全）

检查项：
1. 解引用情况 (*ptr, ptr[], ptr.member)
2. 强制转换 ((type)var)
3. 函数参数传递
4. 赋值左侧
5. 流读写 (>> <<)
6. 条件判断
7. 返回语句
```

### 5.6 isFunctionParUsage() - 函数参数判定
```
职责：判断当前函数调用如何使用参数

返回值：
  -1: 未知
   0: 未使用（通过引用安全传递）
   1: 已使用（值传递，报告错误）

检查项：
1. 获取被调用函数定义
2. 获取对应参数的类型
3. 检查参数是否为指针/引用
4. 查询库函数信息（library.isuninitargbad）
```

### 5.7 valueFlowUninit() - 值流分析
```
职责：基于值流分析的未初始化变量检查（更精确）

流程：
1. 获取符号数据库
2. 两次迭代（当前函数 + 子函数）
3. 对每个token：
   ├─→ 跳过unevaluated上下文（sizeof等）
   ├─→ 查找未初始化值标记
   ├─→ 检查该值是否来自当前函数或子函数
   ├─→ 检查表达式使用方式
   └─→ 报告错误

特点：
- 使用值流信息（ValueFlow::Value）
- 支持间接引用追踪
- 支持子表达式检查
```

---

## 6. 条件分析与状态追踪

### 6.1 条件值分析
```cpp
conditionAlwaysTrueOrFalse(Token*, variableValue, &alwaysTrue, &alwaysFalse)
```
- 分析条件是否总是真/假
- 用于消除不可到达的代码路径
- 支持：常量、变量、比较、逻辑运算

### 6.2 状态变量追踪
```cpp
std::map<nonneg int, VariableValue> variableValue
```
- 维护已知变量值的映射
- 在分支时进行复制
- 用于精确的条件判定

---

## 7. 错误报告机制

```
未初始化变量检测
   ↓
根据类型分类报告：
├─→ uninitvarError()          // 普通变量：legacyUninitvar / uninitvar
├─→ uninitdataError()         // 未初始化数据：uninitdata
└─→ uninitStructMemberError() // 结构体成员：uninitStructMember
```

---

## 8. 跨文件检查 (CTU)

```
getFileInfo()
  └─→ CTU::getUnsafeUsage()
      └─→ 提取不安全的函数参数使用

loadFileInfoFromXml()
  └─→ 从XML恢复跨文件信息

analyseWholeProgram()
  ├─→ 构建调用图 (callsMap)
  ├─→ 追踪参数流动
  └─→ 报告CTU未初始化错误 (ctuuninitvar)
```

---

## 9. 关键算法特性

### 9.1 分支敏感分析
- 为每个分支维护独立的变量状态
- 处理条件初始化：`if (x) y = 1;`
- 追踪 noreturn 函数影响

### 9.2 循环处理
- 识别循环内的初始化
- 处理条件循环
- 区分确定和不确定的初始化

### 9.3 结构体成员检查
- 无构造函数的结构体成员追踪
- 初始化列表识别
- 成员变量赋值检测

### 9.4 指针和数组
- 区分指针和数组
- 追踪解引用级别（indirect）
- 处理动态分配（malloc/new）

---

## 10. 性能优化

```
// 避免重复报告
std::unordered_set<nonneg int> ids
  └─→ 记录已报告的表达式ID

// 诊断日志
bool diag(Token* tok)
  └─→ 防止相同位置重复报告
```

---

## 总结

CheckUninitVar 是一个**两层次的未初始化变量检查系统**：

1. **传统AST遍历法** (`check()`)
   - 从变量声明开始追踪
   - 精确控制流分析
   - 支持复杂的分支和循环

2. **值流分析法** (`valueFlowUninit()`)
   - 基于计算出的值流信息
   - 支持过程间分析
   - 捕捉复杂的初始化模式

两种方法互补，提供全面的未初始化变量检测。
