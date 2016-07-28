#ifndef TPQDB_H
#define TPQDB_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
 
#define MAX_DATA 512
#define MAX_ROWS 1000

struct Address;
struct Database;
struct Connection;
struct Connection *Database_open(const char *filename, char mode);

void die(const char *message);
void Address_print(struct Address *addr);
void Database_load(struct Connection *conn);
void Database_close(struct Connection *conn);
void Database_write(struct Connection *conn);
void Database_create(struct Connection *conn);
void Database_set(struct Connection *conn, int id, const char *name, const char *email, const char *number);
void Database_get(struct Connection *conn, int id);
void Database_delete(struct Connection *conn, int id);
void Database_list(struct Connection *conn);

#endif