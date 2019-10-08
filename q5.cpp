#include <iostream>
#define MYSTERY( x ) #x

int main () {
   int a = 1;
   int b = 2;
   int c = 3;
   std::cout << MYSTERY(a+b*c) << std::endl;

   return 0;
}