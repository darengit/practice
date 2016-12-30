#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 64
#define MAX_ROWS 1024

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection {
	FILE *file;
	struct Database *db;
};


// make die take args similar to printf
void die(const char *message) {
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

void address_print(struct Address *addr) {
	printf("%d %d %s %s\n", addr->id, addr->set, addr->name, addr->email);
}

void database_load(struct Connection *conn) {
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc!=1)
		die("failed to load database");
}

struct Connection *database_open(const char *filename, char mode) {
	struct Connection *conn = (struct Connection *)malloc(sizeof(struct Connection));
	if(!conn) die("memory error");

	conn->db = (struct Database *)malloc(sizeof(struct Database));
	if(!conn->db) die("memory error");

	conn->file = fopen(filename, (mode=='c')?"W":"r+");
	if(conn->file) database_load(conn);
	if(!conn->file) die("failed to open the file");

	return conn;
}

void database_close(struct Connection *conn) {
	if(conn) {
		if(conn->file) free(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void database_write(struct Connection *conn) {
	rewind(conn->file);
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc!=1) die("failed to write database");

	rc = fflush(conn->file);
	if(rc==-1) die("cannot flush database");
}

void database_create(struct Connection *conn) {
	for(int i=0; i<MAX_ROWS; ++i) {
		struct Address addr = {0};
		addr.id=i;
		conn->db->rows[i]=addr;
		//conn->db->rows[i]->id = i;
	}
}

void database_set(struct Connection *conn, int id, const char *name, const char *email) {
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("already set, delete it first");

	char *res = strncpy(addr->name, name, MAX_DATA-1);
	if(!res) die("name copy failed");
	addr->name[MAX_DATA-1] = '\0';

	res = strncpy(addr->email, email, MAX_DATA-1);
	if(!res) die("email copy failed");
	addr->email[MAX_DATA-1] = '\0';

	addr->set = 1;
}

void database_get(struct Connection *conn, int id) {
	struct Address *addr = &conn->db->rows[id];
	if(addr->set)
		address_print(addr);
	else
		die("id is not set");
}

void database_delete(struct Connection *conn, int id) {
	struct Address addr = {.id=id, .set=0};
	conn->db->rows[id] = addr;
}

void database_list(struct Connection *conn) {
	for(int i=0; i<MAX_ROWS; ++i) {
		struct Address *addr = &conn->db->rows[i];
		if(addr->set)
			address_print(addr);
	}
}

int main(int argc, char *argv[]) {
	if(argc < 3)
		die("usage: a.out file action additional_params");

	char *filename = argv[1];

	char action = argv[2][0];
	struct Connection *conn = database_open(filename, action);
	int id=0;

	if(argc > 3) id = atoi(argv[3]);
	if(id >= MAX_ROWS) die("record id too high");

	switch (action) {
		case 'c':
			database_create(conn);
			database_write(conn);
			break;
		case 'g':
			if(argc!=4) die("need an id for database_get()");
			database_get(conn,id);
			break;
		case 's':
			if(argc!=6) die("need id, name, email for database_set()");
			database_set(conn,id,argv[4],argv[5]);
			database_write(conn);
			break;
		case 'd':
			if(argc!=4) die("need id to delete");
			database_delete(conn,id);
			database_write(conn);
			break;
		case 'l':
			database_list(conn);
			break;
		default:
			die("invalid action: c=create, g=get, s=set, d=delete, l=list");
	}

	database_close(conn);
	return 0;
}
