#include "prototype_storage.h"
#include "file_methods_check.h"

#define file_access_error (-1)

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
            case enter_data_client:
                file_clients = fopen("record.dat", "r+");
                if (file_clients == NULL) {
                    puts("Not access");
                    break;
                }

                master_write(file_clients, client_data);
                fclose(file_clients);
            break;

            case enter_data_transaction:
                file_clients = fopen(filename, "r+");
                if (file_clients == NULL) {
                    puts("Not access");
                    break;
                }

                transaction_write(file_clients, transfer_to_client);
                fclose(file_clients);
                break;

            case update_base:
                file_clients = fopen("record.dat", "r");
                if (file_clients == NULL) {
                    puts("Not access");
                    break;
                }

                file_transactions = fopen(filename, "r");
                if (file_transactions == NULL) {
                    puts("Not access");
                    fclose(file_clients);
                    break;
                }

                file_ready_clients = fopen("blackrecord.dat", "w");
                if (file_ready_clients == NULL) {
                    puts("Not access");
                    fclose(file_clients);
                    fclose(file_transactions);
                    break;
                }
                
                black_record(file_clients, file_transactions,
                file_ready_clients, client_data, transfer_to_client);
                fclose(file_clients);
                fclose(file_transactions);
                fclose(file_ready_clients);
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
