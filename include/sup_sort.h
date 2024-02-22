#ifndef sort
#define sort

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum Errors
{
    unknown_error           = -10,
    EOF_error               = EOF,
    arg_function_is_nullptr = 0,
    no_error                = 1
};

typedef struct words
{
    char*             data = 0;
    int     how_many_vowel = 0;
    int                len = 0;
    int             accent = 0;
}Words;

#define check(condition, type_error)      				        														                   		     \
    if (!(condition))                                                                                                                                \
    {                                                                                                                                                \
		printf("\033[91mОшибка в условии %s в строке %d в файле %s в функции %s \n\033[39m", #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__ ); \
        return type_error;                                                                                                                           \
    }

#define hard_check(condition)           				        														                   		     \
    if (!(condition))                                                                                                                                \
    {                                                                                                                                                \
		printf("\033[91mОшибка в условии %s в строке %d в файле %s в функции %s \n\033[39m", #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__ ); \
        abort();                                                                                                                                     \
    }

#define RED(b)   "\033[91m" b "\033[39m"
#define GREEN(b) "\033[32m" b "\033[39m"

//Для очистки буффера
int clear_buf()
{
	while (getchar() != '\n');

    return no_error;
}

//Для корректного ввода целых числовых значений
int enter_int_num(int* koeff)
{
	while ( (scanf("%d", koeff)) != 1 )
	{
			printf(RED("Введено нецелое число. А должно быть введено целое число. Попробуйте ввести его ещё раз. \n"));
			clear_buf();
	}
	clear_buf();

    return no_error;
}

//Для корректного ввода нецелых числовых значений
int enter_double_num(double* koeff)
{
	while ( (scanf("%lf", koeff)) != 1 )
	{
			printf(RED("Введено не число. А должно быть введено число. Попробуйте ввести его ещё раз. \n"));
			clear_buf();
	}
	clear_buf();

    return no_error;
}

int kvazi_puts(char *arr)
{
    check(arr != nullptr, EOF_error)

    int ch = 0;
    size_t count = 0;

    while ( ( ch = putchar(arr[count++]) ) != '\0' && (ch != EOF) && (ch != '\n'))
    {
        ;
    }

    return (count == 0) ? EOF_error : no_error;
}

int kvazi_fputs(char *arr, FILE* fl_ptr)
{
    check(arr != nullptr, EOF_error)

    int ch = 0;
    size_t count = 0;

    while ( ( ch = putc(arr[count++], fl_ptr) ) != '\0' && (ch != EOF) && (ch != '\n'))
    {
        ;
    }

    return (count == 0) ? EOF_error : no_error;
}

Errors show_all_words_and_info(size_t amount_of_str, Words** arr_of_ptr_info)
{
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);
    for(int count = 0; count < amount_of_str; count++)
        {
            check(arr_of_ptr_info[count] != nullptr, arg_function_is_nullptr);
//            kvazi_puts(arr_of_ptr_info[count]->data);
//            printf("\nthis word has %d vowel and is %d in length\n\n", arr_of_ptr_info[count]->how_many_vowel, arr_of_ptr_info[count]->len);
        }

    return no_error;
}

int vowel_check_ISO(char letter)
{
    if (letter == -34)
        return 1;
    else if (letter == -48)
        return 1;
    else if (letter == -43)
        return 1;
    else if (letter == -29)
        return 1;
    else if (letter == -40)
        return 1;
    else if (letter == -17)
        return 1;
    else if (letter == -19)
        return 1;
    else if (letter == -18)
        return 1;
    else if (letter == -21)
        return 1;
    else if (letter == -15)
        return -1;
    else if (letter == -80)
        return 1;
    else if (letter == -75)
        return 1;
    else if (letter == -61)
        return 1;
    else if (letter == -72)
        return 1;
    else if (letter == -49)
        return 1;
    else if (letter == -51)
        return 1;
    else if (letter == -50)
        return 1;
    else if (letter == -53)
        return 1;
    else if (letter == -95)
        return -1;
    else
        return 0;
    return 0;
}

long how_many_str(char* arr_of_symb)
{
    check(arr_of_symb, arg_function_is_nullptr);

    size_t am_str = 0;

    for(size_t schet = 0; arr_of_symb[schet] != '\0'; schet++)
    {
        if (arr_of_symb[schet] == '\n')
            am_str++;
    }
    return am_str;
}

int comp_syll(Words fst, Words sec)
{
    //check(fst != 0, arg_function_is_nullptr);
    //check(sec != 0, arg_function_is_nullptr);

    int razn = 0;

    razn = fst.how_many_vowel - sec.how_many_vowel;

    return razn;
}

int comp_len(Words fst, Words sec)
{
    //check(fst != 0, arg_function_is_nullptr);
    //check(sec != 0, arg_function_is_nullptr);

    int razn = 0;

    razn = fst.len - sec.len;

    return razn;
}

int swap(Words** fst, Words** sec)
{
    check(fst != nullptr, arg_function_is_nullptr);
    check(sec != nullptr, arg_function_is_nullptr);

    Words* yeur = *fst;
    *fst = *sec;
    *sec = yeur;

    return 0;
}

int sort_by_syllable(Words** arr_of_words_info, size_t amount)
{
    check(arr_of_words_info != nullptr, arg_function_is_nullptr);

    for(size_t out_count = 0; out_count < amount - 1; out_count++)
    {
        size_t swapped = 0;

        for(size_t in_count = 0; in_count < amount - 1; in_count++)
        {
            check(arr_of_words_info[in_count] != nullptr, arg_function_is_nullptr);
            check(arr_of_words_info[in_count + 1] != nullptr, arg_function_is_nullptr);

            if (comp_syll(*arr_of_words_info[in_count], *arr_of_words_info[in_count + 1]) > 0)
            {
                swap(&arr_of_words_info[in_count], &arr_of_words_info[in_count + 1]);
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    return 0;
}

int sort_by_len(Words** arr_of_words_info, size_t amount)
{
    check(arr_of_words_info != nullptr, arg_function_is_nullptr);

    for(size_t out_count = 0; out_count < amount - 1; out_count++)
    {
        size_t swapped = 0;

        for(size_t in_count = 0; in_count < amount - 1; in_count++)
        {
            check(arr_of_words_info[in_count] != nullptr, arg_function_is_nullptr);
            check(arr_of_words_info[in_count + 1] != nullptr, arg_function_is_nullptr);

            if (comp_len(*arr_of_words_info[in_count], *arr_of_words_info[in_count + 1]) > 0)
            {
                swap(&arr_of_words_info[in_count], &arr_of_words_info[in_count + 1]);
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    return 0;
}

Errors sort_by_len_complete(Words** arr_of_ptr_info, int* arr_of_syllable, int am_of_boarder)
{
    check(arr_of_syllable != nullptr, arg_function_is_nullptr);
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);

    for(int count = 1; count < am_of_boarder; count++)
    {
//         printf("arr_of_ptr_info = %p\n", arr_of_ptr_info);
//         printf("sizeof(Words**) = %zu\n", sizeof(Words**));
//
//         printf("\narr_of_ptr_info + arr_of_syllable[%d] = %p\narr_of_syllable[%d] - arr_of_syllable[%d] = %d\n", count, arr_of_ptr_info + arr_of_syllable[count -  1], count, count - 1, arr_of_syllable[count] - arr_of_syllable[count - 1]);

        sort_by_len(arr_of_ptr_info + arr_of_syllable[count - 1], arr_of_syllable[count] - arr_of_syllable[count - 1]);

        //show_all_words_and_info(arr_of_syllable[count] - arr_of_syllable[count - 1], arr_of_ptr_info + arr_of_syllable[count]);
    }

    return no_error;
}

int new_am_of_border_search(Words** arr_of_ptr_info, size_t amount_of_str, int* arr_of_syllable)
{
    check(arr_of_syllable != nullptr, arg_function_is_nullptr);
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);

    int am_of_boarder = 1;
    int flag    = 1;

    for(int count = 0; count < amount_of_str; count++)
        {
            check(arr_of_ptr_info[count] != nullptr, arg_function_is_nullptr);

            if (arr_of_ptr_info[count]->how_many_vowel != flag)
            {
                arr_of_syllable[am_of_boarder] = count; //Первый элемент с бОшьшим количеством слогов

                flag++;
                am_of_boarder++;

                check(am_of_boarder != 100, unknown_error);
            }
        }

    return am_of_boarder;
}

Errors full_fl_syll_and_acc(FILE* output, Words** arr_of_ptr_info, size_t file_elem, size_t amount_of_str)
{
    check(output != nullptr, arg_function_is_nullptr;)
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);

    fprintf(output, "%10ld %10ld\n", file_elem, amount_of_str); //Заполняем информацией об отсортированных словах

    for(int count = 0; count < amount_of_str; count++)
    {
        check(arr_of_ptr_info[count] != nullptr, arg_function_is_nullptr);

        fprintf(output, "%10d %10d %10d\n", arr_of_ptr_info[count]->how_many_vowel, arr_of_ptr_info[count]->len, arr_of_ptr_info[count]->accent);
    }

    return no_error;
}

Errors full_fl_rise(FILE* output, int am_of_boarder, int* arr_of_syllable)
{
    check(output != nullptr, arg_function_is_nullptr;)
    check(arr_of_syllable != nullptr, arg_function_is_nullptr);

    fprintf(output, "%d\n", am_of_boarder);

    for(int count = 0; count < am_of_boarder; count++)                //информация о том, где начинаются слова с бОльшим количеством слогов
    {
        fprintf(output, "%d\n", arr_of_syllable[count]);
    }

    return no_error;
}

Errors full_sorted_words(FILE* output, size_t amount_of_str, Words** arr_of_ptr_info)
{
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);
    check(output != nullptr, arg_function_is_nullptr;)

    for(int count = 0; count < amount_of_str; count++)     //Заполняем отсортированными словами
    {
        check(arr_of_ptr_info[count] != nullptr, arg_function_is_nullptr);

        if(kvazi_fputs(arr_of_ptr_info[count]->data, output) != no_error)
            printf(RED("MISSTAKE in word on string: %d"), count);
    }

    return no_error;
}

Errors ptr_and_len_search(Words** arr_of_ptr_info, char* arr_of_symb, size_t file_elem)
{
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);
    check(arr_of_symb != nullptr, arg_function_is_nullptr);

    long cur_word = 0;
    long cur_elem = 0;
    int     begin = -1;

    while (1) //записываем указатели на начало слов и количество слогов в них
    {

        if(arr_of_symb[cur_elem] == '\n')
        {

            check(arr_of_ptr_info[cur_word] != nullptr, arg_function_is_nullptr);

            arr_of_ptr_info[cur_word]->len  = cur_elem - begin - 1;
            arr_of_ptr_info[cur_word]->data = arr_of_symb + begin + 1;

            begin = cur_elem;

            cur_word++;
            cur_elem++;

            continue;
        }

        if(vowel_check_ISO(arr_of_symb[cur_elem]))
        {
            check(arr_of_ptr_info[cur_word] != nullptr, arg_function_is_nullptr);

            (arr_of_ptr_info[cur_word]->how_many_vowel)++;
            //printf("cur_elem = %ld\nVowels = %d\n", cur_elem, arr_of_ptr_info[cur_word]->how_many_vowel);
        }

        if (arr_of_symb[cur_elem] == '\0')
        {
            break;
        }

        cur_elem++;

        check(cur_elem <= file_elem, unknown_error);
    }

    return no_error;
}

Errors accent_search(Words** arr_of_ptr_info, char* arr_of_symb, size_t file_elem, size_t amount_of_str)
{
    size_t cur_elem = 0;
    size_t cur_word = 0;

    int flag = 0;
    int buff = 0;

    for(;cur_word < amount_of_str; cur_word++, cur_elem++)
    {
        flag = 0;

        for(;arr_of_symb[cur_elem] != '\n'; cur_elem++)
        {
            if((buff = vowel_check_ISO(arr_of_symb[cur_elem])) == -1)
            {
                check(arr_of_ptr_info[cur_word] != nullptr, arg_function_is_nullptr);

                arr_of_ptr_info[cur_word]->accent = flag + 1;

                continue;

                //printf("cur_elem = %ld\nVowels = %d\n", cur_elem, arr_of_ptr_info[cur_word]->how_many_vowel);
            }

            if(buff)
            {
                flag++;
            }
        }

        check(cur_elem <= file_elem, unknown_error);
    }

    return no_error;
}

size_t elem_counter(FILE* input)
{
    check(input != nullptr, arg_function_is_nullptr);

    fseek(input, 0L, SEEK_END);
    size_t file_elem = ftell(input);
    fseek(input, 0L, SEEK_SET);

    printf("Элементов: %zu\n", file_elem);

    if (file_elem <= 0)
    {
        printf("В файле нет символов:(\n");
        return 0;
    }

    return file_elem;
}

#endif
