import os, subprocess, sys
import shutil as sh 

#paths
root_path = os.path.abspath(os.curdir)
dest_path = root_path + "/build"

#calling make compile
command = subprocess.run(['make', 'compile'], capture_output=True)
sys.stdout.buffer.write(command.stdout)
sys.stderr.buffer.write(command.stderr)

#moving object files to build dir
for dirpath, dnames, fnames in os.walk(root_path):  
    for f in fnames:
        if f.endswith(".o"):
            #print(f)
            source_file_path =  os.path.join(dirpath, f)
            dest_path_path   =  os.path.join(dest_path, f)
            sh.move(source_file_path, dest_path_path)
            print("[OBJ] => ", f)


print("Compiling.....")
command = subprocess.run(['make', 'build'], capture_output=True)
sys.stdout.buffer.write(command.stdout)
sys.stderr.buffer.write(command.stderr)