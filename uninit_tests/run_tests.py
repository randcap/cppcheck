import os
import subprocess
import sys

def run_tests():
    # Configuration
    cppcheck_exe = r"..\cppcheck.exe" # Assuming cppcheck.exe is in the parent directory
    test_dir = "."
    
    # Check if cppcheck executable exists
    if not os.path.exists(os.path.join(test_dir, cppcheck_exe)) and not os.path.exists(cppcheck_exe):
        print(f"Error: cppcheck executable not found at {cppcheck_exe}")
        # Try to find it in current path or typical build locations if needed
        # But for now, rely on relative path
        return

    # Get all .cpp files in the directory
    files = [f for f in os.listdir(test_dir) if f.endswith(".cpp") and f.startswith("case")]
    files.sort(key=lambda x: int(x.replace("case", "").replace(".cpp", "")))

    output_file = "results.txt"
    with open(output_file, "w") as f_out:
        msg = f"Found {len(files)} test cases.\n" + "-" * 60
        print(msg)
        f_out.write(msg + "\n")

        for filename in files:
            msg_header = f"Testing {filename}..."
            print(msg_header)
            f_out.write(msg_header + "\n")
            
            filepath = os.path.join(test_dir, filename)
            
            # Construct command
            # You can adjust flags here. 
            # For example, to enable all checks: ["--enable=all", "--inconclusive"]
            # To test specific uninit var behavior, you might just use default or specific flags.
            cmd = [cppcheck_exe, "--enable=warning,style", filepath]
            
            try:
                # Run cppcheck
                result = subprocess.run(cmd, capture_output=True, text=True)
                
                if result.returncode != 0:
                    err_msg = f"Cppcheck failed to run on {filename}\n{result.stderr}"
                    print(err_msg)
                    f_out.write(err_msg + "\n")
                else:
                    # Print the output (stderr usually contains the defects found)
                    output = result.stderr.strip()
                    if output:
                        print(output)
                        f_out.write(output + "\n")
                    else:
                        print("No issues found.")
                        f_out.write("No issues found.\n")
            except Exception as e:
                err_msg = f"Failed to execute: {e}"
                print(err_msg)
                f_out.write(err_msg + "\n")
            
            sep = "-" * 60
            print(sep)
            f_out.write(sep + "\n")
            
    print(f"Results saved to {output_file}")

if __name__ == "__main__":
    run_tests()
