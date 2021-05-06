#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char* string_to;
    char* string_from;
    char* string_date;
    char* string_boundary;
} key_words;

bool is_letter(char symbol);

bool is_equal(char* first, char* second);

void free_key_words(key_words* words_to_free);

key_words* create_key_words();

char* delete_endline(char* line);

char* info_to_add(char* info, char* additional_info);

bool expand_key_word(char** key_word, char** line, FILE* file_to_pars);

int find_key_word(char** key_word, char** line, char* required_key_word);

char* lower_string(char* string_to_make_lower);

int find_boundary(char** key_boundary, char** line);
