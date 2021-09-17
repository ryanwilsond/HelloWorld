# Hurdles All the Way Down

Hello world in a simple language built in my custom OS (programming in custom assembly and language) for my custom emulated CPU.

Also made a robust C++ library for fileio, strings, and vectors

> Note: This is made for Windows only

___

## Precompiled Binaries

The actualy executable you want to run is *main.exe* in *bin/*.

For the custom assembler and compiler run *ccc.exe* in *ccc/bin/*.

The ccc installer is *ccc_setup.exe* in *ccc/install*.

## Compiling Yourself

First run `$ make dirs` to create the neccessary folders for the build process. Then run `$ make` and it should create *main.exe* in *bin/*.

To compile ccc first run `$ cd ccc`. Then `$ make dirs` again to create the neccessary folders. Then run `$ make` and it should create *ccc.exe* in *bin/* (inside *ccc/*).

To compile the installer, use Inno to compile *install.iss* (in *ccc/install*).
