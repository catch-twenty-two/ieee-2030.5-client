#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup util Utility

    Provides base layer idiomatic C macros and functions. 
    @{
*/

#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define min(x, y) (((x) < (y))? x : y)
#define max(x, y) (((x) < (y))? y : x)
#define ok(x) if (!(x)) return NULL
#define ok_v(x, value) if (!(x)) return value
#define streq(a,b) (strcmp (a, b) == 0)
#define in_range(x, a, b) ((x) >= a && (x) <= b)
#define alpha(c) (in_range (c, 'a', 'z') || in_range (c, 'A', 'Z'))
#define digit(c) in_range (c, '0', '9')
#define ws(c) (c == '\n' || c == ' ' || c == '\t' || c == '\r')
#define only(x) (*trim (x) == '\0')
#define struct_field(type, any, name) ((type *)any)->name
#define type_alloc(type) calloc (1, sizeof (type))
#define number_q(x, data) (digit (*(data))? number (x, data) : data)

int bit_count (uint32_t x);
int string_index (const char *s, const char * const *ss, int n);
char *trim (char *data);
char *to_lower (char *s);
char *number (int *x, char *data);
char *number64 (uint64_t *x, char *data);

/** @} */

