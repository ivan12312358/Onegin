#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>


typedef struct
{
   char* point;
   unsigned len;
} str;

char* f_open(unsigned* sym_cnt, unsigned* str_cnt, char* file_name);

void txt_str(str* string, char* symbols, unsigned sym_cnt);

int str_compare(const void* str1, const void* str2);

int rv_str_compare(const void* str_1, const void* str_2);

void swap (str* str1, str* str2);

void my_qsort(str* strings, unsigned long begin, unsigned long end, int compare(const void *f_str, const void *s_str));

void text_print(str* string, unsigned str_cnt, const char* mode, char* file_name);

void print_Onegin(char* symbols, unsigned str_cnt, char* file_name);
