#include "Onegin.h"


/**
 * @brief Calls other fuctions
 *
 * @param argc Number of arguments
 * @param argv Sorting and sorted file
 *	
 * @return Program exit status
 */

int main(int argc, char** argv)
{   
	setlocale(LC_ALL, "ru_RU.cp1251");

    unsigned sym_cnt = 0, str_cnt = 0;

    unsigned char* symbols = f_open(&sym_cnt, &str_cnt, argv[1]);

    str* string = (str*)calloc(str_cnt + 1, sizeof(str));

	txt_str(string, symbols, sym_cnt);

    my_qsort(string, 0, str_cnt - 1, str_compare);

    text_print(string, str_cnt, "w", argv[2]);

    my_qsort(string, 0, str_cnt - 1, rv_str_compare);

    text_print(string, str_cnt, "a", argv[2]);

    print_Onegin(symbols, sym_cnt, argv[2]);

    free(string);
    free(symbols);

    return 0;
}


unsigned char* f_open(unsigned* sym_cnt, unsigned* str_cnt, char* file_name)
{
    FILE* file = fopen(file_name, "r");
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    *sym_cnt = ftell(file);

    unsigned char* symbols = (unsigned char*)calloc(*sym_cnt + 1, sizeof(unsigned char));

    rewind(file);
    fread(symbols, sizeof(unsigned char), *sym_cnt, file);


	unsigned char* p = symbols;    
    for(unsigned i = 0; i < *sym_cnt; i++)
    {
    	p = (unsigned char*)strchr((char*)p + 1, '\n');
    	(*str_cnt)++;
   		if(p != NULL)
    		*p = '\0';
    	else 
    		break;
    	
    }

    fclose(file);

    return symbols;
}


void txt_str(str* string, unsigned char* symbols, unsigned sym_cnt)
{
    unsigned pointer = 0, j = 0;

    for(unsigned i = 0; i < sym_cnt; i++)
    {
        if(symbols[i] == '\0')
        {
            string[j].len = strlen((char*)symbols + pointer);
            string[j].point = symbols + pointer;
            pointer = i + 1;
            j++;
        }
    }
}
 

int str_compare(const void* str_1, const void* str_2)
{
    str *str1 = (str*)str_1, *str2 = (str*)str_2;

    unsigned i = 0, j = 0;
    int f_sym = 0, s_sym = 0;
    while(i < str1->len && j < str2->len)
    {
        if(!isalpha((unsigned char)str1->point[i]))
        {
            i++;
            continue;
        }
        else 
            f_sym = tolower((unsigned char)str1->point[i]);
        

        if(!isalpha((unsigned char)str2->point[j]))
        {
            j++;
            continue;
        }
        else 
            s_sym = tolower((unsigned char)str2->point[j]);

        if(f_sym > s_sym)
            return 1;
        else if(f_sym == s_sym)
        {
            i++;
            j++;
        }
        else
            return -1;
    } 

    return str1->len - str2->len;
}


int rv_str_compare(const void* str_1, const void* str_2)
{
    str* str1 = (str*)str_1;
    str* str2 = (str*)str_2;

    unsigned i = str1->len, j = str2->len;
    int f_sym = 0, s_sym = 0;
    while(i > 0 && j > 0)
    {
        if(!isalpha((unsigned char)str1->point[i]))
        {
            i--;
            continue;
        }
        else
            f_sym = tolower(str1->point[i]);


        if(!isalpha(str2->point[j]))
        {
            j--;
            continue;
        }
        else
            s_sym = tolower(str2->point[j]);        
        
   
        if(f_sym > s_sym)
            return 1;
        else if(f_sym == s_sym)
        {
            i--;
            j--;
        }
        else
            return -1;
    }

    return str1->len - str2->len;
}


void my_qsort(str* strings, unsigned long start, unsigned long end, int comparator(const void*, const void*))
{
    unsigned long pivot = (start + end) / 2;
    str pivot_str = strings[pivot];

    unsigned long l = start, r = end;

    while (l <= r)
    {
        while (comparator(&pivot_str, strings + l) >=  1) 
            l++;
        while (comparator(&pivot_str, strings + r) <= -1)
            r--;
        if (l <= r)
        {
            swap(strings + l, strings + r);
            l++;
            r--;
        }
    }

    if (start < r)
        my_qsort(strings, start, r, comparator);
    if (l < end)
        my_qsort(strings, l, end, comparator);
}


void swap (str* str1, str* str2)
{
    assert(str1 && str2);

    str temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}


void text_print(str* string, unsigned str_cnt, const char* mode, char* file_name)
{
    FILE* file = fopen(file_name, mode);
    assert(file != NULL);
    for(unsigned i = 0; i < str_cnt; i++)
    {    
    	for(unsigned j = 0; j < string[i].len; j++)
        {    
            if(isalpha(string[i].point[j]))
            {
                fprintf(file, "%s\n", string[i].point + j);
                break;
            }
        }
    }

    fprintf(file, "\n\n\n\n\n");
    fclose(file);
}


void print_Onegin(unsigned char* symbols, unsigned sym_cnt, char* file_name)
{
    FILE* file = fopen(file_name, "a+");
    assert(file != NULL);
 
    for(unsigned i = 0; i < sym_cnt; i++)
    {  
        if(symbols[i] == '\0')
            fprintf(file, "%s\n", symbols + i + 1);
        if(i == 0)
            fprintf(file, "%s\n", symbols + i);
    }
    
    fclose(file);
}