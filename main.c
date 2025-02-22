#include <stdio.h>
#include "./libsql/include/libsql.h"
#include <math.h>

int main() {
    libsql_setup((libsql_config_t){0});

    libsql_database_t db = libsql_database_init((libsql_database_desc_t){
        .path = "local.db"
    });

    if (db.err) {
        fprintf(stderr, "Error: %s\n", libsql_error_message(db.err));
        return 1;
    }

    libsql_connection_t conn = libsql_database_connect(db);
    if (conn.err) {
        fprintf(stderr, "Connection error: %s\n", libsql_error_message(conn.err));
        return 1;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT);"
                      "INSERT INTO users (name) VALUES ('Alice');";

    libsql_batch_t batch = libsql_connection_batch(conn, sql);
    if (batch.err) {
        fprintf(stderr, "Batch error: %s\n", libsql_error_message(batch.err));
        return 1;
    }

    printf("Database operations completed successfully.\n");

    libsql_connection_deinit(conn);
    libsql_database_deinit(db);

    return 0;
}