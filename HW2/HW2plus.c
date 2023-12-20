#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000
#define MAX 80

int totalInt = 0;
int totalFloat = 0;
int totalID = 0;
int totalError = 0;
int num1 = 0;
int num2 = 0;
int inputFlag = 0;//0 :num1還沒有輸入 1 :可以做運算了

void inToPostfix(char*, char*); // 中序轉後序 
int priority(char); // 運算子優先權

void inToPostfix(char* infix, char* postfix) { 
    char stack[MAX] = {'\0'};
    int i, j, top;
    for(i = 0, j = 0, top = 0; infix[i] != '\0'; i++) switch(infix[i]) { 
        case '(':              // 運算子堆疊 
            stack[++top] = infix[i]; 
            break; 
        case '+': case '-': case '*': case '/': 
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
        default:  // 運算元直接輸出 
            postfix[j++] = infix[i];
    }
    while(top > 0) { 
        postfix[j++] = stack[top--];
    }
} 

int priority(char op) { 
    switch(op) { 
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } 
} 

void judgeToken(char token[]) {
    int isInt = 0;//是否為整數
    int isFloat = 0;//是否為浮點數
    int isID = 0;//是否為ID

    isInt = IsInt(token);
    isFloat = IsFloat(token);
    isID = IsID(token);
    if(isInt){
        totalInt++;
        if(token[strlen(token)-1] == '\n'){printf("Integer: %s", token);}
        else{printf("Integer: %s\n", token);}
    }else if(isFloat){
        totalFloat++;
        if(token[strlen(token)-1] == '\n')printf("Float: %s", token);
        else{printf("Float: %s\n", token);}
    }else if(isID){
        totalID++;
        if(token[strlen(token)-1] == '\n')printf("ID: %s", token);
        else{printf("ID: %s\n", token);}
    }else{
        totalError++;
        if(token[strlen(token)-1] == '\n')printf("Error: %s", token);
        else{printf("Error: %s\n", token);}
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
    
    while(input[0]!=EOF){
        fscanf(fp ,"%s", infix);
        inToPostfix(infix, postfix);
    }
    while (input[0] != EOF)
    {
        strcat(token, input);
        if(input[0] == ';'){
            judgeToken(token);
            memset(token, '\0', strlen(token));
            printFlag = 1;
        }else if(input[0] == '\n'){
            if(printFlag == 0){
                judgeToken(token);
            }else{
                printFlag = 0;
            }
            memset(token, '\0', strlen(token));
        }else{//印完分號下一個不是換行就重置flag
            printFlag = 0;
        }
        input[0] = fgetc(fp);
    }
    //最後一個token
    judgeToken(token);
    fclose(fp);
    for(int i = 0; i < 50; i++){
        printf("*");
    }
    printf("\n");
    printf("Total Integer: %d\n", totalInt);
    printf("Total Float: %d\n", totalFloat);
    printf("Total ID: %d\n", totalID);
    printf("Total Error: %d\n", totalError);
    return 0;
}

 

