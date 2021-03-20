#ifndef PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_
#define PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_

#include "utils.h"
#include "struct.h"

void master_write(FILE *file_clients, data client);
void transaction_write(FILE *file_transactions, data transfer_to_client);
void black_record(FILE *incoming_clients, FILE *incoming_transactions,
                  FILE *file_ready_clients, data client_data, data transfer_to_client);

#endif  //  PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_
