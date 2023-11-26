#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    FILE *fp;
    int printFlag = 0;
    char token[100];
    memset(token, '\0', strlen(token));
    char input[2];
    input[1] = '\0';
    if (( fp = fopen("testData.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        // 文件指针返回 NULL 则退出
        exit(1);         
    }
    input[0] = fgetc(fp);
    while (input[0] != EOF)
    {
        strcat(token, input);
        //printf("token: %s\n", token);
        if(input[0] == ';'){
            printf("token: %s", token);
            printf(";\n");
            printFlag = 1;
            memset(token, '\0', strlen(token));
        }else if(input[0] == '\n'){
            if(printFlag == 0){
                printf("token: %s", token);
                printf("change line");
                printf("strlen: %d\n", strlen(token));
            }
            printFlag = 0;
            memset(token, '\0', strlen(token));
        }else{
            //printf("input: %s\n", input);
        }
        input[0] = fgetc(fp);
    }
    fclose(fp);
    return 0;
}