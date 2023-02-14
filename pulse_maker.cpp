#include "sup_puls.h"

int main()
{
    time_t check = time(0);
    struct timespec cho;

    timespec_get(&cho, TIME_UTC);

    printf("cho.tv_sec = %ld, cho.tv_nsec = %ld, check = %ld\n\n", cho.tv_sec, cho.tv_nsec, check);

    double ti_st = 0;
    double ti_en = 0;

    double bg = 0;
    double en = 0;

    ti_st = time_searcher();

    printf(GREEN("\n\ntime in the begin of prog  is %lf sec\n\n"), ti_st);

    FILE* info_syllable     = fopen("info_syllable.txt", "rb");
    FILE* sorted_words      = fopen("out_kir.txt", "rb");
    FILE* info_about_sorted = fopen("info_about_sorted.txt", "rb");

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

    bg = time_searcher();

    printf(GREEN("\n\nProg is ready for work %lf sec since start\n\n"), bg - ti_st);

    menu_shower(bg, en, arr_of_words_info, arr_of_syllable);    

    free(arr_of_symb);
    free(arr_of_words_info);
    free(arr_of_syllable);

    fclose(info_about_sorted);
    fclose(info_syllable);
    fclose(sorted_words);

    ti_en = time_searcher();
    printf(GREEN("\ntime in the end of prog is %lf sec\n\n"), ti_en);

    printf(RED("prog worked due %lf sec\n"), ti_en - ti_st);

    return 0;
}
