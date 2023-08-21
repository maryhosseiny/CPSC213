#include "str_element.h"
#include "refcount.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct str_element {
  struct str_element_class* class;
  char* value;
};

void str_print(struct element *print_element);
int str_compare(struct element *compare_element1, struct element *compare_element2);
int is_str_element(struct element *element);
char* str_element_get_value(struct str_element *element);
struct str_element *str_element_new(char* element);

struct str_element_class {
void (*print) (struct element*);
int (*compare) (struct element*, struct element*);
int (*is_str_element) (struct element*);
char* (*str_element_get_value) (struct str_element*);
struct str_element* (*str_element_new) (char*);
};

struct str_element_class str_element_class = {
  str_print,
  str_compare,
  is_str_element,
  str_element_get_value,
  str_element_new
}; 

void str_print(struct element *print_element) {
  struct str_element* init_elem = (struct str_element *) print_element;
  printf("%s", init_elem->value); 
} 
int str_compare(struct element *compare_element1, struct element *compare_element2) {
   struct str_element* init_elem0 = (struct str_element* ) compare_element1; 
   if (is_str_element(compare_element2)) { 
      struct str_element* init_elem1 = (struct str_element*) compare_element2; 
      return strcmp(init_elem0->value,init_elem1->value); 
    } else { 
      return 1; 
    } 
} 
  
int is_str_element(struct element *element) { 
  return (((struct str_element*)element)->class == &str_element_class);
} 

char* str_element_get_value(struct str_element *element) { 
  return element->value; 
} 
  
void str_finalizer(void* element_finalizer) { 
  struct str_element* init_element = (struct str_element*) element_finalizer; 
  free(init_element->value); 
} 
    
struct str_element *str_element_new(char* element) { 
  struct str_element *init_element = rc_malloc(sizeof(struct str_element), str_finalizer); 
  init_element->class = &str_element_class; 
  init_element->value = strdup(element); 
  return init_element; 
}