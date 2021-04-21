// DO NOT MODIFY THIS FILE

/**
 * @brief Header file for global macros, structures and fields to be used by the
 * hw7 program.
 */
#ifndef HW7_H
#define HW7_H

#include <stddef.h>

#define UNUSED_PARAM(x) ((void) x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void) x)  // This macro is only used for turning off compiler errors initially

// Success and failure codes for function return
#define SUCCESS 1
#define FAILURE 0

// Sizes for different arrays
#define MAX_CLASS_SIZE  64
#define MAX_NAME_SIZE   10
#define MAX_ID_SIZE     10
#define MIN_ID_SIZE     4

//student struct
struct student {
    char    name[MAX_NAME_SIZE];
    int     age;
    double  gpa;
    char    id[MAX_ID_SIZE];
};

// Prototype hw7.c functions
int addStudent(const char *, int, double, const char *);
int updateStudentName(struct student, const char *);
int swapStudents(int, int);
int removeStudent(struct student);
int compareStudentID(struct student, struct student);
void sortStudents(void);

#endif
