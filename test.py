import subprocess
import os
myenv = os.environ.copy()

def run_performance_test(n):
    for i in range(n):
        proc = subprocess.Popen(['/bin/bash'], stdin=subprocess.PIPE,stdout=subprocess.PIPE)
        result = proc.communicate('ls')
    return result

print(run_performance_test(1))