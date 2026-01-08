import sys
import difflib
import os

def compare_files(file1_path, file2_path):
    if not os.path.exists(file1_path):
        print(f"Error: File '{file1_path}' not found.")
        return
    if not os.path.exists(file2_path):
        print(f"Error: File '{file2_path}' not found.")
        return

    print(f"Comparing '{file1_path}' and '{file2_path}'...")
    print("-" * 60)

    with open(file1_path, 'r', encoding='utf-8') as f1, open(file2_path, 'r', encoding='utf-8') as f2:
        f1_lines = f1.readlines()
        f2_lines = f2.readlines()

    diff = difflib.unified_diff(
        f1_lines, 
        f2_lines, 
        fromfile=file1_path, 
        tofile=file2_path,
        lineterm=''
    )

    diff_list = list(diff)
    
    if not diff_list:
        print("Files are identical.")
    else:
        for line in diff_list:
            # Colorize output for better readability in terminal
            if line.startswith('+'):
                print(f"\033[92m{line}\033[0m") # Green for additions
            elif line.startswith('-'):
                print(f"\033[91m{line}\033[0m") # Red for deletions
            elif line.startswith('^'):
                print(f"\033[94m{line}\033[0m") # Blue for control lines
            else:
                print(line)

if __name__ == "__main__":
    # Default files if no arguments provided
    file1 = "results_check.txt"
    file2 = "results_valueflowuninit.txt"

    if len(sys.argv) == 3:
        file1 = sys.argv[1]
        file2 = sys.argv[2]
    elif len(sys.argv) != 1:
        print("Usage: python compare_results.py [file1] [file2]")
        print(f"Defaulting to comparing '{file1}' and '{file2}'")

    compare_files(file1, file2)
