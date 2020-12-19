#include <iostream>

extern "C" int sayHello(void);

using namespace std;

int main(int argc, char **argv)
{
  // Calls the routine from the linked assembly function
  sayHello();
 
  return 0;
}
