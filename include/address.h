#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

char *hex4 (int *x, char *data);

char *hex16 (char *h, char *data);

int ipv6_input (char c);

char *parse_ipv6 (char *addr, char *data);

char *parse_ipv4 (uint32_t *addr, char *data);

char *parse_address (Address *addr, int port, char *data);

int write_ipv4 (char *buffer, uint32_t addr);

// write 128 bit host number to buffer in IPv6 format
int write_ipv6 (char *buffer, unsigned char *host);

int write_address (char *buffer, Address *addr);

int write_address_port (char *buffer, Address *addr);
