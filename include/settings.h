#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

typedef struct {
  SE_DERAvailability_t *dera;
  SE_DERCapability_t *dercap;
  SE_DERSettings_t *derg;
  SE_DERStatus_t *ders;
} Settings;

