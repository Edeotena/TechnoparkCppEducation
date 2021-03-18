#include "prototype_storage.h"

void black_record(FILE *incoming_clients, FILE *incoming_transfers,
                 FILE *file_to_keep_maked_transactions, data client_data, data transfer_to_client) {
    while (fscanf(incoming_clients,
                  "%d%20s%20s%30s%15s%lf%lf%lf",
                  &client_data.number,
                  client_data.name,
                  client_data.surname,
                  client_data.address,
                  client_data.tel_number,
                  &client_data.indebtedness,
                  &client_data.credit_limit,
                  &client_data.cash_payments) != -1) {
        while (fscanf(incoming_transfers,
                      "%d %lf",
                      &transfer_to_client.number,
                      &transfer_to_client.cash_payments) != -1) {
            if (client_data.number == transfer_to_client.number && transfer_to_client.cash_payments != 0) {
                client_data.credit_limit += transfer_to_client.cash_payments;
            }
        }

        fprintf(file_to_keep_maked_transactions,
                "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                client_data.number,
                client_data.name,
                client_data.surname,
                client_data.address,
                client_data.tel_number,
                client_data.indebtedness,
                client_data.credit_limit,
                client_data.cash_payments);
        rewind(incoming_transfers);
    }
}
