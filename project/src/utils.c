#include "utils.h"

bool is_letter(char symbol) {
    if ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z')) {
        return true;
    }

    return false;
}

bool is_equal(char* first, char* second) {
    if (first == NULL || second == NULL) {
        return false;
    }

    size_t first_size = strlen(first);
    size_t second_size = strlen(second);

    if (first_size != second_size) {
        return false;
    }

       if(!strcmp(first,second)) {
        return true;
    }

    return false;
}

void free_key_words(key_words* words_to_free) {
    if (words_to_free != NULL) {
        if (words_to_free->string_to != NULL) {
            free(words_to_free->string_to);
        }
        if (words_to_free->string_from != NULL) {
            free(words_to_free->string_from);
        }
        if (words_to_free->string_date != NULL) {
            free(words_to_free->string_date);
        }
        if (words_to_free->string_boundary != NULL) {
            free(words_to_free->string_boundary);
        }
        free(words_to_free);
    }
}

key_words* create_key_words() {
    key_words* result = (key_words*) calloc(1, sizeof(key_words));
    if (result == NULL) {
        return NULL;
    }

    result->string_to = (char*)calloc(1, sizeof(char));
    result->string_from = (char*)calloc(1, sizeof(char));
    result->string_date = (char*)calloc(1, sizeof(char));
    result->string_boundary = (char*)calloc(1, sizeof(char));

    if (result->string_to == NULL || result->string_from == NULL ||
    result->string_date == NULL || result->string_boundary == NULL) {
        free_key_words(result);
        return NULL;
    }
    return result;
}

char* delete_endline(char* line) {
    if (line == NULL) {
        return NULL;
    }

    size_t line_size = strlen(line);
    if (line_size <= 2) {
        return NULL;
    }

    size_t symbols_to_delete_count = 0;

    if (line[line_size - 2] == '\n' || line[line_size - 2] == '\r') {
        symbols_to_delete_count = 2;
    } else {
        if (line[line_size - 1] != '\n' && line[line_size - 1] != '\r') {
            return line;
        } else {
            symbols_to_delete_count = 1;
        }
    }

    char* result_line = (char*)calloc(line_size - symbols_to_delete_count + 1, sizeof(char));
    if (result_line == NULL) {
        return NULL;
    }

    memcpy(result_line, line, line_size - symbols_to_delete_count);

    return result_line;
}

char* info_to_add(char* info, char* additional_info) {
    if (additional_info[0] != ' ') {
        return additional_info;
    }

    size_t space_count = 0;
    while(additional_info[space_count] == ' ') {
        ++space_count;
    }
    --space_count;

    size_t info_size = strlen(info);
    size_t additional_info_size = strlen(additional_info);

    char* info_for_result = delete_endline(additional_info);    
    if (info_for_result == NULL) {
        return NULL;
    }

    char* result_info = (char*)calloc((info_size + additional_info_size + 1), sizeof(char));
    if (result_info == NULL) {
        free(info_for_result);
        return NULL;
    }

    memcpy(result_info, info, info_size);
    memcpy(result_info + info_size, info_for_result + space_count, additional_info_size - space_count + 1);

    free(additional_info);
    free(info_for_result);
    info = result_info;

    return result_info;
}

bool expand_key_word(char** key_word, char** line, FILE* file_to_parse) {
    size_t line_size = 0;
    while (true) {
        char* expanded_key_word = info_to_add(*key_word, *line);

        if(expanded_key_word == NULL) {
            return false;
        }

        if(expanded_key_word == *line) {
            break;
        }

        free(*key_word);
        *key_word = expanded_key_word;
        *line = NULL;
        getline(line, &line_size, file_to_parse);
    }

    return true;
}

int find_key_word(char** key_word, char** line, char* required_key_word) {
    size_t key_word_size = strlen(required_key_word);
    if (strlen(*line) < key_word_size) {
        key_word_size = strlen(*line);
    }

    for (size_t i = 0; i < key_word_size; ++i) {
        if ((*line)[i] != required_key_word[i]) {
            return 0;
        }
    }

    size_t symbols_to_skip = strlen(required_key_word);
    while((*line + symbols_to_skip)[0] == ' ') {
        ++symbols_to_skip;
    }

    free(*key_word);	
    *key_word = *line + symbols_to_skip;
    *key_word = delete_endline(*key_word);
    if (*key_word == NULL) {
        return (-1);
    }

    return 1;
}

char* lower_string(char* string_to_make_lower) {    
    size_t string_size = strlen(string_to_make_lower);
    char* result = (char*)calloc(string_size + 1, sizeof(char));

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < string_size; ++i) {
        result[i] = (char)tolower(string_to_make_lower[i]);
    }

    return result;
}

int find_boundary(char** key_boundary, char** line) {

    char* test_boundary = lower_string(*line);
    if (test_boundary == NULL) {
        return (-1);
    }

    if (strstr(test_boundary, "boundary") == NULL) {
        free(test_boundary);
        return 0;
    }

    size_t boundary_place = strlen(*line) - strlen(strstr(test_boundary, "boundary"));
    free(test_boundary);

    if (is_letter((*line)[boundary_place - 1])) {
        return 0;
    }

    size_t boundary_start = boundary_place + strlen("boundary");
    while ((*line + boundary_start)[0] == ' ' || (*line + boundary_start)[0] == '=') {
        boundary_start++;
    }

    if((*line + boundary_start)[0] == '"') {
        ++boundary_start;
    }

    size_t boundary_end = boundary_start;

    for (;; ++boundary_end) {
        if ((*line + boundary_end)[0] == '"' || (*line + boundary_end)[0]  == ';' || (*line + boundary_end)[0] == '\r' || (*line + boundary_end)[0]  == '\n' || (*line + boundary_end)[0]  == ' ') {
            --boundary_end;
            break;
        }
    }

    char* ready_bountary = (char*)calloc(boundary_end,sizeof(char));
    if (ready_bountary == NULL) {
        return (-1);
    }

    strncpy(ready_bountary, *line + boundary_start, boundary_end - boundary_start + 1);

    free(*key_boundary);
    *key_boundary = ready_bountary;

    return 1;
}
