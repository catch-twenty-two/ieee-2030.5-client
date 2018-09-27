#pragma once

#include "platform.h"

// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup dnssd_client Service Discovery

    Provides an implementation of DNS-Based Service Discovery
    (<a href="https://tools.ietf.org/html/rfc6763">RFC 6763</a>).
    @{
*/

typedef struct _Service Service;

/** @brief Initialize a DNS-SD query.

    @param packet is a container for the DNS-SD query
    @returns the destination for the first question within the packet
*/
char *dnssd_query (char *packet);

/** @brief Add a question to a DNS-SD query.
    @param dest is the destination of the question within a DNS-SD packet
    @param name is a pointer to a name in the DNS counted label format
    @param type is the type of resource record that pertains to the question
    @param unicast is the value of the QU bit
    @returns the destination of the next question within the query
*/
char *dnssd_question (char *dest, char *name, int type, int unicast);

/** @brief Receive DNS-SD packets from a UdpPort.
    
    Receive and process packets from a UdpPort and return the discovered
    services.
    @param port is a pointer to a UdpPort
    @param Service is a pointer the first discovered Service
 */
Service *dnssd_receive (UdpPort *port);

/** @brief Return the next Service given a pointer to a discovered Service. 
    @param s is a pointer to a Service
    @returns the next discovered Service
*/
Service *service_next (Service *s);

/** @brief Print description of a Service to stdout.
    @param s is a pointer to a Service
*/
void print_service (Service *s);

/** @} */

void print_dns_name (char *name);

