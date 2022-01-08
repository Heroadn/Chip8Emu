# Chip-8

Dont forget to unpack befored running the emu,
also in the windows release there's a py.run,
its a gui for choosing the rom to be run
without all cmd, but you can run main.exe using the command line,
see Cmd section for avaliable commands

# Cmd
```
Usage:
    -w Width of the screen
    -h Height of the screen
    -p Bits per pixel(opt)
    -r Path to the ROM
    -f Frames per second(opt)
    -c Color of pixels(opt)
    -b Color of the background(opt)
```

# Keyboard - WINDOWS
0   1	2	3
4	5	6	7	
8	9   A   B
C   D   E   F

# Build
run ``` python3.7 build.py WINDOWS|LINUX|RS90``` to build the emulator,
-> ``` python3.7 build.py WINDOWS```
executables will be moved to the folder with the Makefile name
ex: 
WINDOWS uses Makefile.win -> \Makefile.win\main.exe

# Todo
clean up some code related to graphics,
more documentation, bugfixes, debugger gui, and a
configurable keyboard layout, for now they are hardcoded

# Misc

build.py function is to move .o files from /src to /bin, 
call linker and them move the executable to a especific folder  


