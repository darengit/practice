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
}

struct Connection {
	FILE *file;
	struct Database *db;
};

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
	conn->db = {0};
	for(int i=0; i<MAX_ROWS; ++i) {
		conn->db->rows[i]->id = i;
	}
}

void database_set(struct Connection *conn, int id, const char *name, const char *email) {

}
