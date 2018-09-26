#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

#define SHA256_HASH_SIZE (512/8)
// buffer must include space for padding (at least 9 bytes)
// buffer must be a multiple 64 bytes (512 bits)
#define sha256_size(x) (((x)+9+63)&(~0x3f))

void sha256 (uint8_t *out, uint8_t *buffer, int length);

