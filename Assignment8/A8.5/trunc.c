#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list.h"
#include "list.c"

void Print (element_t ev) {
    char* e = (char*) ev;
    printf("%s\n", e);

}

void StringToNum(element_t* rv, element_t av){
    char* a = (char*) av;
    intptr_t* r = (intptr_t*) rv;
    char* p;

    *r = strtol(a, &p, 10);

    if (p == a)
        *r = -1;

}

void ProduceNull(element_t* rv, element_t av, element_t bv){
    char** r = (char**) rv;
    char* a = (char*) av;
    intptr_t b = (intptr_t) bv;

    if (b < 0)
         *r = a;
    else 
        *r = NULL;
}

int RemoveNegativeValues(element_t av){
    intptr_t a = (intptr_t) av;

    if (a >= 0)
        return 1;
    else    
        return 0;
}

int RemoveNullValues(element_t av){
    char* a = (char*) av;

    if (a != NULL)
        return 1;
    else 
        return 0;
}

void TruncateValues(element_t* rv, element_t av, element_t bv){
    char ** r = (char**) rv;
    char* a = (char*) av;
    intptr_t* b = (intptr_t*) bv;

    if (strlen(a) <= *b) {
         *r = a;
    return;
    } 
    a[(int)*b] = 0;
        *r = a;
}

void PrintMaxValue(element_t* rv, element_t av, element_t bv){
    intptr_t* r = (intptr_t*) rv;
    intptr_t a = (intptr_t) av;
    intptr_t b = (intptr_t) bv;

    if (a > b)
        *r = a;
    else
        *r = b;
}

int main(int argc, char *argv[]) {
    
    struct list* list = list_create();
    
    for(int i = 1; i < argc; i++){
        list_append (list, (element_t) argv[i]);
    }
    struct list* listOfNum = list_create ();
    list_map1 (StringToNum, listOfNum, list);
        
    struct list* listWithNull = list_create();
    list_map2 (ProduceNull, listWithNull, list, listOfNum);
    
    struct list* listPositive = list_create();
    list_filter (RemoveNegativeValues, listPositive, listOfNum);

    struct list* listNoNull = list_create();
    list_filter (RemoveNullValues, listNoNull, listWithNull);

    struct list* listTruncated = list_create();
    list_map2 (TruncateValues, listTruncated, listNoNull, listPositive);
    
    list_foreach (Print, listTruncated);

    element_t maxValue = 0;
    list_foldl (PrintMaxValue, (element_t*)&maxValue, listOfNum);
    
    printf("%d\n", maxValue);
    
    list_destroy (list);
    list_destroy (listOfNum);
    list_destroy (listWithNull);
    list_destroy (listPositive);
    list_destroy (listNoNull);
    list_destroy (listTruncated);
}

