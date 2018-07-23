#include<stdio.h>
int fun1();
int fun2();
int fun3();
int main(){
    if(fun1() || fun2()){
	printf("fun1() || fun2()\n");
    }
    if(fun3() || fun2()){
	printf("fun3() || fun2()\n");
    }
    if(fun1() && fun2()){
	printf("fun1() && fun2()\n");
    }
    if(fun3() && fun2()){
	printf("fun3() && fun2()\n");
    }
    return 0;
}
int fun1(){
    printf("in fun1\n");
    return 1;
}
int fun2(){
    printf("in fun2\n");
    return 1;
}
int fun3(){
    printf("in fun3\n");
    return 0;
}
/* Output:
 * in fun1
 * fun1() || fun2()
 * in fun3
 * in fun2
 * fun3() || fun2()
 * in fun1
 * in fun2
 * fun1() && fun2()
 * in fun3
 */
