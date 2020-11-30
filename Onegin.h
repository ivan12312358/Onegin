#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

/**
*	@brief Structure str
*
*	@param point - point to string
*	@param len - length of string
*/

typedef struct
{
   unsigned char* point;
   unsigned len;
} str;

/**
*	@brief Function reads text from a file and writes in array
*
*	@param sym_cnt - count of symbols
*	@param str_cnt - count of strings
*	@param file_name - name of sorting file
*	
*	return symbols - pointer to array of symbols
*/

unsigned char* f_open(unsigned* sym_cnt, unsigned* str_cnt, char* file_name);

/*!
*	@brief Function splits symbols on strings  
*	
*	@param string - point to array of strings
*	@param sym_cnt - count of symbols
*	@param symbols - pointer to array of symbols
*/

void txt_str(str* string, unsigned char* symbols, unsigned sym_cnt);

/**
*	@brief Function compares 2 strings from start
*
*	@param str1 - point to first string
*	@param str2 - point to second string
*
*	return result of compare 2 strings
*/

int str_compare(const void* str1, const void* str2);

/**
*	@brief Function compares 2 strings from end
*
*	@param str1 - point to first string
*	@param str2 - point to second string
*
*	return result of compare 2 strings
*/

int rv_str_compare(const void* str_1, const void* str_2);

/**
*	@brief Function swaps points to strings
*
*	@param str1 - point to first string
*	@param str2 - point to second string
*/

void swap (str* str1, str* str2);

/**
*	@brief Function sorts strings
*	
*	@param strings - point to strings 
*	@param begin - index of first string
*	@param end - index of last string
*/

void my_qsort(str* strings, unsigned long begin, unsigned long end, int compare(const void *f_str, const void *s_str));

/**
*	@brief Function prints sorted text	
*	
*	@param string - point to string
*	@param str_cnt - count of strings
*	@param mode - mode of work with file
*	@param file_name - name of file where the text will be printed
*/

void text_print(str* string, unsigned str_cnt, const char* mode, char* file_name);

/**
*	@brief Function prints origin text
*
*	@param symbols - point to first symbol
*	@param str_cnt - count of strings
*	@param file_name - name of file where the text will be printed
*/

void print_Onegin(unsigned char* symbols, unsigned str_cnt, char* file_name);
