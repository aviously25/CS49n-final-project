import os
import sys
from subprocess import Popen, PIPE, STDOUT

p = Popen([sys.executable, "-u", "hello.py"], stdout=PIPE, stderr=STDOUT, bufsize=1)

with p.stdout:
	for line in iter(p.stdout.readline, b''):
		print(line,)
		os.system("echo -e \"\a\"")
p.wait()
