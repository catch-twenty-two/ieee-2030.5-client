#pragma once

#include "dnssd_client.h"

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup se_discover IEEE 2030.5 Service Discovery
    @ingroup dnssd_client

    Provides an implementation of IEEE 2030.5 Service Discovery.
    @{
*/

enum SeServerFlag {
  BILLING_SERVER = (1 << 0 ),      /**< Billing Server */
  DRLC_SERVER = (1 << 1 ),         /**< Demand Response / Load Control Server */
  DER_SERVER = (1 << 2),           /**< Distributed Energy Resources Server */
  FILE_SERVER = (1 << 3),          /**< File Download Server */
  MESSAGE_SERVER = (1 << 4),       /**< Messaging Server */
  PREPAYMENT_SERVER = (1 << 5),    /**< Prepayment Server */
  RESPONSE_SERVER = (1 << 6),      /**< Response Server */
  PRICE_SERVER = (1 << 7),         /**< Pricing Server */
  TIME_SERVER = (1 << 8),          /**< Time Server */
  METER_SERVER = (1 << 9),         /**< Metering Server */
  EDEV_SERVER = (1 << 10),         /**< End Device Server */
  METER_MIRROR_SERVER = (1 << 11), /**< Metering Mirroring Server */
  SELF_DEVICE_SERVER = (1 << 12),  /**< Self Device Server */
  SE_SERVER = (1 << 13)            /**< Any SmartEnergy Server */
};

/** @brief Return a server flag given its subquery name.
    @param name is a subquery name, one of "bill", "dr", "derp", "file",
    "msg", "ppy", "rsps", "tp", "tm", "upt", "edev", "mup", "sdev", or 
    "smartenergy"
    @returns one of the values of SeServerFlag corresponding with the subquery
    name.
*/
int se_subquery (char *name);

/** @brief Send a DNS-SD query for the indicated servers.
    @param server is a an bitwise OR (|) list of SeServerFlag values.
    @param qu is the value of the QU bit, 1 requests that the server send a
    unicast response, 0 requests that a server send a multicast response 
*/
void se_discover (int server, int qu);

void discover_device ();

/** @brief Return the value of the 'path' key if set.
    @param s is a pointer to a Service
    @returns the value of the 'path' key if set, NULL otherwise
*/
char *service_path (Service *s);

/** @brief Return the value of the 'dcap' key if set.
    @param s is a pointer to a Service
    @returns the value of the 'dcap' key if set, NULL otherwise
*/
char *service_dcap (Service *s);

int service_type (Service *s);

/** @brief Connect to a given service, return the connection.
    @param s is a pointer to a Service
    @param secure indicates whether to attempt a secure TLS connection or not,
    this is only possible when the 'https' key is set.
*/
void *service_connect (Service *s, int secure);

Service *service_receive (UdpPort *port);

void discover_init (char *name);

/** @} */


