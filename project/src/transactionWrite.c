#include "prototype_storage.h"

void transactionWrite(FILE *incoming_ptr, Data transfer_to_client) {
    printf("%s\n%s\n",
           "1 Number account: ",
           "2 Client cash payments: ");

    while (scanf("%d %lf", &transfer_to_client.Number, &transfer_to_client.cash_payments) != -1) {
        fprintf(incoming_ptr, "%-3d%-6.2f\n", transfer_to_client.Number, transfer_to_client.cash_payments);
        printf("%s\n%s\n",
               "1 Number account:",
               "2 Client cash payments: ");
    }
}
