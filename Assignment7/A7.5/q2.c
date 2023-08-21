#include <stdio.h>

int x[8] = {1,2,3,-1,-2,0,184,340057058};
int y[8];

int f(int arg) {
  int temp = 0;

  while (arg != 0) {
    if ((arg & -2147483648) != 0) {
      temp++;
    }
    arg = arg * 2;
  }
  return temp;
}
int main() {
  for (int i = 7; i >= 0; i--) {
    y[i] = f(x[i]);
  }
  
  for (int i = 0; i < 8; i++) {
    printf("%i\n", x[i]);
  }

  for (int i = 0; i < 8; i++) {
    printf("%i\n", y[i]);
  }
}