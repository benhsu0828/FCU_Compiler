#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1000

int IsInt(char token[]){
    for(int i = 0; i < strlen(token); i++){
        switch (token[i])
        {
        case '0':
            break;
        case '1':
            break;
        case '2': 
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6': 
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case '-'://負號
            if(i != 0 ){return 0;} //如果不是第一個字元有負號，則error
            break;
        case ';'://分號
            //避免第一個字元就是分號
            if(i == 0){return 0;}
            break;
        case '\n'://換行
            //避免第一個字元就是換行
            if(i == 0){return 0;}
            break;
        default://除了數字和負號以外的字元都是error
            return 0;
            break;
        }
    }
    return 1;
}
int IsFloat(char token[]){
    int dotCount = 0;//小數點個數
    for(int i = 0; i < strlen(token); i++){
        switch (token[i])
        {
        case '0':
            break;
        case '1':
            break;
        case '2': 
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6': 
            break;
        case '7':
            break;
        case '8':
            break;
        case '9':
            break;
        case '.':
            dotCount++;
            if(dotCount > 1){return 0;}
            break;
        case '-'://負號
            if(i != 0 ){return 0;} //如果不是第一個字元有負號，則error
            break;
        case '_'://底線
            return 0;
            break;
        case ';'://分號
            //避免第一個字元就是分號
            if(i == 0){return 0;}
            break;
        case '\n'://換行
            //避免第一個字元就是換行
            if(i == 0){return 0;}
            break;
        default:
            return 0;
            break;
        }
    }
    return 1;

}
int IsID(char token[]){
    //不符合規則的開頭，負號、底線、小數點或數字開頭
    switch (token[0])
    {
    case '-'://負號
        return 0;
        break;
    case '_'://底線
        return 0;
        break;
    case '.'://小數點
        return 0;
        break;
    case ';'://分號，避免第一個字元就是分號
        return 0;
        break;
    case '\n'://換行
        //避免第一個字元就是換行
        return 0;
        break;
    case '0':
        return 0;
        break;
    case '1':
        return 0;
        break;
    case '2':
        return 0;
        break;
    case '3':
        return 0;
        break;
    case '4':
        return 0;
        break;
    case '5':
        return 0;
        break;
    case '6': 
        return 0;
        break;
    case '7':
        return 0;
        break;
    case '8':
        return 0;
        break;
    case '9':
        return 0;
        break;
    default:
        break;
    }
    //token body
    for(int i = 1; i < strlen(token); i++){
        switch (token[i])
        {
        case '-'://負號
            return 0;
            break;
        case '.'://小數點
            return 0;
            break;
        default:
            break;
        }
    }
    return 1;
}
void judgeToken(char token[]) {
    int isInt = 0;//是否為整數
    int isFloat = 0;//是否為浮點數
    int isID = 0;//是否為ID

    isInt = IsInt(token);
    isFloat = IsFloat(token);
    isID = IsID(token);
    if(isInt){
        if(token[strlen(token)-1] == '\n'){printf("Integer: %s", token);}
        else{printf("Integer: %s\n", token);}
    }else if(isFloat){
        if(token[strlen(token)-1] == '\n')printf("Float: %s", token);
        else{printf("Float: %s\n", token);}
    }else if(isID){
        if(token[strlen(token)-1] == '\n')printf("ID: %s", token);
        else{printf("ID: %s\n", token);}
    }else{
        if(token[strlen(token)-1] == '\n')printf("Error: %s", token);
        else{printf("Error: %s\n", token);}
    }
    
}

int main() {
    FILE *fp;
    char token[SIZE];
    memset(token, '\0', strlen(token));
    char input[2];
    input[1] = '\0';
    int printFlag = 0;
    if (( fp = fopen("testText.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);         
    }
    input[0] = fgetc(fp);
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
    return 0;
}