# Chip-8

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

# Build
run ``` python3.7 build.py OS``` to build the emulator,
```OS``` can be WINDOWS|LINUX|RS90 -> ``` python3.7 build.py WINDOWS```
it can also build to linux or the rs90,
executables will be moved to the folder
with the Makefile name,
Dlls at the moment need to be moved manualy
ex: you will use the Makefile.win -> \Makefile.win\main.exe

# Todo
cleaning up some code related to graphics,
and other bugfixes

# Misc

build.py function is to move .o files from /src to /bin, 
call linker and them move the executable to a especific folder  


