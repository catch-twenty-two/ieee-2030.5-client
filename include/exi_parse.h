#pragma once

// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @addtogroup parse
    @{
*/

/** @brief Initialize the Parser to parse an EXI document.

    @param p is a pointer to a Parser object
    @param schema is the schema to use
    @param data is the beginning of the EXI stream
    @param length is the length of the stream in bytes
*/
void exi_parse_init (Parser *p, const Schema *schema, char *data, int length);

/** @} */


