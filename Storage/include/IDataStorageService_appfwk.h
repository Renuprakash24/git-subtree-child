#ifndef I_DATA_STORAGE_APPFWK_H
#define I_DATA_STORAGE_APPFWK_H

 /**
 * \file
 *         IDataStorageService_appfwk.h
 * \brief
 *         data storage service interface for macchina applications
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
/***** INCLUDES ***********************************************************/

#include "Poco/OSP/Service.h"
#include "Poco/AutoPtr.h"
#include "Poco/Poco.h"

#define DATA_STORAGE_SERVICE_NAME                                    ("stla.persistence.datastorage.service")
#define MAX_FILENAME_SIZE                                            255

/***** TYPEDEFS ***********************************************************/

/*@brief Type of the data storage namespace */
//@serialize
typedef enum {
    DSS_PRIVATE_NAMESPACE = 0,    /* application private name space */
    DSS_SHARED_NAMESPACE  = 1     /* shared namespace - all files are public */
}dss_NameSpaceType_t;

/* @brief Type of the file access */
//@serialize
typedef enum {
    DSS_ACCESS_READ_ONLY  = 0,    /* files are accessed in read only mode */
    DSS_ACCESS_READ_WRITE,        /* files are accessed in read write mode */
    DSS_ACCESS_WRITE_ONLY         /* files are accessed in write only mode */
}dss_FileAccessMode_t;

/* @brief Type of file seek */
//@serialize
typedef enum {
    DSS_SEEK_SET = 0,  /* seek from the begining of the file */
    DSS_SEEK_CUR,      /* seek from current position in file */
    DSS_SEEK_END       /* seek from the end of the file */
}dss_SeekOffset_t;

/* @brief Error codes returned by data storage service API */
//@serialize
typedef enum {
    DSS_SERVICE_DISABLE = -656,
    DSS_ECONNREFUSED    = -111,
    DSS_ENAMETOOLONG    = -32,
    DSS_EINVAL          = -22,
    DSS_EEXIST          = -17,
    DSS_EBUSY           = -16,
    DSS_ENOMEM          = -12,
    DSS_ENOENT          = -2,
    DSS_EGENERIC        = -1
}dss_ErrorCode_t;


namespace Stla {
namespace Persistence {

/***** CLASSES ************************************************************/

class IDataStorageService: public Poco::OSP::Service
{
public:
    /**
     * @brief Ptr is an AutoPtr of IDataStorageService class type
     */
    typedef Poco::AutoPtr<IDataStorageService> Ptr;

    /**
     * @brief IDataStorageService constructor
     */
    IDataStorageService() { }

    /**
     * @brief IDataStorageService destructor
     */
    virtual ~IDataStorageService() { }

    /**
     * IDataStorageService events
     */

    /**
     * @brief File changed event. Applications are notified about shared files beeing changed (created or modified).
     * Name of the file is transmitted as parameter, not the file path.
     */
    Poco::BasicEvent<const std::string>              dss_FileChangedEvent;

    /**
     * @brief File releaseed event. Applications are notified about shared files beeing released (file is not in use).
     * Name of the file is transmitted as parameter, not the file path.
     */
    Poco::BasicEvent<const std::string>              dss_FileReleasedEvent;


    /**
     * IDataStorageService public methods
     */

    /**
     * @brief Open a data storage namespace. Each application or service can open its private namespace or the shared one.
     * @param[in] pBndlContext: bundle context pointer.
     * @param[in] nsType: indicates if the desired namespace to be opened is the private one or the shared one.
     * @return. positive number representing the unique namespace handle or negative value representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_NamespaceOpen( Poco::OSP::BundleContext::Ptr pBndlContext, dss_NameSpaceType_t nsType) = 0;


    /**
     * @brief Return the quota of the namespace.
     * @param[in] nsHandle: handle of the storage namespace. Obtained from dss_NamespaceOpen.
     * @return positive number representing the maximum accepted storage size for the specified namespace (in KiB),
     *          or a negative number in case of an error, representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_NamespaceGetQuota(int32_t nsHandle) = 0;


    /**
     * @brief Return the free space of the namespace
     * @param[in] nsHandle: handle of the storage namespace. Obtained from dss_NamespaceOpen
     * @return. positive number representing the free space size for the specified namespace (in KiB),
     *           or a negative number in case of an error, representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_NamespaceGetFreeSpace(int32_t nsHandle) = 0;


    /**
     * @brief Return the total used space (available for namespaces)
     * @param[in] none
     * @return. positive number representing the total used space size (in KiB),
     *           or a negative number in case of an error, representing the error code
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_GetTotalUsedSpace() = 0;


    /**
     * @brief Return the total free space available for namespaces
     * @param[in] none
     * @return. positive number representing the total free space size (in KiB),
     *           or a negative number in case of an error, representing the error code
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_GetTotalFreeSpace() = 0;


    /**
     * @brief Removes all files from the namespace indicated by the given argument.
     * @param[in] nsHandle: handle of the storage namespace. Obtained from dss_NamespaceOpen
     * @return. Zero in case of success,
     *           or a negative number in case of an error, representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     *          DSS_EBUSY  - file is busy (at least one file is still opened)
     */
    virtual int32_t dss_NamespaceRemoveAllFiles(int32_t nsHandle) = 0;

