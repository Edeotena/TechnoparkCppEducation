#include "prototype_storage.h"
#include "file_methods_check.h"

int main(void) {
    if (file_methods_check("file.dat")) {
        int choice = 0;
        FILE *file_clients, *file_transactions , *file_ready_clients;
        data client_data = {0}, transfer_to_client = {0};

        printf("%s\n%s\n%s\n%s\n\n",
               "please enter action",
               "1 enter data client:",
               "2 enter data transaction:",
               "3 update base");

        while (scanf("%d", &choice) != -1) {
            switch (choice) {
            case 1:
                file_clients = fopen("record.dat", "r+");
                if (file_clients == NULL) {
                    puts("Not access");
                } else {
                    master_write(file_clients, client_data);
                    fclose(file_clients);
                }
            break;

            case 2:
                file_clients = fopen(filename, "r+");
                if (file_clients == NULL) {
                    puts("Not access");
                } else {
                    transaction_write(file_clients, transfer_to_client);
                    fclose(file_clients);
                }
                break;

            case 3:
                file_clients = fopen("record.dat", "r");
                file_transactions = fopen(filename, "r");
                file_ready_clients = fopen("blackrecord.dat", "w");
                if (file_clients == NULL || file_transactions == NULL) {
                    puts("exit");
                } else {
                    black_record(file_clients, file_transactions,
                    file_ready_clients, client_data, transfer_to_client);
                    fclose(file_clients);
                    fclose(file_transactions);
                    fclose(file_ready_clients);
                }
                break;

            default:
                puts("error");
                break;
            }

        printf("%s\n%s\n%s\n%s\n\n",
               "please enter action",
               "1 enter data client:",
               "2 enter data transaction:",
               "3 update base");
        }
    } else {
        printf("work with file trouble");
    }
    return 0;
}
