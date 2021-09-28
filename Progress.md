# Progress & Issues

> ECA/test/command-line shows command-line examples

## Features

- 9/28: Added --help argument to ccc
        Added pop() method to vector
        Added join() method to string

## Issues

- 9/22 (Solved): Segfault and error with fileio and custom string class
    Probably due to allocation issues
    Issues was that there was no copy constructor for my string class, meaning by default it would just copy the address of a c string.
    **Solution**: Added copy constructor for (const string &)

- 9/28 (Solved): Exit of program when appending a string to a vector
    Only an issue because the string was passed into file::ReadAllText()
    **Solution**: string operator+=(string) incorrectly allocted memory, switched to using malloc
