#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000
#define MAX 80
#define INTSIZE 10

int num1 = 0;
int num2 = 0;
int inputFlag = 0;//0 :num1還沒有輸入 1 :可以做運算了

void inToPostfix(char*, char*); // 中序轉後序 
int priority(char); // 運算子優先權
int turnToInt(char*); // 字串轉整數

void inToPostfix(char* infix, char* postfix) { 
    char stack[MAX] = {'\0'};
    int i, j, top;
    char intBuffer[INTSIZE] ; // 整數暫存區
    memset(stack, '\0', strlen(stack));
    memset(intBuffer, '\0', strlen(intBuffer));

    for(i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '(':              // 運算子堆疊 
            stack[++top] = infix[i]; 
            break; 
        case '+': case '-': case '*': case '/': 
            turnToInt(intBuffer);
            while(priority(stack[top]) >= priority(infix[i])) { 
                postfix[j++] = stack[top--];
            } 
            stack[++top] = infix[i]; // 存入堆疊 
            break; 
        case ')': 
            while(stack[top] != '(') { // 遇 ) 輸出至 ( 
                postfix[j++] = stack[top--];
            } 
            top--;  // 不輸出 ( 
            break; 
        default:  // 運算元先暫存至整數暫存區
            strcat(intBuffer, infix[i]);
    }
    while(top > 0) { 
        postfix[j++] = stack[top--];
    }
} 

int turnToInt(char* str){
    int result = 0;
    for(int i = 0; i < strlen(str); i++){
        result = result * 10 + (str[i] - '0');
    }
    return result;
}

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 


int main() {
    FILE *fp;
    char token[SIZE];
    char infix[MAX]; 
    char postfix[MAX]; 
    memset(token, '\0', strlen(token));
    memset(infix, '\0', strlen(infix));
    memset(postfix, '\0', strlen(postfix));    

    if (( fp = fopen("testText.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);         
    }
    fscanf(fp ,"%s", infix);
    while(infix!=EOF){
       
        inToPostfix(infix, postfix);
        fscanf(fp ,"%s", infix);
    }

    //最後一個token
    fclose(fp);
    for(int i = 0; i < 50; i++){
        printf("*");
    }
    return 0;
}

 

