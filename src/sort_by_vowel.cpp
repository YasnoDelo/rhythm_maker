#include "../include/sup_sort.h"

int main()
{

    FILE* output1 = fopen("output_files/out_kir.txt", "w");
    FILE* output2 = fopen("output_files/info_about_sorted.txt", "w"); //Там информация о том, сколько в каких словах слогов и какая у этих слов длина
    FILE* output3 = fopen("output_files/info_syllable.txt", "w");     //Там информация о том, где начинаются слова с бОльшим количеством строк

    check(output1 != nullptr, arg_function_is_nullptr);
    check(output2 != nullptr, arg_function_is_nullptr);
    check(output3 != nullptr, arg_function_is_nullptr);

    FILE* input = fopen("input_files/words_kir.txt", "rb");
    check(input != nullptr, arg_function_is_nullptr);

    size_t file_elem = elem_counter(input);

    char* arr_of_symb = (char*)calloc(file_elem + 2, sizeof(char));
    check(arr_of_symb != nullptr, arg_function_is_nullptr);
    arr_of_symb[file_elem + 1] = '\0';

    size_t schitano = fread(arr_of_symb, sizeof(char), file_elem, input);
    printf("Read %zu elems\n", schitano);

    size_t amount_of_str = how_many_str(arr_of_symb);
    printf("Amount of strings: %zu\n", amount_of_str);

    if(schitano != file_elem)
    {
        printf(RED("\n\nRead less or more elements then needed\n"));
    }

    Words**   arr_of_ptr_info = (Words**)calloc(amount_of_str + 2, sizeof(Words*));
    Words*  arr_of_words_info =  (Words*)calloc(amount_of_str + 2, sizeof(Words));

    check(arr_of_words_info != nullptr, arg_function_is_nullptr);
    check(arr_of_ptr_info != nullptr, arg_function_is_nullptr);

    for(int counter = 0; counter <= amount_of_str; counter++)
    {
        arr_of_ptr_info[counter] = &arr_of_words_info[counter];
    }

    ptr_and_len_search(arr_of_ptr_info, arr_of_symb, file_elem);

    accent_search(arr_of_ptr_info, arr_of_symb, file_elem, amount_of_str);

    show_all_words_and_info(amount_of_str, arr_of_ptr_info);

    sort_by_syllable(arr_of_ptr_info, amount_of_str);

    int arr_of_syllable[100] = {};
    int am_of_boarder = new_am_of_border_search(arr_of_ptr_info, amount_of_str, arr_of_syllable);

    sort_by_len_complete(arr_of_ptr_info, arr_of_syllable, am_of_boarder);

    show_all_words_and_info(amount_of_str, arr_of_ptr_info);

    full_sorted_words(output1, amount_of_str, arr_of_ptr_info);

    full_fl_syll_and_acc(output2, arr_of_ptr_info, file_elem, amount_of_str);

    full_fl_rise(output3, am_of_boarder, arr_of_syllable);

    free(arr_of_symb);
    free(arr_of_words_info);
    free(arr_of_ptr_info);

    fclose(output1);
    fclose(output2);
    fclose(output3);
    fclose(input);

    return 0;
}
