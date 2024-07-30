#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VAL 200
#define TABLE_SIZE 10

typedef struct student {
    int id;
    char name[MAX_VAL];
    struct student* next;
} student;

struct student* hash_table[TABLE_SIZE];

void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

int hash(int id) {
    return id % TABLE_SIZE;
}

bool insert_into_table(student* s) {
    if (s == NULL) return false;

    int idx = hash(s->id);
    if (hash_table[idx] == NULL) {
        hash_table[idx] = s;
    } else {
        student* temp = hash_table[idx];
        s->next = temp;
        hash_table[idx] = s;
    }
    return true;
}

student* hash_table_lookup(int id) {
    int idx = hash(id);
    if (hash_table[idx] == NULL) {
        return NULL;
    } else {
        student* temp = hash_table[idx];
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }
        return temp;
    }
}

bool hash_table_delete(int id) {
    int idx = hash(id);
    if (hash_table[idx] == NULL) {
        return false;
    } else {
        student* temp = hash_table[idx];
        student* prev = NULL;
        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL) return false;

        if (prev == NULL) {
            hash_table[idx] = temp->next;
        } else {
            prev->next = temp->next;
        }
        free(temp);
        return true;
    }
}

void print_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        student* temp = hash_table[i];
        printf("Bucket %d: ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->id);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    init_table();

    student Ashok = { .id = 101, .name = "Ashok" };
    student Ram = { .id = 102, .name = "Ram" };
    student Pavan = { .id = 103, .name = "Pavan" };

    insert_into_table(&Ashok);
    insert_into_table(&Ram);
    insert_into_table(&Pavan);

    print_table(); 

    student* found = hash_table_lookup(101);
    if (found != NULL) {
        printf("Found student with id %d: %s\n", found->id, found->name);
    } else {
        printf("Student not found\n");
    }

    hash_table_delete(101);
    print_table(); 

    return 0;
}