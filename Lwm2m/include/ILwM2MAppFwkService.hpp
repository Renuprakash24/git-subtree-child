/**
 * \file
 *         ILwM2MAppFwkService.hpp
 * \brief
 *         Interface available for 3rd Party application to access the LwM2M General Purpose object instances.
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
 
#ifndef ILwM2MAPPFWKSERVICE_H_
#define ILwM2MAPPFWKSERVICE_H_

#include <string>

#include <Poco/BasicEvent.h>
#include <Poco/OSP/Service.h>
#include "Poco/OSP/SystemEvents.h"
#include "Poco/OSP/BundleContext.h"

#include "ILwM2MAppFwkTypes.hpp"

namespace Stla
{
namespace Connectivity
{
/**
 * ILwM2MInstanceHandler is the class used to interface with an existing instance of General Purpose object.
 *
 */
#ifdef DOXYGEN_WORKING
class ILwM2MInstanceHandler: public Poco::RefCountedObject
#else
class __attribute__((visibility("default"))) ILwM2MInstanceHandler: public Poco::RefCountedObject
#endif
{
public:
    typedef Poco::AutoPtr<ILwM2MInstanceHandler> Ptr;

    /**
     * @brief Destroy the ILwM2MInstanceHandler handler
     *
     */
    virtual ~ILwM2MInstanceHandler()
    {
    }

    // Events
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_string_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_string_resource_t> StringResourceChanged;
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_integer_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_integer_resource_t> IntegerResourceChanged;
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_float_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_float_resource_t> FloatResourceChanged;
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_boolean_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_boolean_resource_t> BooleanResourceChanged;
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_opaque_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_opaque_resource_t> OpaqueResourceChanged;
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_integer_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_integer_resource_t> TimeResourceChanged;
    /**
     * @brief Notification for resource modified by the server.
     *
     * @param str_objlnk_resource_t resource ID & new resource value.
     */
    Poco::BasicEvent<const str_objlnk_resource_t> ObjlnkResourceChanged;

    // Getters / setters
    /**
     * @brief Getter for the object instance ID
     *
     * @return The instance ID of the current instance being accessed.
     */
    virtual lwm2m_appfwk_itf_oiid_t getInstanceId() = 0;

    /**
     * @brief Getter for the whole object instance (all the resources)
     *
     * @param instance reference to an empty instance structure - on success, existing resources will be set on this instance
     *
     * @return
     * OK (0) - success <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getInstance(
            str_instance_t & instance) = 0;

    /**
     * @brief Getter for the list of resources instantiated in the current object instance
     *
     * @param instance_rids reference to an empty list of resources - on success, will contain the list of set resources
     *
     * @return
     * OK (0) - success <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getInstanceResourceIds(
            str_instance_resources_t & instance_rids) = 0;

    /**
     * @brief Getter for the Symbolic Name resource value
     *
     * @param a String resource reference; on success, the value of the resource
     *                 will be set with the Symbolic Name resource ID and value.
     *
     * @return
     * OK (0) - success <br>
     * INVALID_RID - the resource ID does not match the Symbolic Name's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getSymbolicNameResourceValue(
            str_string_resource_t & resource) = 0;

    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write String resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getStringResourceValue(
            str_string_resource_t & resource) = 0;

    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Integer resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getIntegerResourceValue(
            str_integer_resource_t & resource) = 0;
    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Float resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getFloatResourceValue(
            str_float_resource_t & resource) = 0;
    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Boolean resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getBooleanResourceValue(
            str_boolean_resource_t & resource) = 0;
    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Opaque resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getOpaqueResourceValue(
            str_opaque_resource_t & resource) = 0;
    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Time resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getTimeResourceValue(
            str_integer_resource_t & resource) = 0;
    /**
     * @brief Getter for a single resource value
     *
     * @param resource reference to a resource structure with the desired rid
     *                 set - on success, the value of the resource will be set.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write ObjLnk resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getObjlnkResourceValue(
            str_objlnk_resource_t & resource) = 0;

    /**
     * @brief Setter for a single resource value
     *
     * @param resource resource to write - include both value and rid
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write String resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setStringResourceValue(
            const str_string_resource_t resource) = 0;
    /**
     * @brief Setter for a single resource value
     *
     * @param resource resource to write - include both value and rid
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Integer resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setIntegerResourceValue(
            const str_integer_resource_t resource) = 0;
    /**
     * @brief Setter for a single resource value
     *
     * @param resource resource to write - include both value and rid
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Float resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setFloatResourceValue(
            const str_float_resource_t resource) = 0;
    /**
     * @brief Setter for a single resource value
     *
     * @param resource resource to write - include both value and rid
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Boolean resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setBooleanResourceValue(
            const str_boolean_resource_t resource) = 0;
    /**
     * @brief Setter for a single resource value
     *
     * @param resource resource to write - include both value and rid
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Opaque resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setOpaqueResourceValue(
            const str_opaque_resource_t resource) = 0;
    /**
     * @brief Setter for a single resource value
     *
     * @param resource resource to write - include both value and rid
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write Time resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setTimeResourceValue(
            const str_integer_resource_t resource) = 0;
    /**
     * @brief Setter for a single resource value
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for AppFwk-DM object instances <br>
     * INVALID_RID - the resource ID is out of bound of Read-only or Read-write ObjLnk resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setObjlnkResourceValue(
            const str_objlnk_resource_t resource) = 0;

    /**
     * @brief Removes a resource from the object
     *
     * @param rid resource ID to be deleted
     *
     * @warning It is not possible for an application to delete the Symbolic name resource.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * METHOD_NOT_ALLOWED - the operation is not allowed <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t deleteResource(
            const lwm2m_appfwk_itf_rid_t rid) = 0;

    /**
     * @brief Register the application to override the LwM2M client Execute operation.
     *
     * @param rid the resource ID
     *
     * @warning when registered, the application will receive ExecuteOperation events for an executable resource.
     * The application must reply to the operation with "setExecuteResult" in a timely manner, or the Execute operation will fail.
     *
     * @return
     * OK (0) - success <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t registerExecuteOpHandler(
            const lwm2m_appfwk_itf_rid_t rid) = 0;

    /**
     * @brief Notification for new Execute operation from the server.
     *
     * @param str_executable_parameters_t execute parameters: the resource ID and the parameters associated with the Execute operation.
     */
    Poco::BasicEvent<const str_executable_parameters_t> ExecuteOperation;

    /**
     * @brief Send the result of an Execute operation (Failed or Success) to the local LwM2M client.
     *
     * @param rid the ID of the execute operation
     * @param success set to True if the Execute operation was successful, and to False otherwise
     *
     * @warning if the result is not sent in a timely manner (around 60 seconds), the client will consider the operation failed.
     *
     * @return
     * OK (0) - success <br>
     * NOT_FOUND - resource not found <br>
     * INVALID_RID - the resource ID is out of bound of Executable resource's ID <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t setExecuteResult(
            const lwm2m_appfwk_itf_rid_t rid, const bool success) = 0;

};

#ifdef DOXYGEN_WORKING
class ILwM2MObjectHandler: public Poco::RefCountedObject
#else
class __attribute__((visibility("default"))) ILwM2MObjectHandler: public Poco::RefCountedObject
#endif
        {
public:

    /**
     * @brief Class smart pointer definition
     */
    typedef Poco::AutoPtr<ILwM2MObjectHandler> Ptr;

    /**
     * @brief Destroy the ILwM2MObjectHandler handler
     *
     */
    virtual ~ILwM2MObjectHandler()
    {
    }

    /**
     * @brief Getter for the LwM2M AppFwk Service Object instances for a given application (N.B. application Symbolic Name is retrieved by the Framework).
     *
     * @param instance_list reference to an empty list of object instances - on success, the list will contain the instance IDs belonging to the application (whose Symbolic name matches the Symbolic name of each of the instances).
     *
     * @return
     * OK (0) - success <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t getLwM2MAppFwkObjectInstanceList(
            std::vector<lwm2m_appfwk_itf_oiid_t> & instance_list) = 0;

    /**
     * @brief Getter for the LwM2M AppFwk Service Instance Handler for a given Object instance.
     *
     * @param oiid the object instance ID to be retrieved.
     *
     * @return a pointer to the requested object instance handler, or nullptr if no such object.
     */
    virtual ILwM2MInstanceHandler::Ptr getLwM2MAppFwkObjectInstance(
            const lwm2m_appfwk_itf_oiid_t oiid) = 0;

    /**
     * @brief Creates a new object instance based on the instance parameter (save for the symbolic name), and with the specific given object instance id.
     *
     * @param oiid object instance ID created.
     * @param instance the resources for the new instance
     *
     * @info The Symbolic Name will be taken out of context, the one set inside instance's symbolic_name field will be ignored.
     * @warning The framework/interface shall retrieve the Symbolic name of the calling application, and use it for the Symbolic name resource value.
     *
     * @return
     * OK (0) - success <br>
     * OUT_OF_MEMORY - operation exceeds the available memory for one instance <br>
     * OUT_OF_INSTANCE - operation exceeds the maximum number of instances <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     * ALREADY_CREATED - already created the resource <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t createNewInstance(
            const lwm2m_appfwk_itf_oiid_t oiid,
            const str_instance_t instance) = 0;

    /**
     * @brief Deletes an existing object instance.
     *
     * @param oiid object instance ID created.
     *
     * @return
     * OK (0) - success <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     * ID_INVALID - id given is invalid <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t deleteInstance(
            const lwm2m_appfwk_itf_oiid_t oiid) = 0;

    /**
     * @brief Notification for new object instance created by the server (the object is already created).
     *
     * @param lwm2m_appfwk_itf_oiid_t object instance ID created.
     */
    Poco::BasicEvent<const lwm2m_appfwk_itf_oiid_t> InstanceCreated;

    /**
     * @brief Notification for existing object instance deleted by the server (the object is already deleted).
     *
     * @param lwm2m_appfwk_itf_oiid_t object instance ID deleted.
     */
    Poco::BasicEvent<const lwm2m_appfwk_itf_oiid_t> InstanceDeleted;

    /**
     * @brief Notification for existing object instance change (following a write object instance operation from server).
     *
     * @param lwm2m_appfwk_itf_oiid_t object instance ID modified.
     *
     * @warning The new instance may either update the current one (only adding or updating new values) or replace it (resources not present are removed).
     */
    Poco::BasicEvent<const lwm2m_appfwk_itf_oiid_t> InstanceChanged;

};

