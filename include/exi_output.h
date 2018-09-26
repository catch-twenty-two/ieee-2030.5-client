#pragma once

// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @addtogroup output
    @{
*/

/** @brief Initialize Output object to output an EXI document

    @param o is a pointer to an Output object
    @param schema is a pointer to a Schema object
    @param buffer is the container for the EXI output
    @param size is the size of the buffer
*/
void exi_output_init (Output *o, const Schema *schema, char *buffer, int size);

/** @} */


