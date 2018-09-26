// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup parse Parse
    
    The parser converts an XML or EXI document into a C object (a typed data
    structure). The parser is schema based, which means that the document
    structure (the order and types of elements and values) is predefined by an
    XML schema. Successful parsing means that the document conforms to the
    schema, failure means that the document did not conform or that the
    document is incomplete. 

    The parser has a state and can stop and resume parsing at any point in the
    document, this means that a large document can be parsed in segments.
    This feature can be used to reduce the space needed to store documents and
    the segment of time used to process documents. For example, using a fixed
    length buffer to store document data means that the space required to store
    the document and the time used to process a document segment is constant.
    This can useful if there is a need share processing time between other
    tasks or if resources are constrained.

    The only requirement is that the buffer that contains the document is large
    enough to contain the largest XML or EXI token, the unit of information
    that advances the parser's state machine.
    @{
*/

typedef struct _Parser Parser;

/** @brief Parse an XML or EXI document.

    Use @ref parse_init or @ref exi_parse_init to initialize the Parser, then
    call parse_doc to parse the document. If the document is larger than the
    containing buffer, call @ref parser_data to get a pointer to the unparsed
    data, and @ref parser_rebuffer to update the parser once more data has been
    read. Repeat calls to @ref parse_doc until the data is completely read or
    the parse fails.
    @param p is a pointer to a Parser
    @param type is a pointer to the returned schema type of object
    @returns an object and type on success, NULL otherwise
*/
void *parse_doc (Parser *p, int *type);

/** @brief Is there an error in parsing the document? 

    Parsing can fail if the document is incomplete or there is an error in the
    document. This function checks for a parse error.
    @param p is a pointer to a Parser.
    @returns 1 if there is an error parsing the document, 0 otherwise.
*/
int parse_error (Parser *p);

/** @brief Print the current parse stack.
    @param p is a pointer to a Parser
*/
void print_parse_stack (Parser *p);

/** @brief Allocate a Parser. */
Parser *parser_new ();

/** @brief Free a Parser.
    @param p is a pointer to a Parser
*/
void parser_free (Parser *p);

/** @brief Return a pointer to a Parser's unparsed data
    @param p is a pointer to a Parser
*/
char *parser_data (Parser *p);

/** @brief Update the Parser's unparsed data pointer.
    @param p is a pointer to the Parser
    @param data is a pointer to the unparsed data
    @param length is the length of the unparsed data
*/
void parser_rebuffer (Parser *p, void *data, int length);

/** @} */

#include "schema.h"


