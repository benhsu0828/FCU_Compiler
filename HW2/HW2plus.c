#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80
#define INTSIZE 10

int num1 = 0;
int num2 = 0;
int inputFlag = 0;//0 :num1還沒有輸入 1 :可以做運算了
int numBuffer[MAX];

void inToPostfix(char*, char*); // 中序轉後序 
int priority(char); // 運算子優先權
void output(char*); // 輸出結果

void inToPostfix(char* infix, char* postfix) { 
    char stack[MAX] = {'\0'};
    int i, j, k,top;// i: infix index, j: postfix index, k: numBuffer index, top: stack top
    int numPointer = 0;
    char intBuffer[INTSIZE] ; // 整數暫存區
    //init
    memset(stack, '\0', strlen(stack));
    memset(intBuffer, '0', strlen(intBuffer));
    for(int i=0;i<MAX;i++){
        numBuffer[i] = 0;
    }
    
    for(i = 0, j = 0,k =0 ,top = 0; infix[i] != '\0'; i++) {
        //printf("infix[%d]: %c\n", i, infix[i]);
        switch(infix[i]) { 
            case '(':              // 運算子堆疊 
                stack[++top] = infix[i]; 
                break; 
            case '+': case '-': case '*': case '/': 
                if(infix[i]=='-'&& i==0){//第一個為負號
                    intBuffer[numPointer++] = infix[i];
                    intBuffer[numPointer] = '\0';//字串結尾加上'\0
                }else{
                    if(atoi(intBuffer) != 0){
                    numBuffer[k++] = atoi(intBuffer);//將整數暫存區的字串轉成整數存入numBuffer
                    memset(intBuffer, '0', strlen(intBuffer));//清空整數暫存區
                    numPointer = 0;//整數暫存區指標歸零
                    postfix[j++] = 'n';//數字flag
                    }
                    while(priority(stack[top]) >= priority(infix[i])) { 
                        postfix[j++] = stack[top--];
                    }
                    stack[++top] = infix[i]; // 存入堆疊 
                }
                break; 
            case ')': 
                numBuffer[k++] = atoi(intBuffer);//將整數暫存區的字串轉成整數存入numBuffer
                memset(intBuffer, '0', strlen(intBuffer));//清空整數暫存區
                numPointer = 0;//整數暫存區指標歸零
                postfix[j++] = 'n';//數字flag
                while(stack[top] != '(') { // 遇 ) 輸出至 ( 
                    postfix[j++] = stack[top--];
                } 
                top--;  // 不輸出 ( 
                break; 
            default:  // 運算元先暫存至整數暫存區
                intBuffer[numPointer++] = infix[i];
                intBuffer[numPointer] = '\0';//字串結尾加上'\0
                //printf("intBuffer: %s\n", intBuffer);
                break;
        }
    }
    if(atoi(intBuffer) != 0){
        numBuffer[k++] = atoi(intBuffer);//將整數暫存區的字串轉成整數存入numBuffer
        memset(intBuffer, '0', strlen(intBuffer));//清空整數暫存區
        numPointer = 0;//整數暫存區指標歸零
        postfix[j++] = 'n';//數字flag
    }
    while(top > 0) { //將最後的結果輸出
        postfix[j++] = stack[top--];
    }
    //for(int tmp = 0; tmp < k; tmp++)printf("numBuffer: %d\n", numBuffer[tmp]);
} 

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 

void output(char* postfix){
    int top = -1;
    int result = 0;
    for(int i = 0; i < strlen(postfix); i++){
        switch(postfix[i]){
            case 'n':
                top++;
                break;
            case '+':
                num2 = numBuffer[top];
                num1 = numBuffer[--top];
                result = num1 + num2;
                printf("%d plus %d equals %d\n", num1, num2, result);
                numBuffer[top] = result;
                //將numBuffer後面的數字往前移
                for(int j=top+1;j<MAX;j++){
                    numBuffer[j] = numBuffer[j+1];
                }
                break;
            case '-':
                num2 = numBuffer[top];
                num1 = numBuffer[--top];
                result = num1 - num2;
                printf("%d minus %d equals %d\n", num1, num2, result);
                numBuffer[top] = result;
                //將numBuffer後面的數字往前移
                for(int j=top+1;j<MAX;j++){
                    numBuffer[j] = numBuffer[j+1];
                }
                break;
            case '*':
                num2 = numBuffer[top];
                num1 = numBuffer[--top];
                result = num1 * num2;
                printf("%d multiply %d equals %d\n", num1, num2, result);
                numBuffer[top] = result;
                //將numBuffer後面的數字往前移
                for(int j=top+1;j<MAX;j++){
                    numBuffer[j] = numBuffer[j+1];
                }
                break;
            case '/':
                num2 = numBuffer[top];
                num1 = numBuffer[--top];
                result = num1 / num2;
                printf("%d div %d equals %d\n", num1, num2, result);
                numBuffer[top] = result;
                //將numBuffer後面的數字往前移
                for(int j=top+1;j<MAX;j++){
                    numBuffer[j] = numBuffer[j+1];
                }
                break;
            default:
                break;
        }
    }
    printf("ANS is %d\n", result);
}


int main() {
    FILE *fp;
    char infix[MAX]; 
    char postfix[MAX]; 
    memset(infix, '\0', strlen(infix));
    memset(postfix, '\0', strlen(postfix));
    for(int i=0;i<MAX;i++){
        numBuffer[i] = 0;
    }

    if (( fp = fopen("input.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);         
    }
    while(!feof(fp)){
        memset(infix, '\0', strlen(infix));
        memset(postfix, '\0', strlen(postfix));
        fscanf(fp ,"%s", infix);
        printf("infix: %s\n", infix);
        inToPostfix(infix, postfix);
        //printf("postfix: %s\n", postfix);
        output(postfix);
        printf("\n");
    }

    fclose(fp);
    return 0;
}

 

