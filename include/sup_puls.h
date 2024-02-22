#ifndef puls
#define puls

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int ONE    = 1;
const int TWO    = 2;
const int THREE  = 3;

enum haikku_string
{
    FST_STR = 5,
    SEC_STR = 7,
    TRD_STR = 5
};

int arr_of_haikku_str[3] = {FST_STR, SEC_STR, TRD_STR};

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
		printf("\033[91mError in condition %s in string %d in file %s in function %s \n\033[39m", #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__ ); \
        return type_error;                                                                                                                           \
    }

#define hard_check(condition)           				        														                   		     \
    if (!(condition))                                                                                                                                \
    {                                                                                                                                                \
		printf("\033[91mError in condition %s in string %d in file %s in function %s \n\033[39m", #condition, __LINE__, __FILE__, __PRETTY_FUNCTION__ ); \
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
			printf(RED("Entered wrong value. Try one mor time.\n"));
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

int debug_puts(int* arr, int size, int bang)
{
    check(arr != nullptr, EOF_error)

    int ch = 0;
    size_t count = 0;

    while (count < size)
    {
        if(count == bang)
        {
            printf(GREEN("%d"), arr[count]);
        }
        else
        {
            printf(RED("%d"), arr[count]);
        }

        count++;
    }

    return (count == 0) ? EOF_error : no_error;
}

int kvazi_puts(char *arr)
{
    check(arr != nullptr, EOF_error)

    int ch = 0;
    size_t count = 0;

    while ( ( ch = arr[count] ) != '\0' && (ch != EOF) && (ch != '\n'))
    {
        putchar(ch);

        count++;
    }

    if((ch == '\0') || (ch == EOF))
    {
        putchar('\n');
    }
    else
    {
        putchar(' ');
    }

    return (count == 0) ? EOF_error : no_error;
}

double time_searcher()
{
    struct timespec time_str;

    timespec_get(&time_str, TIME_UTC);

    double time_rl = (double)time_str.tv_sec + (double)time_str.tv_nsec/10e8;

    return time_rl;
}

size_t elem_counter(FILE* input)
{
    check(input != nullptr, arg_function_is_nullptr);

    fseek(input, 0L, SEEK_END);
    size_t file_elems= ftell(input);
    fseek(input, 0L, SEEK_SET);

    printf("Elements: %zu\n", file_elems);

    if (file_elems<= 0)
    {
        printf("No symbols in file:(\n");
        return 0;
    }

    return file_elems;
}

Errors null_putter(char* arr_of_symb, size_t file_elems)
{
    for(int cur_elem = 0; cur_elem< file_elems; cur_elem++)
    {
        if(arr_of_symb[cur_elem] == '\n')
        {
            arr_of_symb[cur_elem] = '\0';
        }
    }

    return no_error;
}

Words* scan_fl_syll_and_acc(FILE* input, size_t* file_elems, size_t* amount_of_str)
{
    check(input != nullptr, 0);

    fscanf(input, "%ld%ld", file_elems, amount_of_str); //Заполняем информацией об отсортированных словах

    if(*file_elems <= *amount_of_str)
    {
        printf(RED("\n\nIn file with data may be mystake!\n\nCheck please that it starts by num which show amount \
of symbols in dictionary and amount of string right in this order!!\n"));
    }

    if((*file_elems< 10) || (*amount_of_str < 10))
    {
        printf(RED("\n\nIn file with data may be mystake!\n\nCheck please that it starts by num which show amount \
of symbols in dictionary and amount of string!!\n"));
    }

    Words* arr_of_words_info =  (Words*)calloc(*amount_of_str + 2, sizeof(Words));
    check(arr_of_words_info != nullptr, 0);

    for(int count = 0; count < *amount_of_str; count++)
    {
        fscanf(input, "%d%d%d", &arr_of_words_info[count].how_many_vowel, &arr_of_words_info[count].len, &arr_of_words_info[count].accent);
    }

    return arr_of_words_info;
}

int* scan_fl_boards(FILE* input, int* am_of_boarder)
{
    check(input != nullptr, 0);

    fscanf(input, "%d", am_of_boarder);

    if(*am_of_boarder < 3)
    {
        printf(RED("\n\nIn file with data may be mystake!\n\nCheck please that it starts by num which show amount of syllables' boarder!!\n"));
    }

    int* arr_of_syllable = (int*)calloc(*am_of_boarder + 2, sizeof(int));
    check(arr_of_syllable != nullptr, 0);

    for(int count = 0; count < *am_of_boarder; count++)                //информация о том, где начинаются слова с бОльшим количеством слогов
    {
        fscanf(input, "%d", &arr_of_syllable[count]);
    }

    return arr_of_syllable;
}

Errors bond_make(Words* arr_of_word_info, char* arr_of_symb, size_t amount_of_str, size_t file_elems)
{
    for(size_t cur_elem = 0, cur_word = 0; cur_elem < file_elems; cur_word++)
    {
        arr_of_word_info[cur_word].data = arr_of_symb + cur_elem;

        cur_elem += arr_of_word_info[cur_word].len + 1;

        check(cur_word <= amount_of_str, unknown_error);
    }

    return no_error;
}

char* rule_shower(int* size_of_plot)
{
    printf("\t' accient sign\n\t- syllable without accient\n\t* end of input\n");
    printf("Enter your ritmic please (two accient syllables or more):\n");

    size_t amount = 10;

    int count = 0;

    char* ritm = (char*)calloc(amount, sizeof(char));
    char buf = 0;

    while((scanf("%c", &buf) == 62) || (buf == '-') || (buf == '\''))
    {
        ritm[count] = buf;

        count++;

        if(count == amount)
        {
            amount *= 2;

            ritm = (char*)realloc(ritm, amount);
        }
    }

    *size_of_plot = count;

    ritm[count] = '\0';

    clear_buf();

    return ritm;
}

int* translater(char* arr_of_ritm, int size, int* amount_of_syll)
{
    int* transl_ritm = (int*)calloc(size, sizeof(int));

    for(int count = 0; count < size; count++)
    {
        if(arr_of_ritm[count] == '\'')
        {
            transl_ritm[count] = 1;

            *amount_of_syll += 1;
        }

        if(arr_of_ritm[count] == '-')
        {
            transl_ritm[count] = 0;
        }
    }

    return transl_ritm;
}

int kvazi_random(int bottom, int ceiling)
{
    return bottom + (rand() + time(0)) % (ceiling - bottom + 1);
}

char* word_search(int syllables, int len_min, int len_max, int* arr_of_syllable, Words* arr_of_words_info)
{
    int bottom = arr_of_syllable[syllables - 1];
    int seilling = arr_of_syllable [syllables] - 1;

    int count = 0;
    int find = 0;

    int is_high_time_to_ceparate_word = 0;


    if(syllables != 1)
    {
        while(find == 0)
        {
            count = kvazi_random(bottom, seilling);

            find = 1;

            while((arr_of_words_info[count].len < len_min)
                || (arr_of_words_info[count].len > len_max))               // Идём искать вперёд
            {
                count++;

                if(count == seilling)
                {
                    find = 0;

                    break;                                               //Не нашли, ушли за границу
                }
            }

            if(find == 1)
            {
                return arr_of_words_info[count].data;
            }

            find = 1;

            while((arr_of_words_info[count].len < len_min)              //Идём искать назад
                || (arr_of_words_info[count].len > len_max)) 
            {
                count--;

                if(count == bottom - 1)                                  //Не нашли, ушли за границу => надо разделить слово и найти 2
                {
                    find = 0;
                    is_high_time_to_ceparate_word = 1;

                    return 0;
                }
            }

            if(find == 1)
            {
                return arr_of_words_info[count].data;
            }
        }
    }
    else
    {
        count = kvazi_random(bottom, seilling);

        return arr_of_words_info[count].data;
    }

    return 0;
}

char* word_search_acc(int syllables, int len_min, int len_max, int accent, int* arr_of_syllable, Words* arr_of_words_info)
{
    int bottom = arr_of_syllable[syllables - 1];
    int seilling = arr_of_syllable [syllables] - 1;

    int count = 0;
    int find = 0;

    int is_high_time_to_ceparate_word = 0;


    if(syllables != 1)
    {
        while(find == 0)
        {
            count = kvazi_random(bottom, seilling);

            find = 1;

            while((arr_of_words_info[count].accent != accent)          // Идём искать вперёд
                || (arr_of_words_info[count].len < len_min)
                || (arr_of_words_info[count].len > len_max))
            {
                count++;

                if(count == seilling)
                {
                    find = 0;

                    break;                                               //Не нашли, ушли за границу
                }
            }

            if(find == 1)
            {
                return arr_of_words_info[count].data;
            }

            find = 1;

            while((arr_of_words_info[count].accent != accent)          //Идём искать назад
                ||   (arr_of_words_info[count].len < len_min)
                || (arr_of_words_info[count].len > len_max))
            {
                count--;

                if(count == bottom - 1)                                  //Не нашли, ушли за границу => надо разделить слово и найти 2
                {
                    find = 0;
                    is_high_time_to_ceparate_word = 1;

                    return 0;
                }
            }

            if(find == 1)
            {
                return arr_of_words_info[count].data;
            }
        }
    }
    else
    {
        count = kvazi_random(bottom, seilling);

        return arr_of_words_info[count].data;
    }

    return 0;
}

void dump(int fst, int sec, int rand, int syll_count, int end_of_arr_flag, int word_beg, int words_count, int* transl_ritm, int size, char** arr_of_words)
{

    printf(RED("BEGIN ") GREEN("of debug output\n"));
    printf("fst = %d\t", fst);
    printf("sec = %d\n", sec);
    printf("syll_count = %d:\n\n", syll_count);

    debug_puts(transl_ritm, size, syll_count);

    printf("\nrand = %d\n", rand);
    printf("word_beg = %d\n", word_beg);
    printf("end_of_arr_flag = %d\n", end_of_arr_flag);
    printf("words_count = %d\n", words_count);

    if(arr_of_words[0] != 0)
    {
        printf("Already found words:");

        for(int count = 0; arr_of_words[count] != 0; count++)
        {
            kvazi_puts(arr_of_words[count]);
            putchar('\n');
        }
    }
    else
    {
        printf("No wornd recognized\n");
    }

    printf(RED("END ") GREEN("of debug output\n"));

    getchar();
}

char** seporater_finder (int* transl_ritm, int size_of_plot, int how_many_words, Words* arr_of_words_info, int* arr_of_syllable, int* true_am_of_words)
{
    char** arr_of_words = (char**)calloc(how_many_words + 2, sizeof(char*));

    int fst  = 0;
    int sec  = 0;
    int rand = 0;
    int syll_count = 0;
    int end_of_arr_flag = 0;
    int word_beg = 0;
    int words_count = 0;

    while(1)
    {

        fst = 0;
        sec = 0;

        //Iteration_Count = 0;

        while(1)
        {
            //Iteration_Count++;
            //printf("Iteration_Count = %d\n", Iteration_Count);

            if((transl_ritm[syll_count] == 0) && (end_of_arr_flag == 0))
            {

                //printf("We are in if(transl_ritm[syll_count] == 0)\n");

                //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                if(syll_count > size_of_plot - 1)
                {
                    end_of_arr_flag = 1;
                }

                syll_count++;

                //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                continue;
            }
            else
            {
                if(fst == 0)
                {
                    //printf("We are in if(fst == 0)\n");

                    //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                    fst = syll_count;

                    if(syll_count == 0)
                    {
                        fst = -1;
                    }

                    //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);
                }
                else if((sec == 0) && (syll_count <= size_of_plot - 1))
                {
                    //printf("We are in else if(sec == 0)\n");

                    //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                    sec = syll_count;

                    //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);
                }
                else
                {
                    ;
                }

                if((sec == 0) && (syll_count >= size_of_plot - 1))
                {
                    //printf("We are in if((syll_count == size_of_plot - 1) && (sec == 0))\n");

                    //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                    end_of_arr_flag = 1;

                    //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);
                }

                syll_count++;
                //printf(GREEN("Right now syll_count++\n\n"));

                //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);
            }

            if(sec != 0)
            {
                //printf("We are in if(sec != 0)\n");

                //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                if(fst == -1)
                {
                    fst = 0;
                }

                rand = kvazi_random(fst - word_beg + 1, sec - word_beg);

                arr_of_words[words_count] = word_search_acc(rand, 0, 30, fst - word_beg + 1, arr_of_syllable, arr_of_words_info);
                if(arr_of_words[words_count] == 0)
                {
                    printf(RED("Didn't find word with parametrs:\n%d syllables in long\naccent on %d syllable\n"), rand, fst - word_beg + 1);
                }
                else
                {
                    printf(GREEN("Was found word with parametrs:\n%d syllables in long\naccent on %d syllable\n"), rand, fst - word_beg + 1);
                }
                words_count++;

                word_beg = rand + word_beg;
                syll_count = word_beg;

                break;
            }


            if(end_of_arr_flag == 1)
            {
                //printf("We are in if(end_of_arr_flag == 1)\n");

                //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                if(fst == -1)
                {
                    fst = 0;
                }

                arr_of_words[words_count] = word_search_acc(size_of_plot - word_beg, 0, 30, fst - word_beg + 1, arr_of_syllable, arr_of_words_info);

                if(arr_of_words[words_count] == 0)
                {
                    printf(RED("Didn't find word with parametrs:\n%d syllables in long\naccent on %d syllable\n"), size_of_plot - word_beg, fst - word_beg + 1);
                }
                else
                {
                    printf(GREEN("Was found word with parametrs:\n%d syllables in long\naccent on %d syllable\n"), size_of_plot - word_beg, fst - word_beg + 1);
                }

                //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

                break;
             }
        }

        if(end_of_arr_flag == 1)
        {
            //printf("We are in if (end_of_arr_flag == 1)" RED("out of fst circ\n"));

            //dump(fst, sec, rand, syll_count, end_of_arr_flag, word_beg, words_count, transl_ritm, size_of_plot, arr_of_words);

            break;
        }
    }

    return arr_of_words;
}

Errors pulse_maker(Words* arr_of_words_info, int* arr_of_syllable)
{
    char** arr_of_words = 0;
    char* arr_of_ritm   = 0;
    int*  transl_ritm   = 0;
    int flag            = 0;
    int size_of_plot    = 0;
    int amount_of_acc   = 0;
    int true_am_of_word = 0;

    arr_of_ritm = rule_shower(&size_of_plot);
    check(arr_of_ritm != nullptr, arg_function_is_nullptr);

    transl_ritm = translater(arr_of_ritm, size_of_plot, &amount_of_acc);
    check(transl_ritm != nullptr, arg_function_is_nullptr);

    printf("You entered: %s\nOR ", arr_of_ritm);

    for(int count = 0; count < size_of_plot; count++)
    {
        printf(GREEN("%d"), transl_ritm[count]);
    }

    putchar('\n');


    printf(RED("\namount_of_accent= %d\n"), amount_of_acc);
    printf(GREEN("size_of_plot= %d\n\n"), size_of_plot);

    arr_of_words = seporater_finder(transl_ritm, size_of_plot, amount_of_acc, arr_of_words_info, arr_of_syllable, &true_am_of_word);
    check(arr_of_words != nullptr, arg_function_is_nullptr);

    for(int count = 0; count < amount_of_acc; count++)
    {
        kvazi_puts(arr_of_words[count]);

        putchar('\n');

    }

    printf("Enter " GREEN("0") " to continue, " GREEN("any number instead of 0") " for exit\n");

    free(arr_of_words);
    free(transl_ritm);
    free(arr_of_ritm);

    return no_error;
}

Errors string_maker(char** arr_of_words, int am_of_words, int am_of_syll, int *arr_of_syllable, Words *arr_of_words_info)
{
    int rand       = 0;
    int cur_syll   = 0;
    int high_board = am_of_syll - am_of_words;

    if(am_of_words > am_of_syll)
    {
        printf(RED("\nAmount of syllables can't be more than amount of words!\n\n"));

        return unknown_error;
    }

    printf(RED("We are in string_maker\n"));

    for(int count = 0; count < am_of_words; count++)
    {
        rand = kvazi_random(0, high_board);

        printf("rand = %d on %d circle\n", rand, count + 1);

        if(high_board != 0)
        {
            high_board -= rand; 
        }

        printf("high_board = %d on %d circle\n", high_board, count + 1);

        arr_of_words[count] = word_search(1 + rand, 0, 20, arr_of_syllable, arr_of_words_info);

        cur_syll += rand;

        printf("cur_syll = %d on %d circle\n", cur_syll, count + 1);
    }

    int null_count = 0;
    for(; (arr_of_words[am_of_words - 1])[null_count] != '\n'; null_count++)
    {
        ;
    }

    (arr_of_words[am_of_words - 1])[null_count] = '\0';

    return no_error;
}

Errors cor_enter_haik_ck(int cur_num, int num)
{
    if(num < cur_num)
        {
            printf(RED("\nIn current string can't be %d words because of haikku rules\n\n"), cur_num);
        }

    return no_error;
}

int string_fulling(int str_num, char** arr_of_words, int am_of_syll, int *arr_of_syllable, Words *arr_of_words_info)
{
    int am_of_words = 0;

    printf("How many words shold be in %d string?\n", str_num + 1);

    enter_int_num(&am_of_words);

    cor_enter_haik_ck(am_of_words, am_of_syll);

    string_maker(arr_of_words, am_of_words, am_of_syll, arr_of_syllable, arr_of_words_info);

    return am_of_words;
}

Errors haikku_maker(int *arr_of_syllable, Words *arr_of_words_info)
{
    char** arr_of_words = (char**)calloc(17, sizeof(char*)); //В хокку максимум 17 слов (если все слова односложные)

    int cur_word = 0;

    for(int count = 0; count < THREE; count++)
    {
        cur_word += string_fulling(count, arr_of_words + cur_word, arr_of_haikku_str[count], arr_of_syllable, arr_of_words_info);
    }

    for(int count = 0; count < cur_word; count++)
    {
        kvazi_puts(arr_of_words[count]);
    }

    putchar('\n');

    return no_error;
}

Errors menu_shower(Words* arr_of_words_info, int* arr_of_syllable)
{
    int answ = 0;

    while(1)
    {
        int is_break = 0;

        printf("\tEnter \n\t\t" GREEN("1") " to start pulse_maker\n\n\t\t" GREEN("2") " to start haikku_maker\n\n\t\t" GREEN("any number instead of 1 or 2") " for exit\n");

        enter_int_num(&answ);

        switch(answ)
        {
        case ONE:
            {
                pulse_maker(arr_of_words_info, arr_of_syllable);

                break;
            }
        case TWO:
            {
                haikku_maker(arr_of_syllable, arr_of_words_info);

                break;
            }
        default:
            {
                is_break = 1;

                break;
            }
        }

        if(is_break)
        {
            break;
        }
    }

    return no_error;
}

#endif
