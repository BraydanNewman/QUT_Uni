#include <stdlib.h>

void *f();

int main(int argc, char *argv[]) {
    f();
    return 0;
}

void * f() {
      void *p = malloc(100); // allocate 100 bytes 
      p = malloc(200); // allocate 200 bytes
      return p;
}