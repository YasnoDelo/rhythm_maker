#include "../include/sup_puls.h"

int main()
{
    FILE* info_syllable     = fopen("output_files/info_syllable.txt", "rb");
    FILE* sorted_words      = fopen("output_files/out_kir.txt", "rb");
    FILE* info_about_sorted = fopen("output_files/info_about_sorted.txt", "rb");

    size_t amount_of_words = 0;
    size_t file_elems = 0;

    int am_of_boarder = 0;

    Words* arr_of_words_info = scan_fl_syll_and_acc(info_about_sorted, &file_elems, &amount_of_words);
    check(arr_of_words_info != nullptr, arg_function_is_nullptr);

    int* arr_of_syllable = scan_fl_boards(info_syllable, &am_of_boarder);
    check(arr_of_syllable != nullptr, arg_function_is_nullptr);

    char* arr_of_symb = (char*)calloc(file_elems + 2, sizeof(char));
    check(arr_of_symb != nullptr, arg_function_is_nullptr);
    arr_of_symb[file_elems + 1] = '\0';
    null_putter(arr_of_symb, file_elems);

    size_t schitano = fread(arr_of_symb, sizeof(char), file_elems, sorted_words);
    printf("Read %zu elems\n", schitano);

    if(schitano != file_elems)
    {
        printf(RED("\n\nRead less or more elements then needed\n"));
    }

    printf("\n\namount_of_words = %zu\nfile_elems = %zu\nam_of_boarder = %d\n\n", amount_of_words, file_elems, am_of_boarder);

    bond_make(arr_of_words_info, arr_of_symb, amount_of_words, file_elems);

    menu_shower(arr_of_words_info, arr_of_syllable);    

    free(arr_of_symb);
    free(arr_of_words_info);
    free(arr_of_syllable);

    fclose(info_about_sorted);
    fclose(info_syllable);
    fclose(sorted_words);

    return 0;
}
