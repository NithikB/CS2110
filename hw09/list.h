/**
 * CS 2110 - Spring 2021 - Homework 9
 *
 * Do not modify this file!
 *
 * struct list.h
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

// Values to return from functions that return an int for success or failure
#define FAILURE 1
#define SUCCESS 0

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED(x) ((void)(x))

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the linked list and node types for use in
 * list.c. DO NOT MODIFY THESE STRUCT DEFINITIONS!
 */

struct user {
    char *name;
    int id;
};


struct node {
    struct node *next; // pointer to the next node
    struct user *data; // pointer to the node's string data
};


struct linked_list {
    struct node *head; // Head pointer either points to a node with data or if the struct list is empty NULL
    int size;          // Size of the struct list
};

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check list.c.                                  **
***************************************************/

/* Creating */
struct linked_list *create_list(void);

/* Adding */
int push_front(struct linked_list *list, char *name, int id);
int push_back(struct linked_list *list, char *name, int id);
int add_at_index(struct linked_list *list, int index, char *name, int id);

/* Querying */
int get(struct linked_list *list, int index, struct user **dataOut);
int contains(struct linked_list *list, struct user *data, struct user **dataOut);

/* Removing */
int pop_front(struct linked_list *list, struct user **dataOut);
int pop_back(struct linked_list *list, struct user **dataOut);
int remove_at_index(struct linked_list *list, struct user **dataOut, int index);
void empty_list(struct linked_list *list);

/* Mutating */
int replace_name_at_index(struct linked_list *list, int index, char *newName);

#endif
