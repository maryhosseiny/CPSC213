#include <stdlib.h>
#include <stdio.h>

// YOU: Allocate these global variables, using these names
int  z, q;
int* s;
int  w[10];

int main (int argv, char** argc) {
  // Ignore this block of code
  if (argv != 11) {
    fprintf (stderr, "usage: w[0] ... w[9]\n");
    exit (EXIT_FAILURE);
  }
  for (int n=0; n<10; n++)
    w[n] = atol (argc[1 + n]);

  // YOU: Implement this code
  z  = w[8];
  z  = w[z];
  s  = &q;
  *s = 4;
  s  = &w[w[3]];
  *s = *s + w[7];

  // Ignore this block of code
  printf ("z=%d q=%d s=&w[%d] w={", z, q, s - w);
  for (int n=0; n<10; n++)
    printf("%d%s", w[n], n<9? ", ": "}\n");
  }