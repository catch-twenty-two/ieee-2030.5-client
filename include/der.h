#pragma once

#include "list.h"
#include "schedule.h"

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup der DER Device

    The DER module provides methods and structures for managing DER EndDevices.
    @{
*/

#define DEVICE_SCHEDULE (EVENT_NEW+11)
#define DEVICE_METERING (EVENT_NEW+12)
#define DEFAULT_CONTROL (EVENT_NEW+13)

#include "settings.h"

/** A DerDevice is a representation of a DER EndDevice. */
typedef struct {
  uint64_t sfdi; ///< is the SFDI of the EndDevice
  uint8_t lfdi[20]; ///< is the LFDI of the EndDevice
  int metering_rate; ///< is the post rate for meter readings
  Stub *mup; ///< is a pointer to the MirrorUsagePoint for this EndDevice
  List *readings; ///< is a list of MirrorMeterReadings
  List *derpl; ///< is a list of DER programs 
  SE_DERControlBase_t base; 
  SE_DefaultDERControl_t *dderc; ///< is the default DER control
  Schedule schedule; ///< is the DER schedule for this device
  Settings settings; ///< is the DER device settings
} DerDevice;

/** @brief Get a DerDevice with the matching SFDI.
    @param sfdi is the EndDevice SFDI
    @returns a pointer to a DerDevice
*/
DerDevice *get_device (uint64_t sfdi);

/** @brief Load device settings from the directory.
    @param sfdi is the device SFDI
    @param path is the name of a directory containing XML files with the
    device settings
*/
void device_settings (uint64_t sfdi, char *path);

/** @brief Load a device certificate and store in the DerDevice hash.
    @param path is the file name of the device certificate
*/
void device_cert (const char *path);

/** @brief Load a set of device certificates.
    @param path is the name of the directory containing the device certificates.
*/
void device_certs (char *path);

/** @brief Create a DER schedule for an EndDevice.
    @param edev is a pointer to an EndDevice Stub
*/
void schedule_der (Stub *edev);

/** @} */

