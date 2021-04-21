
#include <stdio.h>
#include <check.h>
#include <stddef.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RETURN_ERROR_VALUE -100

// Suites
extern Suite *hw7_suite(void);
extern Suite *my_string_suite(void);

#define tcase_hack(suite, setup_fixture, teardown_fixture, func)        \
    {                                                                   \
        TCase *tc = tcase_create(STRINGIFY(func));                      \
        tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
        tcase_add_test(tc, func);                                       \
        suite_add_tcase(s, tc);                                         \
    }

/******************************************************************************/
/**************************** hw7 Header Info *********************************/
/******************************************************************************/

#define UNUSED_PARAM(x) ((void)x) // This macro is only used for turning off compiler errors initially
#define UNUSED_FUNC(x) ((void)x)  // This macro is only used for turning off compiler errors initially

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
extern struct student class[MAX_CLASS_SIZE];
extern int size;

// Prototype hw7.c functions
int addStudent(const char *, int, double, const char *);
int updateStudentName(struct student, const char *);
int swapStudents(int, int);
int removeStudent(struct student);
int compareStudentID(struct student, struct student);
void sortStudents(void);

// Function prototypes for my_string.c
size_t my_strlen(const char *s);
int my_strncmp(const char *s1, const char *s2, size_t n);
char *my_strncpy(char *dest, const char *src, size_t n);
