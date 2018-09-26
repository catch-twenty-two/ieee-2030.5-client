#pragma once

// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup schema Schema

    Defines the Schema and SchemaElement data types, provides utility functions
    for Schema defined objects.
    @{
*/

enum XsType {XS_NULL, XS_STRING, XS_BOOLEAN, XS_HEX_BINARY, XS_ANY_URI,
	     XS_LONG, XS_INT, XS_SHORT, XS_BYTE, XS_ULONG, 
	     XS_UINT, XS_USHORT, XS_UBYTE};

#define xs_type(b, l) (((l)<<4)|(b))

typedef struct {
  union {
    unsigned short offset;
    unsigned short size;
  };
  union {
    unsigned short xs_type;
    unsigned short index;
  };
  unsigned char min, max, n;
  unsigned int bit : 5;
  unsigned int attribute : 1;
  unsigned int simple : 1;
  unsigned int unbounded : 1;
} SchemaElement;

typedef struct _Schema {
  const char *namespace;
  const char *schemaId;
  const int length;
  const SchemaElement *elements;
  const char * const *names;
  const uint16_t *ids;
} Schema;

int se_is_a (const SchemaElement *se, int base, const Schema *schema);

/** @brief Is a type derived from another type within a schema?
    @param type is the derived type
    @param base is a base type
    @param schema is a pointer to a Schema
    @returns 1 if type is derived from base, 0 otherwise
*/
int type_is_a (int type, int base, const Schema *schema);

/** @brief What is the size of an object of a given type?
    @param type is a schema type
    @param schema is a pointer to a Schema
    @returns the size of the schema typed object in bytes 
*/
int object_size (int type, const Schema *schema);

/** @brief Return a string representation of a type.
    @param type is a schema type
    @param schema is a pointer to a Schema
    @returns the type name as a string
*/
const char *type_name (int type, const Schema *schema);

/** @brief Free an object's elements without freeing the object container.
    @param obj is a pointer to a schema typed object 
    @param type is the type of the object
    @param schema is a pointer to the Schema
*/
void free_object_elements (void *obj, int type, const Schema *schema);

/** @brief Free an object's elements and the container.
    @param obj is a pointer to a schema typed object 
    @param type is the type of the object
    @param schema is a pointer to the Schema
*/
void free_object (void *obj, int type, const Schema *schema);

/** @brief Replace one object for another.

    Free the elements of the destination object and copy the source object to
    the same location. Free the source object container.
    @param dest is the destination object
    @param src is the source object
    @param type is the schema type of the objects
    @param schema is a pointer to the Schema
 */
void replace_object (void *dest, void *src, int type, const Schema *schema);

/** @} */


