#pragma once

#include <stdint.h>

#include "list.h"
#include "schema.h"
#include "output.h"

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup se_object IEEE 2030.5 Schema

    Provides utility functions for IEEE 2030.5 schema defined objects.
    @ingroup schema
    @{
*/

/** @brief Generate MRID for IEEE 2030.5 identified object.

    MRID is a 16 byte number based upon a random number, a global count, and a
    manufactuer PEN.
    @param mrid is pointer to an array of 16 bytes
*/
void mrid_gen (uint8_t *mrid);

typedef struct {
  unsigned short offset;
  short type;
} Key;

typedef struct {
  unsigned short id;
  unsigned short base;
  unsigned short offset;
  unsigned short type;
  Key key[3];
} ListInfo;

/** @brief Get the list field of a IEEE 2030.5 list type object
    @param obj is a pointer to an IEEE 2030.5 list type object
    @param info is a pointer to the ListInfo for the list type
    @returns a pointer to the list field of the object
*/
#define se_list_field(obj, info) (List **)((obj)+(info)->offset)

/** @brief Is an IEEE 2030.5 object type derived from a base type?
    
    Queries the schema to determine if an object of certain type is derived
    from a base object. This is useful for dealing with certain classes of
    objects (e.g se_type_is_a (type, SE_Resource), or 
    se_type_is_a (type, SE_Event)).
    @param type is the type of the derived object
    @param base is the type of the base object
    @returns 1 if object is derived from base, 0 otherwise
*/
#define se_type_is_a(type, base) type_is_a (type, base, &se_schema)

/** @brief Is an IEEE 2030.5 object type a List derived type?
    @returns 1 if the type is a SubscribableList or a List type, 0 otherwise
*/
#define se_list(type) (se_type_is_a (type, SE_SubscribableList) \
		       || se_type_is_a (type, SE_List))

/** @brief Is an IEEE 2030.5 object type an Event derived type?
    @returns 1 if the type is a Event type, 0 otherwise
*/
#define se_event(type) se_type_is_a (type, SE_Event)

/** @brief Return the size of an IEEE 2030.5 object given its type.

    Queries the schema to determine the size of a object given its type.
    @param type is the type of the IEEE 2030.5 object
    @returns the size of the object in bytes
*/
#define se_object_size(type) object_size (type, &se_schema)

/** @brief Free an IEEE 2030.5 object.
    @param obj is an IEEE 2030.5 object
    @param type is the type of the o
 */
#define free_se_object(obj, type) free_object (obj, type, &se_schema)

/** @brief Replace an IEEE 2030.5 object with another of the same type.

    Frees the elements of the destination object and copies the source object
    to the same location, replacing one object with another. Also frees the
    source object container.
*/
#define replace_se_object(dest, src, type)				\
  replace_object (dest, src, type, &se_schema)

/** @brief Get the ListInfo structure for the given schema type.

    The type should be one the IEEE 2030.5 list types for a non-NULL result.
    @param type is an SE_ type name (e.g. SE_EndDeviceList)
    @returns a pointer to the ListInfo structure for the given type or
    NULL if the type is not a list type.
*/
ListInfo *find_list_info (unsigned short type);

/** @brief Compare the keys of two IEEE 2030.5 objects using the provided list
    ordering.

    @param a is an IEEE 2030.5 object
    @param b is an IEEE 2030.5 object
    @param info is a pointer to a ListInfo structure
    @returns a result < 0 if a comes before b, a result > 0 if a comes after b,
    and a result == 0 if a and b can occupy the same position 
*/
int compare_keys (void *a, void *b, ListInfo *info);

/** @brief Insert an IEEE 2030.5 object into a sorted list.

    Comparison is based upon the ListInfo given.
    @param list is a list of objects of a uniform type given by info->type
    @param n is a pointer to the List container of the object to be inserted.
    @param info is a pointer to the ListInfo upon which the comparison is made.
    @returns the sorted list with n inserted
*/
void *insert_se_object (List *list, List *n, ListInfo *info);

/** @brief Initialize an Output object to output an XML or EXI document.
    @param o is a pointer to an Output object
    @param buffer is a container for the document
    @param size is the size of the container
    @param xml is 1 for an XML document, 0 for an EXI document
*/
void se_output_init (Output *o, char *buffer, int size, int xml);

/** @brief Print an IEEE 2030.5 object as an XML document
    @param obj is a pointer to the object
    @param type is the object type
*/
void print_se_object (void *obj, int type);

/** @} */

extern int pen_id; //< set to manufacturer PEN
extern Schema se_schema;

