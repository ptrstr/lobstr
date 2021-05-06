# lobstr
Cross platform minimal and fast hooking library with useful extensions

## Dependencies
This project depends on [capstone](https://www.capstone-engine.org/). Make sure you have correctly [installed](https://www.capstone-engine.org/documentation.html) it and that the required header and library are available for your compiler.

## Building
1. Get the source
    - `git clone https://github.com/ptrstr/lobstr`
2. Configure project
    - `cd lobstr/build`
    - `cmake ..`
3. Build
    - Linux
        - `make`
        - `sudo make install`

            Use this option to install the library
    - Windows
        
        You will need to build the `dll` with Visual Studio with the provided `.sln` file

## Using
This project was made to be as easy as possible to use. Here is an example:
```c
#include <lobstr/lobstr.h>
#include <stdio.h>

void integerPrinter(int value) {
  printf("Printing integer: %d\n", value);
}

void (*originalIntegerPrinter)(int);
void hookedIntegerPrinter(int value) {
  printf("Custom printing integer: ~~%d~~\n", value);
  // Modfication of `value` and callback
  value = 1337;
  originalIntegerPrinter(value);
}

int main(int argc, char *argv[]) {
  originalIntegerPrinter = &integerPrinter;
  
  // Returns 1 on error
  if (allocHook((void *)hookedIntegerPrinter, (void **)&originalIntegerPrinter))
    return 1;
   
  integerPrinter(55);
  
  return 0;
}
```

Output:
```
Custom printing integer: ~~55~~
Your modified? integer: 1337
```
