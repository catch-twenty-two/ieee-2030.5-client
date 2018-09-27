#pragma once

#include "resource.h"
#include "dnssd_client.h"

// Copyright (c) 2018 Electric Power Research Institute, Inc.
// author: Mark Slicker <mark.slicker@gmail.com>

/** @defgroup retrieve Retrieve

    The retrieve module provides high level methods to retrieve resources from
    IEEE 2030.5 servers. These methods use a placeholder called a Stub to track
    the state of retrieval and provide local storage for a resource. The Stubs
    can be linked together to create and manage hierarchies of both dependent
    and required resources.

    When a resource and all of its subordinates are fully and successfully
    retrieved then the resource is considered complete, this condition is
    monitored by the retrieval algorithm and can optionally signal a user
    supplied routine using the resource as a parameter.
    
    @ingroup resource
    @{
*/

#define RESOURCE_POLL (EVENT_NEW+6)
#define RESOURCE_UPDATE (EVENT_NEW+7)
#define RESOURCE_REMOVE (EVENT_NEW+8)
#define RETRIEVE_FAIL (EVENT_NEW+9)

/** A Resource Stub. */
typedef struct _Stub {
  Resource base; ///< is a container for the resource
  void *conn; ///< is a pointer to an SeConnection
  int status; ///< is the HTTP status, 0 for a new Stub, -1 for an update
  time_t poll_next; ///< is the next time to poll the resource
  int16_t poll_rate; ///< is the poll rate for the resource
  unsigned complete : 1; ///< marks the Stub as complete
  unsigned subscribed : 1;
  uint32_t flag; ///< is the marker for this resource in its dependents
  uint32_t flags; ///< is a bitwise requirements checklist
  uint32_t offset; ///< is the offset used for list paging
  uint32_t all; ///< is the total number of list items
  struct _Stub *moved; ///< is a pointer to the new resource
  List *list; ///< is a list of old requirements for updates
  List *deps; ///< is a list of dependencies
  List *reqs; ///< is a list of requirements
  union {
    void *context; ///< is a user defined completion context
    List *schedules; //< is a list of schedules for event resources 
  };
  void (*completion) (struct _Stub *); ///< is a user defined completion routine
} Stub;

/** @brief Get an IEEE 2030.5 resource.
    @param conn is a pointer to an SeConnection
    @param type is an IEEE 2030.5 schema type
    @param href is URI string, the location of the resource
    @param count is the number of items to get for %List resources, should be 0
    for non-List resources
    @returns a pointer to the Stub for the resource
*/
Stub *get_resource (void *conn, int type, const char *href, int count);

/** @brief Get a subordinate resource given a parent object.

    Subordinate resources are retrieved from links in the parent object.
    Links follow a naming convention, they are named after the type of the
    subordinate resource with the string "Link" appended. This macro
    provides a convienent way to retrieve a subordinate resource, taking
    advantage of the naming pattern used to link subordinate resources from
    their parent object.
    @param conn is a pointer to an SeConnection
    @param obj is a pointer to an IEEE 2030.5 object
    @param type is the type name of the subordinate resource
    @returns a pointer to the Stub for the resource if the link exists,
    NULL otherwise
*/
#define get_root(conn, obj, type)				\
  (se_exists (obj, type##Link)?					\
   get_resource (conn, SE_##type, (obj)->type##Link.href, 0) : NULL)

/** @brief Get a subordinate %List resource given a parent object.

    The same as @ref get_root but for subordinate %List resources. Links to
    %List resources include the "all" parameter, this indicates the number of
    items contained in the %List resource and is used as a query parameter in
    the HTTP GET request.
    @param conn is a pointer to an SeConnection
    @param obj is a pointer to an IEEE 2030.5 object
    @param type is the type name of the subordinate resource
    @returns a pointer to the Stub for the resourceif the link exists,
    NULL otherwise
*/
#define get_list_root(conn, obj, type)				\
  (se_exists (obj, type##Link)?					\
   get_resource (conn, SE_##type, (obj)->type##Link.href,	\
		 (obj)->type##Link.all) : NULL)

/** Get a subordinate resource Stub and make the parent resource a dependent.

    Creates a two way link between the subordinate and parent resources, the
    parent stores a bit representing the requirement for the subordinate
    resource and the subordinate resource clears this bit once all of its
    requirements are met (full retrieval of itself and all of its
    subordinates). 
    @param r is a pointer to a Stub, the parent resource
    @param obj is a pointer to an IEEE 2030.5 object
    @param type is the type name of the subordinate resource    
    @returns a pointer to the subordinate resource Stub
*/
#define get_dep(r, obj, type)					\
  new_dep (r, get_root ((r)->conn, obj, type), SE_##type##Link_exists)

/** @brief Get a subordinate %List resource Stub and make the parent resource a
    dependent.

    Performs the same function as @ref get_dep except for %List resources.
    @param r is a pointer to a Stub, the parent resource
    @param obj is a pointer to an IEEE 2030.5 object
    @param type is the type name of the subordinate resource
    @returns a pointer to the subordinate resource Stub
*/
#define get_list_dep(r, obj, type)				\
  new_dep (r, get_list_root ((r)->conn, obj, type), SE_##type##Link_exists)

/** @brief Dependency function */
typedef void (*DepFunc) (Stub *s);

/** @brief Process HTTP data from an SeConnection. 

    For each retrieved resource that matches a pre-existing Stub resource,
    store the resource and process it with the dependency function to retrieve
    any subordinate resources and create the requirement/dependency
    relationship.
    @param conn is a pointer to an SeConnection
    @param dep is a pointer to a DepFunc
 */
int process_http (void *conn, DepFunc dep);
void poll_resource (Stub *s);
void remove_stub (Stub *s);
void get_seq (Stub *s, int offset, int count);
void *get_subordinate (Stub *s, int type);
Stub *new_dep (Stub *r, Stub *d, int flag);
void delete_stub (Stub *s);
Stub *get_dcap (Service *s, int secure);
Stub *get_path (Service *s, int secure);
void cleanup_http (void *conn);

/** @} */

