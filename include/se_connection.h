#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>
#include "http.h"

/** @defgroup se_connection SeConnection
    @ingroup http_connection

    An SeConnection extends an HttpConnection and provides support for the 
    IEEE 2030.5 media types "application/sep+xml" and "application/sep-exi". 
    @{
*/

#define SE_CONNECTION EVENT_NEW

#define SE_ERROR (HTTP_RESPONSE+1)
#define SE_INCOMPLETE (HTTP_RESPONSE+2)

enum ResponseType {EventReceived=1, EventStarted, EventCompleted,
		   EventOptOut, EventOptIn, EventCanceled, EventSuperseded,
		   EventPartialOptOut, EventPartialOptIn, EventCompleteOptOut,
		   EventAcknowledge, EventNoDisplay, EventAbortedServer,
		   EventAbortedProgram,
		   EventInapplicable=252, EventInvalid, EventExpired};

typedef struct _SeConnection SeConnection;
enum SeMediaType {SE_EXI, SE_XML, APPLICATION_XML};

#define se_post(conn, data, type, href)		\
  se_send (conn, data, type, href, HTTP_POST)
#define se_put(conn, data, type, href)		\
  se_send (conn, data, type, href, HTTP_PUT)
#define link_send(conn, obj, data, type, method)			\
  if ((data) && se_exists (obj, type##Link))				\
    se_send (conn, data, SE_##type, (obj)->type##Link.href, method)
#define link_put(conn, obj, data, type)		\
  link_send (conn, obj, data, type, HTTP_PUT)
#define link_post(conn, obj, data, type)		\
  link_send (conn, obj, data, type, HTTP_POST)

/** @brief PUT or POST an IEEE 2030.5 object to a server.

    Use the conn parameter to send the object if the host address matches the 
    server specified in the the href parameter, otherwise attempt a new
    connection and send the object on that connection. 
    @param conn is a pointer to an SeConnection
    @param obj is a pointer to an IEEE 2030.5 object
    @param type is the schema type of the object
    @param href is a URI string, the location to send the object to
    @param method is the HTTP method to use, either HTTP_POST or HTTP_PUT
*/
void *se_send (void *conn, void *obj, int type, char *href, int method);

/** @brief Initialize a Response to an Event.

    @param resp is a pointer to an SE_Response_t object or dervied type.
    @param ev is a pointer to an SE_Event_t object
    @param lfdi is the lfdi of an EndDevice.
    @param status updates the event with a ResponseType
*/
void se_response (void *resp, SE_Event_t *ev, char *lfdi, int status);

/** @brief Get the SFDI of the server or client.
    
    When a secure connection is established, certificates are exchanged between
    the client and server. The SFDI is a hash reduction of a device's
    certificate. Use this function to  
*/
uint64_t *se_sfdi (void *conn);

/** @brief Return the negotiated content type.
    @param conn is pointer to an SeConnection
    @param type is pointer to the returned content type
    @returns the negotiated content type as a string and integer
 */
const char *se_content_type (void *conn, int *type);

/** @brief Returns the message body as an IEEE 2030.5 object (if any).

    If @ref se_receive returns an HTTP method or an HTTP response, this
    function returns the HTTP message body as an IEEE 2030.5 object if any
    were present or NULL to indicate the message body was empty. Caller is
    responsible for freeing the object with @ref free_se_object.
    @param conn is a pointer to an SeConnection
    @param type is a pointer to the returned type of IEEE 2030.5 object
    @returns an IEEE 2030.5 object present in the HTTP message body (if any),
    otherwise NULL
*/
void *se_body (void *conn, int *type);

/** @brief Free the IEEE 2030.5 object parsed from the HTTP message
    body (if any).
    @param conn is a pointer to an SeConnection
*/ 
void free_se_body (void *conn);

/** @brief Receive an IEEE 2030.5 message.
    @param conn is a pointer to a SeConnection
    @returns the HTTP method on success (see @ref http_receive)

    SE_INCOMPLETE to indicate an incomplete message

    SE_ERROR to indicate an error in the message
*/
int se_receive (void *conn);

/** @brief Connect to an IEEE 2030.5 server.

    Only one connection is maintained per server address/port, so this function
    first searches a list of existing connection for a matching Address, before
    creating a new connection.
    @param addr is a pointer to Address of the server
    @param secure is 1 for a encrypted TLS connection, 0 for an unencrypted
    TCP connection
    @returns a pointer to an SeConnection
*/
void *se_connect (Address *addr, int secure);

/** @brief Connect to an IEEE 2030.5 server using a Uri parameter.

    The same as @ref se_connect, but uses a Uri as a parameter. The URI scheme
    determines whether to attempt a secure connection, "https" for an encrypted
    TLS connection, "http" for an unencrypted TCP connection.
    @param uri is a Uri with a host and a HTTP scheme
    @returns a pointer to an SeConnection
*/
void *se_connect_uri (Uri *uri);

/** @brief Accept a connection request from an IEEE 2030.5 client.
    @param a is a pointer to an Acceptor
    @param secure is 1 for an encrypted TLS connection, 0 for an unencypted
    TCP connection
    @returns a pointer to a SeConnection.
*/
void *se_accept (Acceptor *a, int secure);

void *find_conn (Address *addr);
void *get_conn (Address *addr);

/** @} */


