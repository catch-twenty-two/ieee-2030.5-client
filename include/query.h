#pragma once

#include <stdint.h>

typedef struct {
  int64_t after;
  uint16_t start;
  uint8_t limit;
} Query;

int parse_query (Query *q, char *query);
