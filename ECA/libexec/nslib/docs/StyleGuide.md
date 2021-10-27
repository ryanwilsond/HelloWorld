# Style Guide

Code styles and naming convenctions for nslib. (Mostly just a personal reference to stay consistent.)
Only for this part of the project because it will end up being the most robust section, because there is a possibility I will use this in other projects.

## Naming Conventions

```cpp
// in general, things that start with underscore are not used by the user

class my_class {};      // class names are snake_case
class _My_class {};     // privatly used classes (only used behind the scenes) are underscore started Upper_snake_case
struct my_struct {};    // struct names are snake_case
int my_function();      // public methods & functions are snake_case
int _Private_method();  // private methods & internal methods (see formatting for more info) are underscore started Upper_snake_case
int _Getterfunc();      // getter and setter type methods are underscore started singleword names (start with uppercase)
int mymacro();          // macro-esc functions are singleword lowercase
template<_Ty> int f();  // template names are underscore started Upper_snake_case, and commonly just called _Ty, _T, or _Tp (_Elem is also common)

using _Alty = <...>     // special types used with templating are often underscore started abbreviations (start with uppercase); this is an example with _Alty meaning allocator type

int _MY_INT;            // private class variables are underscore started SCREAMING_SNAKE_CASE
int _My_var;            // function variables are underscore started Upper_snake_case
using my_type = int;    // typenames are snake_case

#define MY_CONST 1;     // preprocess constants are SCREAMING_SNAKE_CASE
#define _STD std::      // preprocess abstraction constants are underscore started SCREAMING_SNAKE_CASE
#ifndef _MYFILE_        // #ifndef locks on files are underscore surrounded uppercase filenames
#include <mylib>        // headers are snake_case (common single word) surrounded in angle-brackets (<>)
```

## Formatting

Code samples that highlight *most* the formatting.

```cpp
#define _STD std::
#define _STD_BEGIN namespace std {
#define _STD_END }

_STD_BEGIN

// empty class declarations are back-to-back
template<_Elem>
    class _My_traits
    {
    };
template<_Elem>
    class allocator
    {
    };

template<_Elem>
    class _Inherit_class
    {
public: // could be protected but usally not
    using size_t = unsigned long long int;

    };

template<_Elem, // newline for each template argument
    class _Traits = _My_traits<_Elem>,
    class _Alloc = allocator<_Elem>>
    class class_name // indented
        : public _Inherit_class<_Elem> // inheritance on seperate line, indented
    {
private:
    using _Alty = _Alloc;
    using _Mybase = _Inherit_class<_Elem>;

    using size_type = typename _Mybase::size_t;
// space between seperate types of things (types and members)

    size_type _MY_SIZE;

public: // newline after private or public if the first thing there is a function

// constructors and assigners

    class_name() noexcept // all constructors and assigners are noexcecpt (thats it, only things that actually matter if noexcept)
        : _Mybase()
        { // "docstrings" go on opening bracket
        }

    void operator=(const class_name& _Right) noexcept // use & references to assure that it is const
        {
        this->_Construct_self(_Right); // generally try to redirect all operators to named functions
        }

// internal methods (public methods that are only used by this class and not by the user)

    void _Construct_self(const class_name& _Right)
        {
        this->_MY_SIZE = _Right._Mysize(); // has to be public so this can access, but user never calls _Mysize()
        }

    size_type _Mysize() const // everthing const if possible
        {
        return this->_MY_SIZE;
        }

// public methods (methods the user calls)

    size_type size() const
        {
        return this->_Mysize(); // only use reference to actual private member when setting
        }

    };

_STD_END
```
