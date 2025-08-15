#ifndef INTAL_H
#define INTAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
char* intal_add(const char* intal1,const char* intal2);
int intal_compare(const char* intal1,const char* intal2);
char* intal_diff(const char* intal1, const char* intal2);
char* intal_multiply(const char* intal1, const char* intal2);
char* intal_mod(const char* intal1, const char* intal2);
char* intal_pow(const char* intal1,unsigned int n);
char* intal_gcd(const char* intal1,const char* intal2);
char* intal_fibonacci(unsigned int n);
char* intal_factorial(unsigned int n);
char* intal_bincoeff(unsigned int n,unsigned int k);
static int getmin(unsigned int a,unsigned int b);
int intal_max(char** arr,int n);
int intal_min(char** arr,int n);
int intal_search(char **arr,int n,const char* key);

static void mergeSort(char **arr,int n);
static void merge(char **arr,int n,int m);

int intal_binsearch(char **arr,int n,const char* key);
static int custom_binSearch(char **arr,int l,int r,char* key);

char* coin_row_problem(char **arr,int n);

static char* find_max(char **arr,char **dp_table,int n);

#endif