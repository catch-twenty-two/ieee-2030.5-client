#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup uri Uri

    Provides a parser for Uniform Resource Identifiers (URIs 
    <a href="https://www.ietf.org/rfc/rfc3986.txt">RFC 3986</a>) 
    @{
*/

/** Parsed URI representation */
typedef struct {
  char *scheme; ///< is the URI scheme
  char *name; ///< is the host name (if any)
  char *end; ///< is a pointer to the end of the host name
  char *path; ///< is the URI path
  char *query; ///< is the URI query
  Address *host; ///< is pointer to the URI host
  int port; ///< is the URI port
} Uri;

/** A buffered URI (abstract type) */
typedef struct {
  Uri uri;
  Address host;
  char buffer[];
} UriBuffered;

/** A buffered URI instance type */
typedef struct {
  Uri uri;
  Address host;
  char buffer[128];
} Uri128;

/** @brief Parse a URI.
    @param buf is a pointer to a buffered Uri
    @param href is a pointer to URI string
    @param length is the maximum length of the URI string
 */
int uri_parse (void *buf, const char *href, int length);

int write_uri (char *buffer, Uri *uri);

/** @} */


