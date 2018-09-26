#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup http_connection HttpConnection
    @ingroup connection

    An HttpConnection extends a Connection and provides a client or server
    interface to an HTTP message stream
    (<a href="https://tools.ietf.org/html/rfc7230">RFC 7230</a>,
    <a href="https://tools.ietf.org/html/rfc7231">RFC 7231</a>).

    In HTTP client/server roles are fixed through the lifetime of the
    connection and are determined by whether a host requested a connection
    (a client) or accepted a connection request (a server). Clients submit
    requests (GET, PUT, POST, DELETE) and process responses. Servers process
    client requests and respond with a status code and possibly a message body.

    @{
*/

typedef struct _HttpConnection HttpConnection;

enum HttpMethod {HTTP_GET, HTTP_PUT, HTTP_POST, HTTP_DELETE, HTTP_HEAD,
		 HTTP_UNKNOWN, HTTP_RESPONSE, HTTP_NONE, HTTP_ERROR};

/** @brief An HTTP request */
typedef struct _HttpRequest {
  struct _HttpRequest *next;
  void *context;
  uint8_t method; char uri[];
} HttpRequest;

/** @brief Write a POST request to a buffer and queue the request.

    See @ref http_send.
*/
#define http_post(conn, buffer, uri)		\
  http_send (conn, buffer, uri, HTTP_POST)
/** @brief Write a PUT request to a buffer and queue the request.

    See @ref http_send.
*/
#define http_put(conn, buffer, uri)			\
  http_send (conn, buffer, uri, HTTP_PUT)

/** @brief Initialize an HTTP connection.
    @param conn is a pointer to an HttpConnection
    @param client is non-zero for a client HttpConnection
    @param accept is a string listing acceptable media ranges (Accept header)
    @param media is the Content-Type for PUT and POST
*/
void http_init (void *conn, int client, const char *accept, const char *media);

/** @brief Flush queued data to an HTTP connection.
    @param conn is a pointer to an HttpConnection
*/
void http_flush (void *conn);

/** @brief Write data to an HTTP connection immediately if possible or queue
    for later.

    Use http_flush to flush queued data.
    @param conn is a pointer to an HttpConnection
    @param data is an array of bytes
    @param length is the length of data
*/
void http_write (void *conn, void *data, int length);

/** @brief Perform a GET request immediately if possible or queue for later.
    @param conn is a pointer to an HttpConnection
    @param uri is the request URI
*/
void http_get (void *conn, const char *uri);

/** @brief Perform a DELETE request immediately if possible or queue for later.
    @param conn is a pointer to an HttpConnection
    @param uri is the request URI
*/
void http_delete (void *conn, const char *uri);

/** @brief Write a PUT or POST request message to a buffer and queue the
    request.
    
    Use the length returned as a location for the request content. Use the
    function @ref set_content_length to update the Content-Length. Finally, use
    the function @ref http_write to complete the request.
    @param conn is a pointer to an HttpConnection
    @param buffer is a buffer large enough for the request
    @param uri is the request URI
    @param method is either HTTP_PUT or HTTP_POST
    @returns the length of the message
*/
int http_send (void *conn, char *buffer, const char *uri, int method);

/** @brief Write an HTTP status line to buffer.
    @param buffer is the storage for the status line
    @param status is the status code
    @param reason is a string explaining the status
    @returns the length of the status line
*/
int http_status_line (char *buffer, int status, const char *reason);

/** @brief Write HTTP content headers to a buffer.
    @param buffer is the storage for the headers
    @param media is the Content-Type
    @param length is the Content-Length
    @returns the length of the headers
*/
int http_content (char *buffer, const char *media, int length);

/** @brief Update the Content-Length header.

    The Content-Length header should have a enough blank spaces for the length.
    This function overwrites the blank spaces with the length provided.
    @param buffer contains a Content-Length header
    @param length is the value to be set for the Content-Length
*/
void set_content_length (char *buffer, int length);

/** @brief Close the HTTP connection and return queued requests.
    @param conn is a pointer to an HttpConnection
    @returns an HttpRequest linked list
*/
HttpRequest *http_queued (void *conn);

/** @brief Close the HTTP connection and free queued requests/data.
    @param conn is a pointer to an HttpConnection
*/
void http_close (void *conn);

/** @brief Send HTTP response, status 405 (Method Not Allowed).
    @param conn is a pointer to an HttpConnection
    @param allow is a list of allowed methods (Allow header)
*/
void http_allow (void *conn, const char *allow);

/** @brief Send an HTTP response with status.
    @param conn is a pointer to an HttpConnection
    @param status is the status code to return
*/
void http_respond (void *conn, int status);

/** @brief Send an HTTP response with status 201 (Created).
    @param conn is a pointer to an HttpConnection
    @param uri is the value to be returned in the Location header
*/
void http_created (void *conn, const char *uri);

/** @brief Send HTTP response with status 204 (No Content).
    @param conn is a pointer to an HttpConnection
    @param uri is the value to be returned in the Location header
*/
void http_no_content (void *conn, const char *uri);

/** @brief Send HTTP response with status and close connection.
    @param conn is a pointer to an HttpConnection
    @param status is the status code to return 
*/
void http_error (void *conn, int status);

/** @brief Receive an HTTP request/response.
    @param conn is a pointer to an HttpConnection
    @returns one of HTTP_GET, HTTP_PUT, HTTP_POST, HTTP_DELETE, HTTP_HEAD if
    an HTTP request is succesfully received (server).
    
    HTTP_UNKNOWN for a request with an method other than GET, PUT, POST, DELETE,
    or HEAD (server).

    HTTP_RESPONSE for an HTTP response (client)

    HTTP_NONE for an incomplete message (client, server), @ref http_receive
    can called again when more data is available.

    HTTP_ERROR for an incorrect message (client, server)
*/
int http_receive (void *conn);

/** @brief Does the HTTP message have a body?
    @returns 1 if the message has a body, 0 otherwise
*/
int http_body (void *conn);

/** @brief Return data from the message body.

    Call again until all the data has been returned. @ref http_complete

    @param conn is a pointer to an HttpConnection
    @param length is a pointer to the length of the data returned
    @returns a pointer to the data from the message body
*/
char *http_data (void *conn, int *length);

/** @brief Clear data up to the pointer and read more data from the connection.

    An HttpConnection uses a fixed length buffer to retrieve data, this
    function clears data and moves the remainder of the data to the beginning
    of the buffer so more data can be read.
    @param conn is a pointer to an HttpConnection
    @param data is a pointer to 
*/
void http_rebuffer (void *conn, char *data);

/** @brief Is data from the message body complete?
    @param conn is a pointer to an HttpConnection
    @returns 1 is message is complete, 0 otherwise
*/
int http_complete (void *conn);

/** @brief Get status for HTTP response.

    Valid when @ref http_receive returns HTTP_RESPONSE.
    @param conn is a pointer to an HttpConnection
    @returns the status
*/
int http_status (void *conn);

/** @brief Return the method associated with the HTTP response.
    @param conn is a pointer to an HttpConnection
    @returns the HTTP method
*/
int http_method (void *conn);

/** @brief Get the path for an HTTP request.
    @param conn is a pointer to an HttpConnection
    @returns the path
*/
char *http_path (void *conn);

/** @brief Get the query for an HTTP request.
    @param conn is a pointer to an HttpConnection
    @returns the query
*/
char *http_query (void *conn);

/** @brief Get the Accept header value (media range).
    @param conn is a pointer to an HttpConnection
    @returns the media range
*/
char *http_range (void *conn);

/** @brief Is the HTTP connection a client?
    @param conn is a pointer to an HttpConnection
    @returns 1 for a client side connection, 0 for a server side connection
 */
int http_client (void *conn);

/** @brief Get the Location header value
    @param conn is a pointer to an HttpConnection
    @returns the value of the Location header or NULL if none exists
*/
char *http_location (void *conn);

/** @brief Parse an HTTP URI using connection parameters.
    @param buf is a pointer to a buffered Uri
    @param conn is a pointer to an HttpConnection
    @param href is a pointer to the URI string
    @param length is maximmum length of the URI string
    @returns 1 if href is a valid URI, 0 otherwise
*/
int http_parse_uri (void *buf, void *conn, const char *href, int length);

/** @brief Print the HTTP request/response on stdout
    @param conn is a pointer to an HttpConnection
    @param enable is 1 to enable debug output, 0 to disable
*/
void http_debug (void *conn, int enable);

/** @brief Set the context for an HTTP request.

    Sets the context for the last queued HTTP request. This value can later be
    retrieved by @ref http_context when a response is received.
    @param conn is a pointer to an HttpConnection
    @param context is value to associate with the last request
*/
void set_request_context (void *conn, void *context);

/** @brief Get the context for an HTTP response.

    Use @ref set_request_context to set the value of the context for a request,
    this value can then be retrieved using this function once a response has
    been successfully received. 
    @param conn is a pointer to an HttpConnection
    @returns the value associated with the request
*/
void *http_context (void *conn);

/** @} */


