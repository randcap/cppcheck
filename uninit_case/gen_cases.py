import os

def write_file(filename, content):
    with open(filename, 'w') as f:
        f.write(content)

def generate_structure(depth, current_depth, is_positive):
    indent = "    " * current_depth
    if current_depth >= depth:
        if is_positive:
            return f"{indent}x = 1; // Assignment at depth {depth}\n"
        else:
            return f"{indent}if (val == 999) x = 1; // Conditional assignment at depth {depth}\n"
    
    structure_type = current_depth % 3
    content = ""
    
    if structure_type == 0: # if
        content += f"{indent}if (val > {current_depth}) {{\n"
        content += generate_structure(depth, current_depth + 1, is_positive)
        content += f"{indent}}}\n"
    elif structure_type == 1: # for
        content += f"{indent}for (int i{current_depth} = 0; i{current_depth} < 5; ++i{current_depth}) {{\n"
        content += generate_structure(depth, current_depth + 1, is_positive)
        content += f"{indent}}}\n"
    else: # while
        content += f"{indent}while (val < {100 + current_depth}) {{\n"
        content += f"{indent}    val++;\n"
        content += generate_structure(depth, current_depth + 1, is_positive)
        content += f"{indent}}}\n"
        
    return content

def generate_case(filename, depth, is_positive):
    content = f"// {'Positive' if is_positive else 'Negative'} Case: Depth {depth}\n"
    content += "int test_func(int val) {\n"
    
    if is_positive:
        content += "    int x = 0; // Initialized at declaration\n"
    else:
        content += "    int x; // Not initialized at declaration\n"
        
    content += generate_structure(depth, 1, is_positive)
    
    content += "    return x;\n"
    content += "}\n"
    
    write_file(filename, content)

depths = [2, 10, 30, 60, 100]

# Positive cases (1-5)
for i, d in enumerate(depths):
    generate_case(f"test_case_{i+1}.cpp", d, True)

# Negative cases (6-10)
for i, d in enumerate(depths):
    generate_case(f"test_case_{i+6}.cpp", d, False)

print("Generated 10 test cases.")
