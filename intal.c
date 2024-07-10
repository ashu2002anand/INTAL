#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"

//assuming the max intial length to be 1000 (+1 is for null chracter)
#define MAX_SIZE 1001

//Helper function to perform arithematic operations
static char* padding(const char* intalTemp,int zeros,int new_length);
static char* stripZeros(const char* intalTemp);
static char* compute_gcd(char* n1,char* n2);
static int getmin(unsigned int a,unsigned int b);
static void merge(char **arr,int n,int m);
static void mergeSort(char **arr,int n);
static int custom_binSearch(char ** arr,int l,int r,char *key);
static char* find_max(char **arr,char **dp_table,int n);

//padding with prefix zeros to change the length of given character array function description
static char* padding(const char* intalTemp,int zeros,int new_length){
    char *res;
    res = (char*)malloc(sizeof(char)*new_length +1);
    int k =0;
    for(int i=0;i<zeros;i++){
        res[k]='0';
        k++;
    }
    for(int i=0;i<strlen(intalTemp);i++){
        res[k]=intalTemp[i];
        k++;
    }
    res[k]='\0';
    return res;
}

// stripfunction description --- remove the prefix zeros if present
static char* stripZeros(const char* intalTemp){
    int check = 1;
    for(int i=0;i<strlen(intalTemp);i++){
        if(intalTemp[i]!='0'){
            check=0;
            break;
        }
    }
    if(check){
        char* res = (char*)malloc(sizeof(char)*2);
        res[0]='0';
        res[1]='\0';
        return res;
    }

    int initial_zeros = 0;
    for(int i=0; i<strlen(intalTemp); i++){
        if(intalTemp[i]=='0')
            initial_zeros++;
        else
            break;
    } 

    int new_len = strlen(intalTemp) - initial_zeros, k = 0;
    char* res;
    res = (char*)malloc(sizeof(char)*(new_len+1));
    
    for(int i=initial_zeros; i<strlen(intalTemp); i++){
        res[k] = intalTemp[i];
        k++;
    }
    res[new_len] = '\0';
    return res;
}