# Design Principles

C-style syntax, based on C++ and C#

Design Principle: Logical vs Physical: Abstract hardware and implementation details from code e.g. integer size

- Pointer: Use reference abstraction and safety like C#
- Imports: Combine C# project using and C includes to allow either complex projects or simple files
- Null: Null != 0, Null = Null; Null values cant be copied from because they have no value; No default empty constructors
- No redundant concepts i.e. array vs vector vs linked list, struct vs class, etc. Combine these to have the compiler figure out which is best not the user
- No integer limits by storing back to back (much harder to do this with floats)
