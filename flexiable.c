/**
 * This file is a test of flexiable array
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct struct1 {
    int num1;
    char num2;
    char num3[];
} struct1;

typedef struct struct2 {
    int num1;
    int num2;
    char num3[];
} struct2;

int main () {
    struct1* s1 = malloc(sizeof(struct1) + 4*sizeof(char));
    struct2* s2 = malloc(sizeof(struct2) + 4*sizeof(char));
    s1->num1 = 10;
    s1->num2 = 'z';
    s2->num1 = 10;
    s2->num2 = 333;
    char* tmp = "word";
    
    memcpy((char*)(s1 + 1), tmp, 4);
    memcpy((char*)(s2 + 1), tmp, 4);

    printf("sizeof char: %d\n",(int)sizeof(char));
    printf("sizeof int:  %d\n",(int)sizeof(int));

    printf("sizeof struct1: %d\n",(int)sizeof(struct1));
    printf("sizeof struct2: %d\n",(int)sizeof(struct2));

    printf("\n");
    printf("for struct1\n");
    printf("                  num1             num2    num3\n");
    printf("                  -------------------------------------\n");
    printf("                  |     4Byte      |2Byte  |2Byte  |...\n");
    printf("                  -------------------------------------\n");
    printf("                  |<-----------struct1------------>|\n");
    printf("   num1: %d\n", s1->num1);
    printf("   num2: %c\n", s1->num2);
    printf("num3[0]: %c\n", s1->num3[0]);
    printf("num3[1]: %c\n", s1->num3[1]);
    printf("num3[2]: %c\n", s1->num3[2]);
    printf("num3[3]: %c\n", s1->num3[3]);

    printf("addr of s1          %p\n", s1);
    printf("addr of s1->num1    %p\n", &s1->num1);
    printf("addr of s1->num2    %p\n", &s1->num2);
    printf("addr of s1->num3    %p\n", &s1->num3);
    printf("addr of s1->num3[0] %p\n", &s1->num3[0]);
    printf("addr of s1->num3[1] %p\n", &s1->num3[1]);
    printf("addr of s1->num3[2] %p\n", &s1->num3[2]);
    printf("addr of s1->num3[3] %p\n", &s1->num3[3]);

    printf("\n");
    printf("for struct2\n");
    printf("                  num1             num2            num3\n");
    printf("                  -------------------------------------\n");
    printf("                  |     4Byte      |     4Byte     |...\n");
    printf("                  -------------------------------------\n");
    printf("                  |<-----------struct2------------>|\n");
    printf("   num1: %d\n", s2->num1);
    printf("   num2: %d\n", s2->num2);
    printf("num3[0]: %c\n", s2->num3[0]);
    printf("num3[1]: %c\n", s2->num3[1]);
    printf("num3[2]: %c\n", s2->num3[2]);
    printf("num3[3]: %c\n", s2->num3[3]);

    printf("addr of s2          %p\n", s2);
    printf("addr of s2->num1    %p\n", &s2->num1);
    printf("addr of s2->num2    %p\n", &s2->num2);
    printf("addr of s2->num3    %p\n", &s2->num3);
    printf("addr of s2->num3[0] %p\n", &s2->num3[0]);
    printf("addr of s2->num3[1] %p\n", &s2->num3[1]);
    printf("addr of s2->num3[2] %p\n", &s2->num3[2]);
    printf("addr of s2->num3[3] %p\n", &s2->num3[3]);
    return 0;
}
