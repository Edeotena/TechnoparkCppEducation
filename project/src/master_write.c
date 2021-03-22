#include "prototype_storage.h"

void master_write(const FILE *file_clients, data Client) {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           "1 Number account: ",
           "2 Client name: ",
           "3 Surname: ",
           "4 address client: ",
           "5 Client Telnum: ",
           "6 Client indebtedness: ",
           "7 Client credit limit: ",
           "8 Client cash payments: ");

    while (scanf("%d%20s%20s%30s%15s%lf%lf%lf",
                 &Client.number,
                 Client.name,
                 Client.surname,
                 Client.address,
                 Client.tel_number,
                 &Client.indebtedness,
                 &Client.credit_limit,
                 &Client.cash_payments) != -1) {
           fprintf(file_clients,
                   "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                   Client.number,
                   Client.name,
                   Client.surname,
                   Client.address,
                   Client.tel_number,
                   Client.indebtedness,
                   Client.credit_limit,
                   Client.cash_payments);

           printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
                  "1 Number account: ",
                  "2 Client name: ",
                  "3 Surname: ",
                  "4 address client: ",
                  "5 Client Telnum: ",
                  "6 Client indebtedness: ",
                  "7 Client credit limit: ",
                  "8 Client cash payments:");
    }
}
