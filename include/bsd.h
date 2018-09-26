// BSD socket interface

#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct _Address {
  union {
    struct {
      uint16_t family;
      uint16_t port;
    };
    struct sockaddr_in in;
    struct sockaddr_in6 in6;
  };
  socklen_t length;
} Address;

#define ADDR_IPv6 AF_INET6
#define ADDR_IPv4 AF_INET

#define address_eq(x, y) (memcmp (x, y, sizeof (Address)) == 0)
#define address_copy(x, y) memcpy (x, y, sizeof (Address))
#define set_port(addr, p) (addr)->port = htons (p)
#define address_port(addr) ntohs ((addr)->port)
#define address_ipv6(addr) (addr)->in6.sin6_addr.s6_addr
#define address_ipv4(addr) ntohl ((addr)->in.sin_addr.s_addr)
#define address_type(addr) (addr)->family

#include "address.h"

int global_if_index;

void net_select (int index);

Address *new_address ();
Address *ipv4_address (Address *addr, uint32_t ip, int port);

int ipv6_scope (const char *addr);

Address *ipv6_address (Address *addr, const char *ip, int port);

void reuse_address (int s);

void reuse_port (int s);

int bsd_socket (int family);

int bsd_listen (Address *address);

int bsd_connected (int socket);

void multicast_join (int socket, const char *addr, int loop);

