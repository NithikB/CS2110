/**
 * @file my_string.c
 * @author YOUR NAME HERE
 * @brief Your implementation of these famous 3 string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2021-03-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"

/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
    int size_t = 0;
    while(*(s+size_t) != '\0') {
        size_t++;
    }
    return size_t;
}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    int size_t = 0;
    while(*(s1+size_t) == *(s2+size_t) && *(s1+size_t) != '\0' && *(s2+size_t) != '\0' && size_t < (int)n) {
        size_t++;
    }
    return *(s1+size_t) - *(s2+size_t);
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{

    int size_t = 0;
    while(*(src+size_t) != '\0' && size_t != (int)n) {
        *(dest+size_t) = *(src+size_t);
        size_t++;
    }

    while(size_t < (int)n) {
        *(dest+size_t) = '\0';
        size_t++;
    }

    return dest;
}
