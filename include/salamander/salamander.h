/**
 * salamander.h
 * 
 * See the 'LICENSE' file for this file's license.
 *
 * This header file provides the main API functions and symbols related to
 * SalamanderVM. Include this file, if you wish to run bytecodes and do
 * interaction with the VM through the API stack.
 *
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 7th Dec. 2022
 */

#ifndef __SALAMANDER_H__
#define __SALAMANDER_H__

// For API access specifier.

#include <salamander/api.h>

// SalamanderVM version number componenets.

#define SALAMANDER_VERSION_MAJOR 1
#define SALAMANDER_VERSION_MINOR 0
#define SALAMANDER_VERSION_PATCH 1
#define SALAMANDER_VERSION_REVIS 1    // Revision.

// SVM version string.

#define SALAMANDER_VERSION_STRING "1.0.1r1"

// Numeric representation of SVM version number. Use this if you want to do 
// altogether version check and use specific features in the host application.
// 
// Version number does not include revision.

#define SALAMANDER_VERSION_NUMBER (SALAMANDER_VERSION_MAJOR * 1000000 \
                                   SALAMANDER_VERSION_MINOR *    1000 \
								   SALAMANDER_VERSION_PATCH)

// Forward declaration of structure SalamanderVM. When you embed SVM in your 
// host application, you don't need to access the contents of that struct. So, 
// therefore for security reasons, the contents has been abstracted and the 
// struct declaration can be found on "vm.h" in the main VM implementation.

typedef struct struct_SalamanderVM SalamanderVM;

// TODO: add conf.

// struct struct_SalamanderConfiguration {

// } SalamanderConfiguration;

#endif    // __SALAMANDER_H__