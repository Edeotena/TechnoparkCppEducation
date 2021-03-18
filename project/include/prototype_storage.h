#ifndef PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_
#define PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_

#include "utils.h"

void masterWrite(FILE *incoming_ptr, Data Client);
void transactionWrite(FILE *incoming_ptr, Data transfer_to_client);
void blackRecord(
    FILE *incoming_clients,
    FILE *incoming_transfers,
    FILE *blackrecord,
    Data client_data, Data transfer_to_client);

#endif  //  PROJECT_INCLUDE_PROTOTYPE_STORAGE_H_
