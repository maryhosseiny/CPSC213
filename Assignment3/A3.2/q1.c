#include <stdlib.h>
#include <stdio.h>

// YOU: Allocate these global variables, using these names
int  n, w;
int* d;
int  l[10];

int main (int argv, char** argc) {
  // Ignore this block of code
  if (argv != 11) {
    fprintf (stderr, "usage: l[0] ... l[9]\n");
    exit (EXIT_FAILURE);
  }
  for (int h=0; h<10; h++)
    l[h] = atol (argc[1 + h]);

  // YOU: Implement this code
  n  = l[9];
  n  = l[n];
  d  = &w;
  *d = 8;
  d  = &l[l[6]];
  *d = *d + l[4];

  // Ignore this block of code
  printf ("n=%d w=%d d=&l[%d] l={", n, w, d - l);
  for (int h=0; h<10; h++)
    printf("%d%s", l[h], h<9? ", ": "}\n");
  }
