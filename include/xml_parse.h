#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @addtogroup parse
    @{
*/

/** @brief Initialize the Parser to parse an XML document.

    @param p is a pointer to the Parser
    @param schema is a pointer to the Schema
    @param data is a pointer to the XML stream
*/
void parse_init (Parser *p, const Schema *schema, char *data);

/** @} */

#include "xml_token.h"

