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
// 4. Mutiplication function
char* intal_multiply(const char* intal1, const char* intal2){
    int l1, l2, res_len;
    l1 = strlen(intal1);
    l2 = strlen(intal2);
    res_len = l1+l2;

    char *res = (char*)malloc(sizeof(char)*(res_len+1));
    for(int k=0;k<res_len;k++){
        res[k] = '0';
    }
    res[res_len] = '\0';

    int i, j, d1, d2, sum, carry, v_shift=res_len-1, h_shift=0;

    for(i=l1-1; i>=0; i--){
        d1 = intal1[i] - '0';
        carry = 0;
        v_shift = res_len-1;

        for(j=l2-1; j>=0; j--){
            d2 = intal2[j] - '0';
            sum = (d1*d2) + (res[v_shift-h_shift] - '0') + carry;
            carry = sum / 10;
            sum = sum % 10;
            res[v_shift-h_shift] = sum + '0';
            v_shift--;
        }

        if(carry>0){
            int c = res[v_shift-h_shift] - '0';
            c = c + carry;
            res[v_shift-h_shift] = c + '0';
        }

        h_shift++;
    }
    res[res_len] = '\0';

    //removing extra zeros from the result string
    char *t1, *t2;
    t1 = stripZeros(res);
    t2 = res;
    res = t1;

    free(t2);
    return res;
}
//5. Mod function where intal1(divident) and intal2(divisor)
char* intal_mod(const char* intal1, const char* intal2){
    char *divident, *divisor, *t1, *t2;
    divident = strdup(intal1);

    int iter = 0;   //value varies between 0 and 1

    //run loop till divident is greater than divisor 
    while(intal_compare(divident,intal2)!=-1){

        divisor = strdup(intal2);
        //run loop till divisor is smaller than divident
        while(intal_compare(divident,divisor)==1){
            t1 = intal_multiply(divisor,"2");
            t2 = divisor;
            divisor = t1;
            free(t2);
        }        
        t1 = intal_diff(divisor,divident);
        t2 = divident;
        divident = t1;
        free(t2);

        //if intal1 is a factor of intal2
        if(intal_compare(divident,"0")==0){
            free(divident);
            free(divisor);
            char *res = (char*)malloc(sizeof(char)*2);
            res[0] = '0';
            res[1] = '\0';
            return res;
        }

        iter+=1;
        iter%=2;
    }

    if(iter==1){
        t1 = intal_diff(intal2,divident);
        t2 = divident;
        divident = t1;
        free(t2);
    }

    t1 = stripZeros(divident);
    t2 = divident;
    divident = t1;
    free(t2);

    free(divisor);

    return divident;  
}
//6 . power function( where intal1^n)

char* intal_pow(const char* intal1,unsigned int n){
    if(!n){
        char* res = (char*)malloc(sizeof(char)*2);
        res[0]='1';
        res[1]='\0';
        return res;
    }
    char *temp,*res;
    temp = intal_pow(intal1,n>>1);

    if(n%2==0){
        res = intal_multiply(temp,temp);
        free(temp);
        return res;
    }
    else{
        temp = intal_multiply(temp,temp);
        res = intal_multiply(intal1,temp);
        free(temp);
        return res;
    }
}

// 7. GCD -- Function to find GCD of intal1 and intal2
char* intal_gcd(const char* intal1,const char* intal2){
    if(intal_compare(intal1,"0")==0 && intal_compare(intal2,"0")==0){
        char* res = (char*)malloc(sizeof(char)*2);
        res[0]='0';
        res[1]='\0';
        return res;
    }
    else{
        char *res,*n1,*n2;
        n1 = strdup(intal1);
        n2 = strdup(intal2);
        res = compute_gcd(n1,n2);
        free(n1);
        free(n2);
        return res;
    }
}
static char* compute_gcd(char* n1,char* n2){
    if(intal_compare(n2,"0")==0){
        char* res = strdup(n1);
        return res;
    }
    char *t,*res;
    t = intal_mod(n1,n2);
    res = compute_gcd(n2,t);
    free(t);
    return res;
}

//8 . Fibonacci function
char* intal_fibonacci(unsigned int n){
    char *prev_2,*prev_1,*res,*t;
    prev_2 = (char*)malloc(sizeof(char)*2);
    prev_2[0]='0';
    prev_2[1]='\0';

    if(n==0)
        return prev_2;
    
    prev_1 = (char*)malloc(sizeof(char)*2);
    prev_1[0]='1';
    prev_1[1]='\0';

    if(n==1)
        return prev_1;
    
    int i = 2;
    while(i<=n){
        res = intal_add(prev_1,prev_2);
        t = prev_2;
        prev_2 = prev_1;
        prev_1 = res;
        free(t);
        i++;
    }
    free(prev_2);
    return res;
}