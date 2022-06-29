/**
 * \file
 *         ILwM2MAppFwkTypes.hpp
 * \brief
 *         Primitives available for 3rd Party application to manipulate LwM2M General Purpose instances.
 * 
 * \par Copyright Notice:
 * \verbatim
 * Copyright (c) 2021 Stellantis N.V.
 * All Rights Reserved.
 * The reproduction, transmission or use of this document or its contents is
 * not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights created
 * by patent grant or registration of a utility model or design, are reserved.
 * \endverbatim
 */

#ifndef ILwM2MAPPFWKTYPES_H_
#define ILwM2MAPPFWKTYPES_H_

#include <string>
#include <cstdint>
#include <cstdbool>
#include <vector>


/**
 * @brief Object ID of an LwM2M object.
 */
typedef uint16_t lwm2m_appfwk_itf_oid_t;

/**
 * @brief Object Instance ID of an LwM2M object instance.
 */
typedef uint16_t lwm2m_appfwk_itf_oiid_t;

/**
 * @brief Resource ID of the resource of an LwM2M object.
 */
typedef uint16_t lwm2m_appfwk_itf_rid_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_string_resource
{
    lwm2m_appfwk_itf_rid_t rid;
    std::string value;
} str_string_resource_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_integer_resource
{
    lwm2m_appfwk_itf_rid_t rid;
    int64_t value;
} str_integer_resource_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_float_resource
{
    lwm2m_appfwk_itf_rid_t rid;
    double value;
} str_float_resource_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_boolean_resource
{
    lwm2m_appfwk_itf_rid_t rid;
    bool value;
} str_boolean_resource_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_opaque_resource
{
    lwm2m_appfwk_itf_rid_t rid;
    std::vector<unsigned char> value;
} str_opaque_resource_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_objlnk_resource
{
    lwm2m_appfwk_itf_rid_t rid;
    lwm2m_appfwk_itf_oid_t lnk_oid;
    lwm2m_appfwk_itf_oiid_t lnk_oiid;
} str_objlnk_resource_t;

/**
 * @brief Resource ID and value.
 */
typedef struct str_executable_parameters
{
    lwm2m_appfwk_itf_rid_t rid;
    std::vector<std::string> parameters;
} str_executable_parameters_t;

/**
 * @brief List (vector) of resource IDs.
 */
typedef struct str_instance_resources
{
    std::vector<lwm2m_appfwk_itf_rid_t> rids;
} str_instance_resources_t;

/**
 * @brief Instance's all values, lists (vectors) with resource IDs and values.
 */
typedef struct str_instance
{
    str_string_resource_t symbolic_name;
    std::vector<str_string_resource_t> read_only_string_list;
    std::vector<str_string_resource_t> read_write_string_list;
    std::vector<str_integer_resource_t> read_only_integer_list;
    std::vector<str_integer_resource_t> read_write_integer_list;
    std::vector<str_float_resource_t> read_only_float_list;
    std::vector<str_float_resource_t> read_write_float_list;
    std::vector<str_boolean_resource_t> read_only_boolean_list;
    std::vector<str_boolean_resource_t> read_write_boolean_list;
    std::vector<str_opaque_resource_t> read_only_opaque_list;
    std::vector<str_opaque_resource_t> read_write_opaque_list;
    std::vector<str_integer_resource_t> read_only_time_list;
    std::vector<str_integer_resource_t> read_write_time_list;
    std::vector<str_objlnk_resource_t> read_only_objlnk_list;
    std::vector<str_objlnk_resource_t> read_write_objlnk_list;
} str_instance_t;


/**
 * @brief The possible communication error codes:
 * OK - success
 * NOT_FOUND - resource not found
 * METHOD_NOT_ALLOWED - the operation is not allowed
 * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances
 * OUT_OF_INSTANCE - all available General Purpose object instances are being used
 * INVALID_RID - the type of the resource/value does not match the preset type, or is out of bound
 * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost 
 * COMM_NOT_AVAILABLE - internet connection not available
 * ALREADY_CREATED - already created the resource
 * ID_INVALID - id given is invalid
 */
 //@serialize
typedef enum e_lwm2m_appfwk_itf_err_code
{
    OK = 0,             // no error
    NOT_FOUND,          // resource not found
    METHOD_NOT_ALLOWED, // the operation is not allowed
    OUT_OF_MEMORY,      // operation exceeds the available memory for AppFwk-DM object instances
    OUT_OF_INSTANCE,    // all available General Purpose object instances are being used
    INVALID_RID,        // the type of the resource/value does not match the preset type, or is out of bound
    BROKEN_LINK,        // link is broken depending on TCU architecture. For eg: usb connection is lost
    COMM_NOT_AVAILABLE, // internet connection not available
    ALREADY_CREATED,    // already created the resource
    ID_INVALID,         // id given is invalid
    UNKNOWN_ERROR
} e_lwm2m_appfwk_itf_err_code_t;

#endif /* ILwM2MAPPFWKTYPES_H_ */
