#include "tpqdb.h"

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email [MAX_DATA];
	char number [MAX_DATA];
};

struct Database{
	struct Address rows[MAX_ROWS];
};

struct Connection{
	FILE *file;
	struct Database *db;
};

struct Connection *Database_open(const char *filename, char mode){
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn)
		die("Memory Error");

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db)
		die("Memory Error");

	if(mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if(conn->file) {
			Database_load(conn);
		}
	}

	if(!conn->file) 
		die("Failed to open database file");

	return conn;
}

void die(const char *message){
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

void Address_print(struct Address *addr){
	printf("-> %-4d | %-25s | %-52s | %-12s\n", 
		addr->id, addr->name, addr->email, addr->number);
}

void Database_load(struct Connection *conn){
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1)
		die("Failed to load the database");
}

void Database_close(struct Connection *conn){
	if(conn) {
		if(conn->file) 
			fclose(conn->file);
		if(conn->db)
			free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn){
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1)
		die("Failed to write to the database");
	rc = fflush(conn->file);
	if(rc == -1)
		die("Cannot flush to the database");
}

void Database_create(struct Connection *conn){
	int i = 0;

	for(i = 0; i < MAX_ROWS; i++) {
		struct Address addr = {.id = i, .set = 0};
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email, const char *number){
	struct Address * addr = &conn->db->rows[id];
	if(addr->set)
		die("There is a record with that id already, delete it first");
	addr->set = 1;

	char *res = strncpy(addr->name, name, MAX_DATA);
	if(!res)
		die("Name copy failed");

	res = strncpy(addr->email, email, MAX_DATA);
	if(!res)
		die("Email copy failed");

	res = strncpy(addr->number, number, MAX_DATA);
	if(!res)
		die("Number copy failed");
}

void Database_get(struct Connection *conn, int id){
	struct Address *addr = &conn->db->rows[id];

	if(addr->set){
		Address_print(addr);
	} else {
		die("ID is not set");
	}
}

void Database_delete(struct Connection *conn, int id){
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn){
	int i = 0;
	struct Database *db = conn->db;

	for (int i = 0; i < MAX_ROWS; ++i) {
		struct Address *cur = &db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}