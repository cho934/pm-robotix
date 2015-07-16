# Coding Standards #

This document is based on Coding Standards of Wesnoth http://www.wesnoth.org/wiki/CodingStandards. Some references to Wesnoth could be found.

## Formatting ##

Indent with a tab character (width 4 characters), but align with spaces so tab width can change.

You may use long lines.

[indent](UtilIndent.md) do all for you so use it and "don't panic".

## Naming ##

### Class, method and others standard elements ###

All elements must use names write with [A-Za-z0-9] characters.

Classes must start with a capital letter, other elements must start with a small letter.

### End Non-Public Members of Classes with an Underscore ###

All non-public data members of classes should have their names terminated with an underscore, to show that they are a class member. This makes for more readable code, once one is familiar with the convention.

## Idioms ##

### Use References when a value may not be NULL ###

If a value passed to a function can never be NULL, use a reference instead of a pointer. I.e.

```cpp

void myFunction(Object& obj);
```

rather than

```
void myFunction(Object* obj);
```

This more clearly shows the user of the function that obj may never be NULL, without them having to consult documentation or the implementation of the function.

### Use Const ###
The 'const' feature of C++ allows interfaces to more clearly specify how they treat objects. Always use const when you are not going to modify an object.

I.e.

```
void myFunction(const Object& obj);
```

demonstrates to the caller of myfunction() that obj will not be modified. If myfunction may modify obj, then use

```
void myFunction(Object& obj);
```

likewise, if a variable is not changed after initialization, make it const.

### Write Exception-Safe Code ###
Wesnoth code should be exception-safe, even if you do not use exceptions directly. That is, you should be able to assume that an exception is thrown almost anywhere from within the code, with well-defined results (i.e. no resource leaks).

Code that uses a pattern like,

```
 {
 Surface* image = imageLoad("image.bmp");
 ...some code, which uses 'image'...
 freeSurface(image);
 }
```

is bad, because the code may throw an exception, and 'image' will never be freed. Instead, use wrapper objects which free the object in their destructor.

For SDL\_Surface objects, use the surface class. So you could rewrite the above code,

```
 {
 Surface image(imageLoad("image.bmp"));
 ...some code, which uses 'image'...
 }
```
> the image is automatically freed here when 'image' is destroyed
Instead of allocating memory directly using new[.md](.md) or malloc(), use language-provided containers, such as vector.

### Do not use sprintf ###
Sprintf does not check whether or not it is writing past the end of the space allocated. This is a security problem if someone other than the person running the game can cause sprintf to write very long strings. In Wesnoth this untrusted data could come potentially from other players in a multiplayer game or from downloaded campaigns. Instead you should use snprintf with the second argument being sizeof of the buffer that will hold the result.

## Standard C++ to avoid ##
### Respect for loop scoping of different platforms ###
In the code,

```
 for(int i = 0; i != 100; ++i) {...}
```
the variable 'i' is scoped within the for loop according to ISO/ANSI C++ and GNU G++. However it is scoped within the surrounding scope according to Visual C++ 6.

This means that the code,

```
 for(int i = 0; i != 100; ++i) {}
 for(int i = 0; i != 100; ++i) {}
```
is illegal on VC++6, because i is defined twice, although it is legal according to the standard, and GNU G++.

On VC++6, the legal way to write it would be,

```
 for(int i = 0; i != 100; ++i) {}
 for(i = 0; i != 100; ++i) {}
```
But this is illegal according to the standard, because 'i' is not defined in the second loop. The correct way to write this code to conform to the standard and work on all platforms is to simply abandon declaring variables in the initialization statement of a for loop when the variable must be reused in the same scope,

```
 int i;
 for(i = 0; i != 100; ++i) {}
 for(i = 0; i != 100; ++i) {}
```

### Do not use wstring ###
The standard C++ wstring class, defined as a basic\_string< wchar\_t >, does not exist in some platforms supported by Wesnoth. Use wide\_string, defined in language.hpp, instead. wide\_string is actually defined as a vector< wchar\_t >

## C legacy to be avoided ##

### Use util::array instead of C-style Arrays ###
C-style arrays are very efficient, but their interface is ugly. Use util::array defined in array.hpp. It is a wrapper for an array which has a C++ container-style interface. If you need to, extend it to make it fit your needs.

> A coder ?

### Do not use C-style casts ###
The following code,

```
 if(i->second.side() == (size_t)player_number_) {
```
is considered bad practice in C++ since a C-style cast is overpowered -- if types change around it could end up casting away constness, or performing an implementation-defined data reinterpretation (basically a C-style cast is a compiler generated combination of static\_cast, reinterpret\_cast, and const\_cast).

Good programming style is to use the least powerful tool available that does what you want. For example,

```
 if(i->second.side() == static_cast<size_t>(player_number_)) {
```
Alternatively, a constructor call may be used for non-builtin types.

Note: there may be some obscure cases where a C-style cast is desirable, such as converting a pointer to an integer type of unspecified size.

## Documentation ##

> A compléter