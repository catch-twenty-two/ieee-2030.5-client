#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

#define CIPHER_LIST "ECDHE-ECDSA-AES128-CCM8"

/** @addtogroup security
    @{
*/

typedef int (*VerifyFunc) (void *context, uint8_t *cert, int length);

/** @brief Initialize the TLS library.

    Initialize the TLS library calling the appropriate functions. Load the
    device certificate 'path'.x509 and use the device private key
    'path'.pem, where 'path' is the first function parameter.
    @param path is used to identify the device certificate and private key
    files, 'path'.x509 and 'path'.pem respectively.
    @param verify is called as extra step to verify the client TLS certificate.
    Certificates are in any case are verified against their CA certificate
    chain, this extra step this can be used to impliment a filter by only
    accepting clients with the right credentials (SFDI, LFDI), this parameter
    can be NULL to indicate not to take this step.
    @returns the path of the device certificate 'path'.x509
*/
void tls_init (const char *path, VerifyFunc verify);

/** @brief Load a CA certificate.

    This certificate can be sent along with client certificate as part of
    establishing a TLS session, it can also be used in CA certificate chain
    verification of a client certificate.
    @param path is the file name of the CA certificate
*/
void load_cert (const char *path);

/** @brief Load a CA certificate directory.

    Call @ref load_cert for every file in the directory.
    @param path is the file name of the directory to load
*/
void load_cert_dir (const char *path);

/** @} */


