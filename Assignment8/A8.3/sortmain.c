#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "int_element.h"
#include "str_element.h"
#include "element.h"

/* If the string is numeric, return an int_element. Otherwise return a str_element. */
struct element *parse_string(char *str) {
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(str, &endp, 10);
  if(str[0] != '\0' && endp[0] == '\0') {
    /* String was non-empty and strtol conversion succeeded - integer */
    return (struct element *)int_element_new(value);
  } else {
    return (struct element *)str_element_new(str);
  }
}

int compare_elements(const void *elem1, const void *elem2) {
  struct element *el = *(struct element **)elem1;
  struct element *e2 = *(struct element **)elem2;
  if (is_int_element(el) && is_int_element(e2))  {
    if (int_element_get_value(el) < int_element_get_value(e2)) {
      return -1;
    } else if (int_element_get_value(el) == int_element_get_value(e2)) {
      return 0;
    } else {
      return 1;
    }
  } else if (is_str_element(el) && is_str_element(e2)) {
    // char *s1 = str_element_get_value(el);
    // char *s2 = str_element_get_value(e2);
  
    // while (*s1 && (*s1 == *s2)) {
    //   s1++;
    //   s2++;
    // }
    // return (*s1 - *s2);
    struct str_element *se1 = (struct str_element *)el;
    struct str_element *se2 = (struct str_element *)e2;
    return strcmp(str_element_get_value(se1), str_element_get_value(se2));
  } else {
    if (is_int_element(el) && is_str_element(e2))  {
      return -1;
      } else {
        return 1;
      }
  }
}

int main(int argc, char **argv) {
  struct element * elements[argc-1];
  for (int i= 0; i < argc-1; i++) {
    elements[i] = parse_string(argv[i+1]);
  }
  /* TODO: Sort elements with qsort */
  qsort(elements, argc-1, sizeof(struct element *), compare_elements);
  
  printf("Sorted: ");
  for (int i = 0; i < argc -1; i++) {
    if (is_int_element(elements[i])) {
      struct int_element *int_el = (struct int_element *)elements[i];
      printf("%d ", int_element_get_value(int_el));
    } else {
    struct str_element *str_el = (struct str_element *)elements[i];
    printf("%s ", str_element_get_value(str_el));
    }
  }
  printf("\n"); 

  for (int i = 0; i < argc - 1; i++) {
    rc_free_ref(elements[i]);
}

  return 0;
  
}
