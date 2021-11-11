# Hurdles All the Way Down

Goal of the project is to make a hello world program in my custom programming langauage G. It will compile with a custom compiler that runs on an operating system I will make. This operating system will be compiled and assembled to run on my custom emulated CPU.

OS source files are in 'WorldOS/src'.

CPU source files are in 'src'.

ECA (ecc compiler and assembler) are in 'ECA/src'.

Also for a learning expierence I am using only my custom string and vector classes. These headers are in 'ECA/libexec/nslib'.

> Note: This is made for Windows only

___

For all documentation:

- CPU docs: 'docs/'
- OS docs: 'WorldOS/docs'
- ECA docs: 'ECA/docs'

For developer doc info read [README-dev.md](README-dev.md).

___

## Precompiled Binaries

All precompiled binaries are in 'bin/release'.

## Building

First run `$ make dirs` to create the neccessary folders for the build process. Then run `$ make` and it should create 'main.exe' in 'bin/'.

## Running

Support for specifiying a file to treat as disk will be added.

For bash: `$ ./bin/main.exe`

> Note: Only tested with bash MinGW64, using command prompt may not work properly

For cmd: `> bin/main.exe`
