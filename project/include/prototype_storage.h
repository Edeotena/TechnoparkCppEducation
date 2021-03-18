#ifndef PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_
#define PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_

#include "utils.h"
#include "struct.h"

void master_write(FILE *file_to_keep_clients, data client);
void transaction_write(FILE *file_to_keep_transfers, data transfer_to_client);
void black_record(FILE *incoming_clients, FILE *incoming_transfers,
                  FILE *file_to_keep_maked_transactions, data client_data, data transfer_to_client);

#endif  //  PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_
