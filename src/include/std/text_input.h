#ifndef STD_TEXT_INPUT_H
#define STD_TEXT_INPUT_H

void std_text_input_create(struct std_draw_point *point, char *str, char str_length, char (*test_func)(char input));

char std_ti_number_test(char input);
char std_ti_letters_lowercase_test(char input);
char std_ti_letters_uppercase_test(char input);
char std_ti_letters_test(char input);
char std_ti_alphanum_test(char input);

#endif /* std/text_input.h */