/**
 * This is a test of malloc() and free().
 * It is proved that whatever the type of the pointer acquired from malloc()
 * you cast to, when you invoke free(), all the memory block would be recycled.
 * although you can access the memory after free(), and the values stored here 
 * are not changed, it illegal.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _struct1 {
    int num1;
    int num2;
    char num3[];
} struct1;

int main() {
    struct1* s1 = malloc(sizeof(struct1) + 5);
    s1->num1 = 10;
    s1->num2 = 20;
    char* tmp = "hello";
    memcpy((char*)(s1 + 1), tmp, 4);

    printf("s1->num3[2]: %c\n", s1->num3[2]);
    printf("addr of      s1: %p\n", s1);
    printf("addr of    num1: %p\n", &s1->num1);
    printf("addr of    num3: %p\n", &s1->num3);
    printf("addr of num3[2]: %p\n", &s1->num3[2]);

    //keep the pointer, then free memory 
    char * p_num32 = &s1->num3[2];
    free(s1);

    //you can access it, but that's illegal
    printf("s1->num3[2] after free accessed by pointer: %c\n", *p_num32);
    printf("s1->num3[2] after free accessed by    name: %c\n", s1->num3[2]); 
    
    //remalloc memory to test if the memory just freed available 
    struct1* s2 = malloc(sizeof(struct1) + 5);
    s1->num1 = 10;
    s1->num2 = 20;
    char* tmp1 = "uvwxy";
    memcpy((char*)(s2 + 1), tmp, 4);
    
    printf("see if the addr of s2 is the same with s1");
    printf("addr of      s2: %p\n", s2);
    printf("addr of    num1: %p\n", &s2->num1);
    printf("addr of    num3: %p\n", &s2->num3);
    printf("addr of num3[2]: %p\n", &s2->num3[2]);

    return 0;
}
