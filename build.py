import os, subprocess, sys
import shutil as sh 
from os.path import exists

#paths
root_path = os.path.abspath(os.curdir)
build_path = root_path + "/build"
bin_path = root_path + "/bin"
#name_exec = "main"
#name_make = "Makefile.rs90"
name_exec = "main.exe"
name_make = "Makefile.win"

#calling make compile
command = subprocess.run(['make', '-f', name_make, 'compile'], capture_output=True)
sys.stdout.buffer.write(command.stdout)
sys.stderr.buffer.write(command.stderr)

#moving object files to build dir
for dirpath, dnames, fnames in os.walk(root_path):  
    for f in fnames:
        if f.endswith(".o"):
            #print(f)
            source_file_path =  os.path.join(dirpath, f)
            dest_path_path   =  os.path.join(bin_path, f)
            sh.move(source_file_path, dest_path_path)
            print("[OBJ] => ", f)


print("Compiling.....")
command = subprocess.run(['make', '-f', name_make, 'build'], capture_output=True)
sys.stdout.buffer.write(command.stdout)
sys.stderr.buffer.write(command.stderr)

#command = subprocess.run(['make', '-f', name_make, 'opk'], capture_output=True)
#sys.stdout.buffer.write(command.stdout)
#sys.stderr.buffer.write(command.stderr)

#move executable to build and dlls 
if exists(build_path + "/" + name_exec):
    os.remove(build_path + "/" + name_exec)
sh.move(name_exec, build_path)