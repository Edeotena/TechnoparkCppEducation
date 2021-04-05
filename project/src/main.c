#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

size_t is_in(const char* string_1, const char* string_2) {
    if (strlen(string_1) < strlen(string_2)) {
        return 0;
    }

    for (size_t i = 0; i < strlen(string_1) - strlen(string_2) + 1; ++i) {
        size_t o = 0;

        for (size_t j = 0; j < strlen(string_2); ++j) {
            if (string_1[i+j] == string_2[j] || string_1[i+j] == string_2[j] - 32) {
                o++;
            }
        }

        if (o == strlen(string_2)) {
            return i + 1;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		return -1;
	}
    bool multi_parts = false, to_found = false, from_found = false, date_found = false,
    	 from_just_found = false, to_just_found = false, date_just_found = false;
    char *path_to_file = argv[1];
    size_t parts = 0;

    char* string = (char*)(malloc(sizeof(char) * 2400000));
    if (!string) {
        free(string);
        return -1;
    }
    char* string_to = (char*)(malloc(sizeof(char) * 2400000));
    if (!string_to) {
        free(string_to);
        free(string);
        return -1;
    }
    char* string_from = (char*)(malloc(sizeof(char) * 1024));
    if (!string_from) {
        free(string_from);
        free(string_to);
        free(string);
        return -1;
    }
    char* string_date = (char*)(malloc(sizeof(char) * 1024));
    if (!string_date) {
        free(string_date);
        free(string_from);
        free(string_to);
        free(string);
        return -1;
    }
    char* string_boundary = (char*)(malloc(sizeof(char) * 1024));
    if (!string_boundary) {
        free(string_boundary);
        free(string_date);
        free(string_from);
        free(string_to);
        free(string);
        return -1;
    }
    memset(string, '\0', 2400000);
    memset(string_from, '\0', 2400000);
    memset(string_to, '\0', 2400000);
    memset(string_date, '\0', 1024);
    memset(string_boundary, '\0', 1024);

    FILE* file_to_pars = fopen(path_to_file, "r");
    if (!file_to_pars) {
        free(string_boundary);
        free(string_date);
        free(string_from);
        free(string_to);
        free(string);
        return -1;
    }

    while (!feof(file_to_pars)) {
        fgets(string, 2400000, file_to_pars);
        bool already_found_smth = false;

        if (from_just_found) {
            from_just_found = false;
            size_t i = 0;
            while (string[i] == ' ') {
                i++;
            }
            if (i) {
                from_just_found = true;
            }
            size_t size_of_string = strlen(string_from);
            for (size_t j = 0; j < strlen(string) + 1; ++j) {
                if (string[i - 1 ] == '\n' || string[i - 1] == '\r') {
                    break;
                }
                string_from[size_of_string + j] = string[i - 1];
                i++;
            }
        }

        if (to_just_found) {
            to_just_found = false;
            size_t i = 0;
            while (string[i] == ' ') {
                i++;
            }
            if (i) {
                to_just_found = true;
            }
            size_t size_of_string = strlen(string_to);
            for (size_t j = 0; j < strlen(string) + 1; ++j) {
                if (string[i - 1 ] == '\n' || string[i - 1] == '\r') {
                    break;
                }
                string_to[size_of_string + j] = string[i - 1];
                i++;
            }
        }

        if (date_just_found) {
            date_just_found = false;
            size_t i = 0;
            while (string[i] == ' ') {
                i++;
            }
            if (i) {
                date_just_found = true;
            }
            size_t size_of_string = strlen(string_date);
            for (size_t j = 0; j < strlen(string) + 1; ++j) {
                if (string[i - 1 ] == '\n' || string[i - 1] == '\r') {
                    break;
                }
                string_date[size_of_string + j] = string[i - 1];
                i++;
            }
        }

        if (string[0] == 'T' && string[1] == 'o' && string[2] == ':' && !to_found) {
        	size_t space_count = 0;
        	while (string[3 + space_count] == ' ') {
        		++space_count;
        	}
            for (size_t i = 0; i < strlen(string) - 4 - space_count; i++) {
                if (string[i + 3 + space_count] == '\r') {
                    break;
                }
                string_to[i] = string[i + 3 + space_count];
            }
            already_found_smth = true;
            to_found = true;
            to_just_found = true;
        }

        if (string[0] == 'F' && string[1] == 'r' && string[2] == 'o' &&
        	string[3] == 'm' && string[4] == ':' && !from_found && !already_found_smth) {
        	size_t space_count = 0;
        	while (string[5 + space_count] == ' ') {
        		++space_count;
        	}
            for (size_t i = 0; i < strlen(string) - 6 - space_count; i++) {
                if (string[i + 5 + space_count] == '\r') {
                    break;
                }
                string_from[i] = string[i + 5 + space_count];
            }
            already_found_smth = true;
            from_found = true;
            from_just_found = true;
        }

        if (string[0] == 'D' && string[1] == 'a' && string[2] == 't' &&
        	string[3] == 'e' && string[4] == ':'  && !date_found && !already_found_smth) {
        	size_t space_count = 0;
        	while (string[5 + space_count] == ' ') {
        		++space_count;
        	}
            for (size_t i = 0; i < strlen(string) - 6 - space_count; i++) {
                if (string[i + 5 + space_count] == '\r') {
                    break;
                }
                string_date[i] = string[i + 5 + space_count];
            }
            already_found_smth = true;
            date_found = true;
            date_just_found = true;
        }

        if (!already_found_smth && (is_in(string, " boundary=") || is_in(string, "	boundary=") ||
        	 is_in(string, ";boundary=")) && !multi_parts) {
            size_t j = 0;
            size_t qoutes_count = 0;
            for (size_t i = is_in(string, "boundary=") + 8; i < strlen(string); ++i) {
                if (string[i] == '"') {
                    i++;
                    qoutes_count++;
                }
                if (string[i] == '/' && string[i + 1] == '"') {
                    i+=2;
                    qoutes_count++;
                }
                if (string[i] == ' ') {
                    i++;
                }
                if (qoutes_count == 2) {
                    while (string[i] != '\r' && string[i]!= '\n') {
                        i++;
                    }
                }
                string_boundary[j] = string[i];
                j++;
            }
            multi_parts = true;
        }

        if (strlen(string) <= 2) {
            break;
        }
    }

    if (multi_parts) {
        while (!feof(file_to_pars)) {
            fgets(string, 1024, file_to_pars);
            if (is_in(string, string_boundary)) {
                ++parts;
            }
        }
    } else {
        while (!feof(file_to_pars)) {
            fgets(string, 1024, file_to_pars);
            if (strlen(string) > 2) {
                parts = 1;
                break;
            }
        }
    }
    fclose(file_to_pars);

    printf("%s|%s|%s|%zu", string_from, string_to, string_date, parts);
    free(string_boundary);
    free(string);
    free(string_to);
    free(string_date);
    free(string_from);
    return 0;
}
