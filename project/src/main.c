#include "utils.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return (-1);
    }

    char *path_to_file = argv[1];

    FILE* file_to_pars = fopen(path_to_file, "r");
    if (!file_to_pars) {
        return (-1);
    }

    key_words* mail = create_key_words();
    if (mail == NULL) {
        fclose(file_to_pars);
        return (-1);
    }

    size_t parts = 0;
    bool is_multy = false, is_empty = true;
    bool from_just_found = false, to_just_found = false, date_just_found = false;

    char* line = NULL;
    size_t line_size = 0;

    while (!feof(file_to_pars)) {
        getline(&line, &line_size, file_to_pars);
        if (line[0] == '\r' || line[0] == '\n') {
            break;
        }

        if (to_just_found) {
            if (!expand_key_word(&mail->string_to, &line, file_to_pars)) {
                free_key_words(mail);
                free(line);
                fclose(file_to_pars);
                return (-1);
            }
            to_just_found = false;
        }

        if (from_just_found) {
            if (!expand_key_word(&mail->string_from, &line, file_to_pars)) {
                free_key_words(mail);
                free(line);
                fclose(file_to_pars);
                return (-1);
            }
            from_just_found = false;
        }

        if (date_just_found) {
            if (!expand_key_word(&mail->string_date, &line, file_to_pars)) {
                free_key_words(mail);
                free(line);
                fclose(file_to_pars);
                return (-1);
            }
            date_just_found = false;
        }

        int new_key_word;

        new_key_word = find_key_word(&mail->string_to, &line , "To:");
        if (new_key_word) {
            if (new_key_word == -1) {
                free_key_words(mail);
                free(line);
                fclose(file_to_pars);
                return (-1);
            }
            to_just_found = true;
        }

        new_key_word = find_key_word(&mail->string_from, &line , "From:");
        if (new_key_word) {
            if (new_key_word == -1) {
                free_key_words(mail);
                free(line);
                fclose(file_to_pars);
                return (-1);
            }
            from_just_found = true;
        }

        new_key_word = find_key_word(&mail->string_date, &line , "Date:");
        if (new_key_word) {
            if (new_key_word == -1) {
                free_key_words(mail);
                free(line);
                fclose(file_to_pars);
                return (-1);
            }
            date_just_found = true;
        }

        if (!is_multy) {
            new_key_word = find_boundary(&mail->string_boundary, &line);
            if (new_key_word) {
                if (new_key_word == -1) {
                    free_key_words(mail);
                    free(line);
                    fclose(file_to_pars);
                    return (-1);
                }
                is_multy = true;
            }
        }
    }

    while (!feof(file_to_pars)) {
        getline(&line, &line_size, file_to_pars);
        size_t line_len = strlen(line);

        if (line[0] != '\n' && line[0] != '\r') {
            is_empty = false;
            if (!is_multy) {
                break;
            }
        }

        if (is_multy) {
            size_t boundary_len = strlen(mail->string_boundary);

            if (strstr(line, mail->string_boundary) != NULL) {
                if (line_len - boundary_len <= 4 && line[line_len - 1] != '-') {
                    ++parts;
                }
            }
        }
    }

    if (is_empty) {
        parts = 0;
    } else {
        if (!is_multy) {
            parts = 1;
        }
    }


    printf("%s|%s|%s|%zu", mail->string_from, mail->string_to, mail->string_date, parts);

    fclose(file_to_pars);
    free(line);
    free_key_words(mail);
    return 0;
}
