#pragma once

// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup output Output

    The output formater takes a C object that corresponds with a schema
    element declaration and converts it into an XML or EXI document. Just like
    the parser the formater can operate in segments, outputting only the
    portion of the document that will fit within the buffer.

    Most documents within a schema can be comfortably output to a fixed length
    buffer, however documents with unbounded elements (elements that can occur
    any number of times) can easily exceed these confines. The %List derived
    documents in IEEE 2030.5 are an example of documents that contain unbounded
    elements. According to the protocol these documents support a "paged"
    access method where a document is returned with only a portion of the
    entire set of elements.

    To support this paged access method with a fixed length buffer, it is
    useful to know how many elements fit in the buffer before the formater
    ran out of space. A call to @ref output_item_count will return the number
    of elements successfully written to a buffer at the specified element level
    before @ref output_doc returned. This count can be used to determine a
    limit of items that can be reliably output to a buffer.
    @{
*/

typedef struct _Output Output;

/** @brief Return the item count at the specified element level.

    This function is useful for determining the limit when outputting unbounded
    lists of objects to a fixed length buffer. The level is the level of
    the document at which the unbounded element occurs with 0 as the level of
    the root element, 1 as the level of the child of the root and so forth.
    @param o is a pointer to the Output object
    @param level is the stack level
    @returns the count of items at the specified level
*/
int output_item_count (Output *o, int level);

/** @brief Is the output complete?
    @returns 1 if the output is complete, 0 otherwise
*/
int output_complete (Output *o);

/** @brief Output an XML or EXI document to a buffer.

    The buffer is fixed in length so this function may need to be called more
    than once to output the complete document. Use @ref output_complete to
    determine if the output is complete.
    @param o is a pointer to an Output object
    @param base is a pointer to the object to output
    @param type is the type of object to output
    @returns the length of the output (complete or partial)
    
*/
int output_doc (Output *o, void *obj, int type);

/** @} */

extern Output output_global;


