#include "blackRecord.h"
#include "transactionWrite.h"
#include "masterWrite.h"

int main(void) {
    int choice = 0;
    FILE *ptr, *ptr_2 , *blackrecord;
    Data client_data = {0}, transfer = {0};

    printf("%s\n%s\n%s\n%s\n\n",
        "please enter action",
        "1 enter data client:",
        "2 enter data transaction:",
        "3 update base");

    while (scanf("%d", &choice) != -1) {
        switch (choice) {
        case 1:
            ptr = fopen("record.dat", "r+");
            if (ptr == NULL) {
                puts("Not acess");
            } else {
                masterWrite(ptr, client_data);
                fclose(ptr);
            }
        break;

        case 2:
            ptr = fopen(filename, "r+");
            if (ptr == NULL) {
                puts("Not acess");
            } else {
                transactionWrite(ptr, transfer);
                fclose(ptr);
            }
            break;

        case 3:
            ptr = fopen("record.dat", "r");
            ptr_2 = fopen(filename, "r");
            blackrecord = fopen("blackrecord.dat", "w");
            if (ptr == NULL || ptr_2 == NULL) {
                puts("exit");
            } else {
                blackRecord(ptr, ptr_2, blackrecord, client_data, transfer);
                fclose(ptr);
                fclose(ptr_2);
                fclose(blackrecord);
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

    return 0;
}
