#pragma once

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup metering Metering

    Create MirrorUsagePoints and MirrorMeterReadings.
    @{
*/

/** RoleFlags for a UsagePoint */
enum RoleFlags {
  isMirror = 1, ///< SHALL be set if the server is not the measurement device
  isPremisesAggregationPoint = (1 << 1),
  ///< SHALL be set if the UsagePoint is the point of delivery for a premises
  isPEV = (1 << 2),///< SHALL be set if the usage applies to an electric vehicle
  isDER = (1 << 3),
  /**< SHALL be set if the usage applies to a distributed
     energy resource, capable of delivering power to the grid. */
  isRevenueQuality = (1 << 4), /**< SHALL be set if usage was measured by a
				  device certified as revenue quality */
  isDC = (1 << 5), //< SHALL be set if the usage point measures direct current
  isSubmeter = (1 << 6) /**< SHALL be set if the usage point is not a premises
			    aggregation point */
};

/** @brief Initialize a MirrorUsagePoint structure.
    @param mup is a pointer to an SE_MirrorUsagePoint_t strcuture
    @param desc is a pointer to a string (up to 31 bytes) describing the mirror
    or NULL for no description.
    @param flags is a set of RoleFlags (bitwise OR of zero or more flags)
    @param lfdi is a pointer to a device LFDI
*/
void create_mirror (SE_MirrorUsagePoint_t *mup, char *desc,
		    int flags, char *lfdi);

/** @brief Create a new MirrorMeterReading and add it to the list. 
    @param rds is a pointer to a List of MirrorMeterReadings
    @param desc is a pointer to a string, the reading description, or NULL for
    no description
    @param uom is the type of the reading (UomType)
    @param kind is ReadingType kind (KindType)
*/
List *create_reading (List *rds, char *desc, int uom, int kind);

/** @} */

