# Lab 7: The C Preprocessor

## Using Text Replacement (with Macros)

A good c++ programmer will minimize use of macros. However, it is still important to understand how they work, because you will see them fairly frequently in c++ programs. 
### Example 1: Basic Program

Run the simple pre.cpp file

```
int main(){
    return 8;
}
```

with the make command

```
g++ pre.cpp -o pre
```

Now, verify the output is as expected, using:

```
./pre
echo $?
> 8
```

### Example 2: Basic Definition

Change pre.cpp to

```
int main(){
    return DEFN;
}
```

and adjust the make command accordingly

```
g++ -DDEFN=4 pre.cpp -o pre
```

Again, verify the output using:

```
./pre
echo $?
> 4
```

The same functionality could have also been achieved without modifying the make command, by adding the following statement to the top of pre.cpp

```
#define DEFN 4
```

## Using Compiler Directives

### Example 3: Line Numbers

If you add a line number redefinition and a error-inducing line immediately below it in pre.cpp

```
#define DEFN 6

#line 12345
var
int main(){
    return DEFN
}
```

you'll see that compiling with

```
g++ pre.cpp
```

yields an error on line 12345.

### Example 4: Hard-Coded Errors

Replacing the error-inducing line in Example 3 with

```
#error "This is an error"
```

yields the error

```
error: #error "This is an error"
```

when compiled.

## Using Text Replacement (from File)

### Example 5

Replace the program in pre.cpp with

```
#include "stdio.h"

int main(){
    return 0;
}
```

Compiling the program and piping the output with

```
cpp pre.cpp 1> pre.out
```

allows us to view all of the text that c++ adds to the source code in pre.out.

## Using Conditionals

### Example 6: If Statement

You can add an if-statement to pre.cpp, as follows:

```
#include "stdio.h"

#if DEFN == 1
int f(){
    garbage
}
#endif

int main(){
    return 0;
}
```

Compiling this code with

```
g++ pre.cpp
```

will not generate any errors since DEFN does not equal 1. However, compiling with

```
g++ pre.cpp -DDEFN=1
```

will generate an error at line 3.

### Example 7: Include

If we add a file f.cpp

```
int f(){
    return 4;
}
```

and include it in pre.cpp

```
#include "f.cpp"

int main(){
    return 0;
}
```

it will include the code from f.cpp in the compiled source. We can confirm this with

```
g++ pre.cpp -E
```

It follows, then, that including f.cpp twice

```
#include "f.cpp"
#include "f.cpp"

int main(){
    return 0;
}
```

will cause a re-definition error for f() upon compile.

### Example 8: Ifndef

Let's add a #define statement to f.cpp

```
#define F_IS_DEFINED

int f(){
    return 4;
}
```

and an #ifndef statement to pre.cpp

```
#include "f.cpp"

#ifndef F_IS_DEFINED
#include "f.cpp"
#endif

int main(){
    return 0;
}
```

This will **not** cause an error upon compiling. If we change f.cpp to

```
#ifndef F_IS_DEFINED
#define F_IS_DEFINED

int f(){
    return 4;
}

#endif
```

we can include f.cpp in pre.cpp as many times as we want

```
#include "f.cpp"
#include "f.cpp"
#include "f.cpp"
#include "f.cpp"
#include "f.cpp"
#include "f.cpp"

int main(){
    return 0;
}
```

but it will only include f.cpp once.

It's important to use #ifndef when programming a codebase with multiple files as two files in a single repository might include the same file.

## Using Parametrized Macros

Using parametrized macros is highly discouraged because it has the potential to make code very convoluted and confusing.

### Example 9: Adder Function

Add the macro function ADDER to pre.cpp

```
#define ADDER(a,b) a+b

int main(){
    return ADDER(1,2);
}
```

and compile it using

```
g++ pre.cpp -E
```

and see that the preprocessor generates

```
int main(){
    return 1 + 2;
}
```

for the main() function above.

### Example 10: Glue Function

Add the macro function ADDER to pre.cpp

```
#include <iostream>

#define GLUE(a,b) std::a##b

int main(){
    GLUE(c,out) << "Hello";
}
```

Compiling and running the program will, in fact, print "Hello".

## Using Macros

### Example 11: \_\_LINE\_\_

This program in pre.cpp

```
#include <iostream>

#define GLUE(a,b) std::a##b

void report(int line){
    std::cout << "Error at line " << line << std::endl;
}

int main(){
    report(__LINE__);
}
```

will print

```
Error at line 10
```

when it is compiled and run. 

### Example 12: \_\_FILE\_\_

This program in pre.cpp

```
#include <iostream>

#define GLUE(a,b) std::a##b

void report(int line){
    std::cout << "Error at line " << line << std::endl;
}

int main(){
    report(__LINE__);
    std::cout << "Error in file " << __FILE__ << std::endl;
}
```

will print

```
Error at line 10
Error in file pre.cpp
```

when it is compiled and run. 

### Example 13: \_\_func\_\_

This program in pre.cpp

```
#include <iostream>

#define GLUE(a,b) std::a##b

void report(int line){
    std::cout << "Error at line " << line << std::endl;
}

int main(){
    report(__LINE__);
    std::cout << "Error in file " << __FILE__ << std::endl;
    std::cout << "Error in func " << __func__ << std::endl;
}
```

will print

```
Error at line 10
Error in file pre.cpp
Error in func main
```

when it is compiled and run.