# How to use ccc

## Running the compiler & assembler

You can use ccc to compile G files and assembly language files at the same time. Files in the form of *name.g* are assumed to be G files and files in the form of *name.s* are assumed to be assembly language files.

> Note: The outputed file from ccc is a binary file which can only be run through an emulator.

To compile or assemble a file:

<span>&nbsp;&nbsp;&nbsp;&nbsp;ccc </span><i>compile-options</i><span> file.s -o file.bin</span>

<span>&nbsp;&nbsp;&nbsp;&nbsp;ccc </span><i>compile-options</i><span> file.g -o file.bin</span>

## Options

-o *file-name*

<span>&nbsp;&nbsp;&nbsp;&nbsp;Send output to </span><i>file-name</i><span> instead of default <i>a.out</i>.</span>

-O1

<span>&nbsp;&nbsp;&nbsp;&nbsp;Optimization level 1 (default).</span>

-O2

<span>&nbsp;&nbsp;&nbsp;&nbsp;Optimization level 2, shrinks instruction operand sizes.</span>

-Werror

<span>&nbsp;&nbsp;&nbsp;&nbsp;Treat all warnings as errors.</span>

-Wall

<span>&nbsp;&nbsp;&nbsp;&nbsp;Shows warnings for things that are legal but dubious.</span>