    /**
     * @brief Removes all files and namespace dir. for the namespace indicated by the given argument
     * @param[in] bundleSymbolicName: bundle symbolic name extracted from bundle context
     * @return. Zero in case of success,
     *           or a negative number in case of an error, representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     *          DSS_EBUSY  - file is busy (at least one file is still opened)
     */
    virtual int32_t dss_NamespaceRemove(const std::string bundleSymbolicName) = 0;


    /**
     * @brief Open a file from the storage namespace indicated by nsHandle.
     *     In case file is opened for read write or write only and file does not exist, it is created.
     * @param[in] nsHandle: handle of the storage namespace. Obtained from dss_NamespaceOpen.
     * @param[in] fileName: null terminated string representing the name of the file to be opened.
     * @param[in] accesMode: indicates the way file has to be opened read only, read write, or write only.
     * @return. Positive number representing the unique file handle, or negative value representing the error code in case of error
     *          DSS_EINVAL - invalid argument
     *          DSS_ENOENT - file does not exist (when opened read only)
     *          DSS_ENAMETOOLONG - file name too long
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_FileOpen(int32_t nsHandle, char const *fileName, dss_FileAccessMode_t accesMode) = 0;


    /**
     * @brief Close the file given as parameter through file handle received from dss_FileOpen call.
     * @param[in] fileHandle: handle of the opened file to close.
     * @return. Zero in case of success, or negative value representing the error code in case of error
     *          DSS_EINVAL - invalid argument
     */
    virtual int32_t dss_FileClose(int32_t fileHandle) = 0;

     /**
     * @brief Save a file from the storage. File must not be in use.
     * @param[in] nsHandle: handle of the storage namespace. Obtained from dss_NamespaceOpen
     * @param[in] fileName: null terminated string representing the name of the file to be opened
     * @param[in] isSynchronous: if true, the method call will end when the file was saved on file system.
     * @return. Zero on success, or negative value in case of error representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ENOENT - file does not exist (when opened read only)
     *          DSS_EBUSY  - file is in use
     *          DSS_ENAMETOOLONG - file name too long
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_FileSave(int32_t nsHandle, char const *fileName, bool isSynchronous) = 0;


     /**
     * @brief Delete a file from the storage. File must not be in use.
     * @param[in] nsHandle: handle of the storage namespace. Obtained from dss_NamespaceOpen
     * @param[in] fileName: null terminated string representing the name of the file to be removed
     * @return. Zero on success, or negative value in case of error representing the error code
     *          DSS_EINVAL - invalid argument
     *          DSS_ENOENT - file does not exist (when opened read only)
     *          DSS_EBUSY  - file is in use
     *          DSS_ENAMETOOLONG - file name too long
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_FileRemove(int32_t nsHandle, char const *fileName) = 0;


    /**
     * @brief Returns the size of the file.
     * @param[in] fileHandle: handle of the opened file to read from.
     * @return Size of the file in bytes, or negative value representing the error code, in case of error.
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_FileGetSize(int32_t fileHandle) = 0;


    /**
     * @brief Read from file at the current file offset. Offset updated after read opperation.
     *     Offset can be set using method dss_FileSeek
     * @param[in] fileHandle: handle of the opened file to read from.
     * @param[out] readBuffer: buffer to read into
     * @param[out] count: number of bytes to be read from file
     * @return Number of bytes read. Zero is returned in case offset is at the end of file.
     *   Negative value is returned in case of error (representing the error code)
     *          DSS_EINVAL - invalid argument
     *          DSS_ENOENT - file does not exist
     *          DSS_EBUSY  - file is busy (the file is shared and is being written)
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_FileRead(int32_t fileHandle, void *readBuffer, uint32_t count) = 0;


    /**
     * @brief Write in file at the current file offset. Offset is updated after write opperation.
     *     Offset can be set using method dss_FileSeek.
     * @param[in] fileHandle: handle of the opened file to write into.
     * @param[out] writeBuffer: buffer to write from
     * @param[out] count: number of bytes to be written to file
     * @return Number of bytes written. Negative value is returned in case of error (representing the error code)
     *          DSS_EINVAL - invalid argument
     *          DSS_EBUSY  - file is in use (the file is shared and is being read)
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     *          DSS_ENOMEM - if there is not enough space available
     */
    virtual int32_t dss_FileWrite(int32_t fileHandle, const void *writeBuffer, uint32_t count) = 0;


    /**
     * @brief Change the current file offset. Offset is updated after write opperation.
     *     Offset can be set using method dss_FileSeek
     * @param[in] fileHandle: handle of the opened file to seek.
     * @param[out] seekOffset: offset in bytes to seek in the file (could be positive, or negative number to give the seek direction)
     * @param[out] seekType: seek possition (begining, current possition, or end of the file)
     * @return File offset after seek operation. Negative value is returned in case of error (representing the error code)
     *          DSS_EINVAL - invalid argument
     *          DSS_ECONNREFUSED - storage is inaccessible (due to a connection problem, or not mounted yet)
     */
    virtual int32_t dss_FileSeek(int32_t fileHandle, int32_t seekOffset, dss_SeekOffset_t seekType) = 0;
};

} }

#endif
