#pragma once

// Copyright (c) 2015 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup security Security
    @{
*/

void print_bytes (unsigned char *data, int n);

/** @brief Generate SFDI from LFDI hash.
    @param lfdi is the 20 byte LFDI
    @returns the computed SFDI result
*/
uint64_t sfdi_gen (uint8_t *lfdi);

/** @brief Generate SFDI and LFDI hash values from a device certificate.
    @param lfdi is a 20 byte buffer that stores the LFDI result
    @param buffer contains the device certificate, it must be a multiple of
    SHA256_HASH_SIZE (64 bytes) and have at least 9 bytes of padding, this
    can be obtained by allocating a buffer of size sha256_size (length).
    @param length is the length of the device certificate
    @returns the SFDI hash result truncated from the LFDI result
*/
uint64_t lfdi_hash (uint8_t *lfdi, uint8_t *buffer, int length);

/** @brief Generate SFDI and LFDI hash values from a device certificate file.
    @param lfdi is a 20 byte buffer that stores the LFDI result
    @param path is the path of the device certificate
    @returns the SFDI hash result truncated from the LFDI result
*/
uint64_t lfdi_gen (uint8_t *lfdi, const char *path);

/** @brief Generate SFDI and LFDI hash values from a device certificate file and
    print them to the console.
    @param lfdi is a 20 byte buffer that stores the LFDI result
    @param path is the path of the device certificate
    @returns the SFDI hash result truncated from the LFDI result
*/
uint64_t load_device_cert (uint8_t *lfdi, const char *path);

/** @brief Initialize the device SFDI and LDFI.

    Initialize the global variable device_lfdi and device_sfdi by computing the
    hash of a device certificate.
    @param path is the path of the device certificate.
 */
void security_init (const char *path);

/** @} */

extern uint8_t device_lfdi[20];
extern uint64_t device_sfdi;