/**
 * @brief LwM2M (DM) - AppFwk service name used in OSP
 */
const char* const LWM2M_APPFWK_SERVICE_NAME =
        "stla.connectivity.lwm2mappfwk.service.base";

/**
 * ILwM2MAppFwkService is the LwM2M (DM) - AppFwk service definition to allow access to General Purpose Object instances.
 */
#ifdef DOXYGEN_WORKING
class ILwM2MAppFwkService: public Poco::OSP::Service
#else
class __attribute__((visibility("default"))) ILwM2MAppFwkService: public Poco::OSP::Service
#endif
        {
public:

    /**
     * @brief Class smart pointer definition
     */
    typedef Poco::AutoPtr<ILwM2MAppFwkService> Ptr;

    /**
     * ILwM2MAppFwkService constructor.
     *
     * This class is used to interface with the LwM2M object
     *
     * @warning The framework/interface shall retrieve the Symbolic name of the calling application.
     */
    ILwM2MAppFwkService()
    {
    }

    /**
     * ILwM2MAppFwkService destructor.
     */
    virtual ~ILwM2MAppFwkService()
    {
    }

    // Here add if wanted broadcasted events, or general functional 
    /**
     * @brief Tells if the service functionality is ready or not
     *
     * @return
     * OK (0) - success <br>
     * BROKEN_LINK - link is broken depending on TCU architecture. For eg: usb connection is lost <br>
     */
    virtual e_lwm2m_appfwk_itf_err_code_t isServiceReady() const = 0;

    /**
     * @brief Poco event notifying that the service is ready (service ready value == lwm2m_appfwk_itf_err_code::OK)
     *
     */
    Poco::BasicEvent<const e_lwm2m_appfwk_itf_err_code_t> event_ServiceStatusChange;

    /**
     * @brief Get the Object Handler, unique per bundlecontext (= unique per application)
     *
     * @param pAppBndlContext Application context
     *
     * @return ILwM2MObjectHandler::Ptr
     */
    virtual ILwM2MObjectHandler::Ptr getObjectHandler(
            Poco::OSP::BundleContext::Ptr pAppBndlContext) = 0;

    /**
     * @brief       Returns the service information for the object's class.
     */
    const std::type_info& type() const
    {
        return typeid(ILwM2MAppFwkService);
    }

    /**
     * @brief       Returns true if the class is a subclass of the class given by obj.
     */
    bool isA(const std::type_info& obj) const
    {
        std::string name(type().name());
        return name == obj.name();
    }

};

} /* namespace Connectivity */
} /* namespace Stla */

#endif /* ILwM2MAPPFWKINSTANCES_H_ */
