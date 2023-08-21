#include <stdio.h>

int arr[10] = {0,0,0,0,0,0,0,0,0,0};

void adding(int x, int y) {
  arr[y] = arr[x] + x;
}

int main() {
  adding(3,4);
  adding(1,2);

  for (int i = 0; i < 10; i++) {
    printf("%i\n", arr[i]);
  }
  
}