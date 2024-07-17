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
// 9.. factorial function: fuction of factorial of unsigend integer n
char* intal_factorail(unsigned int n){
    if(n==0 || n==1){
        char *res = (char*)malloc(sizeof(char)*2);
        res[0]='1';
        res[1]='\0';
        return res;
    }
    int i = 2;
    char *t1, *t2, *res, *add_one, *next_num;

   
    add_one = (char*)malloc(sizeof(char)*2);
    add_one[0] = '1';
    add_one[1] = '\0';

    next_num = (char*)malloc(sizeof(char)*2);
    next_num[0] = '1';
    next_num[1] = '\0';

    res = (char*)malloc(sizeof(char)*2);
    res[0] = '1';
    res[1] = '\0';

    while(i<=n){
        t1 = intal_add(next_num,add_one);
        t2 = next_num;
        next_num = t1;
        free(t2);
        t1 = intal_multiply(res,next_num);
        t2 = res;
        res = t1;
        free(t2); 
        i+=1;
    }

    free(add_one);
    free(next_num);

    return res;

}
// 10. INTAL_BINCOEFF: FUnction to compute the binary coefficeint of C(n,k)
char* intal_bincoeff(unsigned int n,unsigned int k){
    if(k> n/2)
        k= n-k;
    char** arr = (char**)malloc(sizeof(char*)*(k+1));
    for(int i =0;i<=k;i++){
        arr[i]=(char*)malloc(sizeof(char*)*MAX_SIZE);
        strcpy(arr[i],"0");
    }
    strcpy(arr[0],"1");
    char *t,*res;
    for(int i=1;i<=n;i++){
        for(int j = getmin(i,k);j>0;j--){
            t = intal_add(arr[j],arr[j-1]);
            strcpy(arr[j],t);
            free(t);
        }
    }

    res = strdup(arr[k]);
    for(int i =0;i<=k;i++){
        free(arr[i]);
    }
    free(arr);
    return res;
}

static int getmin(unsigned int a,unsigned int b){
    return (a>=b) ? a :b;
}

//11. INTAL_MAX:  Function to find max intal from array of intal & return the index pf max intal
int intal_max(char** arr,int n){
    int max_index= 0,cmp;
    char* max_intal,*t;
    max_intal = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(max_intal,arr[0]);

    for (int i = 1; i < n; i++){
        t = arr[i];
        cmp = intal_compare(t,max_intal);
        if(cmp==1){
            strcpy(max_intal,t);
            max_index = i;
        }
    }
    free(t);
    free(max_intal);
    return max_index;
}

//12. INTAL_MIN: Function to find min INTAL from given array of INTAL and return the min_index

int intal_min(char** arr,int n){
    int min_index = 0,cmp;
    char *min_intal,*t;

    min_intal = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(min_intal,arr[0]);
    for(int i =1;i<n;i++){
        t = arr[i];
        cmp = intal_compare(t,min_intal);
        if(cmp==-1){
            strcpy(min_intal,t);
            min_index = i;
        }
    }
    free(t);
    free(min_intal);
    return min_index;
}

//13. INTAL_SEARCH: A linear search to find the number from array of intal
int intal_search(char** arr,int n, const char* key){
    int res =-1,cmp;
    char* t;
    for(int i=0;i<n;i++){
        t = arr[i];
        cmp = intal_compare(t,key);
        if(cmp==0){
            res = i;
            free(t);
            break;
        }
    }
    return res;
}

static void mergeSort(char **arr,int n){
    if(n<=1)
        return;
    
    int m= n/2;
    mergeSort(arr,m);
    mergeSort(arr+m,n-m);
    merge(arr,n,m);
}

static void merge(char ** arr,int n,int m){
    int i=0,j=m,k=0;

    char **t;
    t = (char**)malloc(sizeof(char*)*n);
    for(int i = 0;i<n;i++){
        t[i]=(char*)malloc(sizeof(char)*MAX_SIZE);
        strcpy(t[i],"0");
    }

    while (i<m && j<n){
        if(intal_compare(arr[i],arr[j])!=1){
            strcpy(t[k],arr[i]);
            i++;
        }
        else{
            strcpy(t[k],arr[j]);
            j++;
        }
        k++;
    }

    if(j==n){
        while (i<m)
        {
            strcpy(t[k++],arr[i++]);
        }
    }
    else{
        while(j<n){
            strcpy(t[k++],arr[j++]);
        }
    }

    for(int i=0;i<n;i++){
        strcpy(arr[i],t[i]);
        free(t[i]);
    }
    free(t);
    
}

//15. INTAL_BINSEARCH
int intal_binsearch(char** arr,int n,const char* key){
    char *k = (char*)malloc(sizeof(char)*MAX_SIZE);
    strcpy(k,key);
    int res;
    res = custom_binSearch(arr,0,n,k);
    free(k);
    return res;
}

static int custom_binSearch(char **arr,int l,int r,char* key){
    if(r-l<0)
        return -1;
    
    int m = (l+r)/2;

    if(intal_compare(key,arr[m])==0)
        return m;
    else if(intal_compare(key,arr[m])==-1)
        return custom_binSearch(arr,l,m-1,key);
    else
        return custom_binSearch(arr,m+1,r,key);
}

