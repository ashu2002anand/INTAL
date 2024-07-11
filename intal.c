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

//1.  ADD Finction implementation
char* intal_add(const char* intal1,const char* intal2){
    int l1,l2,diff_len,res_len;
    l1=strlen(intal1);
    l2=strlen(intal2);
    diff_len=(l1>l2)?(l1-l2):(l2-l1);
    
    //we will create new copies of intal2 and intal2
    char *new_intal1,*new_intal2;
    if(l1>l2){
        new_intal1 = strdup(intal1);
        new_intal2 = padding(intal2,diff_len,l1);
        res_len=l1;
        l2=l1;
    }
    else if(l2>l1){
        new_intal1 = padding(intal1,diff_len,l2);
        new_intal2 = strdup(intal2);
        res_len = l2;
        l1 = l2;
    }
    else{
        new_intal1 = strdup(intal1);
        new_intal2 = strdup(intal2);
        res_len = l1;
    }

    char *res;
    res = (char*)malloc(sizeof(char)*(res_len+2));

    int i,j,d1,d2,sum,carry=0,k=res_len;
    for(i=l1-1,j=l2-1;i>=0;i--,j--){
        d1 = new_intal1[i]-'0';
        d2 = new_intal2[j]-'0';
        sum=d1+d2+carry;
        carry=sum/10;
        sum%=10;
        res[k]=sum+'0';
        k--;
    }
    res[0]=carry+'0';
    res[res_len+1]='\0';

    //trimming off extra zeros from answer
    char *t1,*t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;

    free(t2);
    free(new_intal1);
    free(new_intal2);
    return res;
}
//2.  COMPARE FUNCTION Description
int intal_compare(const char* intal1,const char* intal2){
    int l1,l2;
    l1 = strlen(intal1);
    l2 = strlen(intal2);

    if(l1>l2)
        return 1;
    if(l2>l1)
        return -1;

    for(int i=0;i<l1;i++){
        if(intal1[i]>intal2[i])
            return 1;
        if(intal2[i]>intal1[i])
            return -1;
    }   
    return 0;
}
//3.  Difference / substraction function
char* intal_diff(const char* intal1, const char* intal2){
    int l1, l2, cmp, diff_len, res_len;
    l1 = strlen(intal1);
    l2 = strlen(intal2);

    diff_len = (l1>l2) ? (l1-l2) : (l2-l1);

    char* new_intal1, *new_intal2;      //variables to create copies of intal1 and intal2

    if(l1>l2){
        new_intal1 = strdup(intal1);
        new_intal2 = padding(intal2,diff_len,l1);
        res_len = l1;
        l2 = l1;
    }
    else if(l2>l1){
        new_intal1 = padding(intal1,diff_len,l2);
        new_intal2 = strdup(intal2);
        res_len = l2;
        l1 = l2;
    }
    else{
        new_intal1 = strdup(intal1);
        new_intal2 = strdup(intal2);
        res_len = l1;
    }

    //value comparison, lengths are same after padding 
    cmp = intal_compare(new_intal1,new_intal2);
    if(cmp == -1){
        char *temp;
        temp = new_intal1;
        new_intal1 = new_intal2;
        new_intal2 = temp;
    }
    else if(cmp == 0){
        char *res;
        res = (char*)malloc(sizeof(char)*(2));
        res[0] = '0';
        res[1] = '\0';
        free(new_intal1);
        free(new_intal2);
        return res;
    }

    char *res;
    res = (char*)malloc(sizeof(char)*(res_len+1));

    int i, j, d1, d2, diff, carry=0, k=res_len-1;

    for(i=l1-1,j=l2-1; i>=0; i--,j--){
        d1 = new_intal1[i] - '0';
        d2 = new_intal2[i] - '0';
        diff = d1 - d2 - carry;
        if(diff<0){
            diff = diff + 10;
            carry = 1;
        }
        else{
            carry = 0;
        }

        res[k] = diff + '0';
        k--;
    }
    res[res_len] = '\0';

    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;

    free(t2);
    free(new_intal1);       
    free(new_intal2);       

    return res;
}