#include "prototype_storage.h"

void transaction_write(FILE *file_to_keep_transfers, data transfer_to_client) {
    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");

    while (scanf("%d %lf", &transfer_to_client.number, &transfer_to_client.cash_payments) != -1) {
           fprintf(file_to_keep_transfers,
                   "%-3d%-6.2f\n",
                   transfer_to_client.number,
                   transfer_to_client.cash_payments);
           printf("%s\n%s\n",
                  "1 Number account:",
                  "2 Client cash payments: ");
    }
}
