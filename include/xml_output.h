/** @addtogroup output
    @{
*/

/** @brief Initialize an Output object to output an XML document.

    @param o is a pointer to an Output object
    @param schema is a pointer to a Schema object
    @param buffer is a container for the XML document
    @param size is the size of the buffer
*/
void output_init (Output *o, const Schema *schema, char *buffer, int size);

/** @} */


