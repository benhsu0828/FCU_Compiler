#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX 80
#define INTSIZE 10

int num1 = 0;
int num2 = 0;
int inputFlag = 0;//0 :num1還沒有輸入 1 :可以做運算了
int numBuffer[MAX];


int main ()
{
    FILE *fp;
    char infix[MAX]; 
    char postfix[MAX]; 
    memset(infix, '\0', strlen(infix));

    if (( fp = fopen("testData.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);         
    }
    int i=0;
    while(!feof(fp)){
        fscanf(fp ,"%s", &infix[0]);
        printf("%dinfix: %s\n",i++, infix);
        test(infix);
        printf("%dinfix: %s\n",i++, infix);
    }
    fclose(fp);
    return 0;
}