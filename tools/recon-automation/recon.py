import subprocess 


# Info Gathering/Defining Variables
target = input("Give me the IP address of the target")
scan = input("What type of scan do u want? \
1 = fast scan (scan first 100 ports + version + service \
2 = full scan (all ports + threading + version + service" )

# Main command execution funcition
def run_command(cmd):
    result = subprocess.run(
        cmd,
        capture_output=True,
        text=True,
        timeout=30

    )
        
    return {
        "stdout": result.stdout,
        "stderr": result.stderr,
        "return_code": result.returncode
    }

# Defining Scan type 
def fast_scan(target):
    cmd = ["nmap", "-sS", "-sV", "-sC", "-T5", "-F", target]
    
    result = run_command(cmd)
    
    print("== Fast Scan Result ==")
    print(result["stdout"])

    return result


def full_scan(target):
    cmd = ["nmap", "-sS", "-sV", "-sC", "-T5", "-p-", target]

    result = run_command(cmd)

    print("== Full Scan Result ==")
    print(result["stdout"])

    return result

# Scanning

if scan == "1":
    fast_scan(target)

elif scan == "2":
    full_scan(target)

else:
    print("Invalid option")

