#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static int data = 0;

void change(){
    data = 1;
}

int main(){
    // bool x = 1;
    // printf("%d\n",x);

    // for(int i=3; i<2; i++){
    //     i = 10;
    // }

    printf("%d ",data);
    change();
    printf("%d\n",data);
    return 0;
}