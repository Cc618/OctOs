# OctOs
An OS created in October. This OS is 32 bits, provides a heap and a command line interface.

## Build
Here is makefile commands. To build :
```bash
$ make
```
To build and run :
```bash
$ make run
```
To remove temporary files :
```bash
$ make flush
```
To clean everything (removes all build files) :
```bash
$ make clean
```

## Depedencies
To build the OS you must have :
- nasm : Assembly sources
- cc (for i386, provided with GCC) : For C sources
- ld (for i386, provided with GCC) : To link object files

If the compilation fails, please make sure that you have a cross compiler (for i386).
Here is some [documentation](https://wiki.osdev.org/GCC_Cross-Compiler "Build a cross compiler") about how to build a cross compiler. 
