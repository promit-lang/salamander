/**
 * api.h
 * 
 * See the 'LICENSE' file for this file's license.
 * 
 * SalamaderVM is designed portablility and integration in mind. So, in that
 * regards SVM can be compiled as a dynamic/shared library, static library
 * or can be integrated inside of native application code entirely.
 * 
 * This file holds all the necessary macros for each of the integration 
 * behaviour.
 * 
 * Note: This header file is also used on other Promit implementation projects
 *       e.g. promit, which is the official implementation of Promit 
 *       Programming Language which uses SVM as it's main VM.
 * 
 * @authors:
 *   1. SD Asif Hossein <s.dah.ingularity@gmail.com> 27th Nov. 2022
*/

#ifndef __SALAMANDER_API_H__
#define __SALAMANDER_API_H__

#ifdef SALAMANDER_BUILD_SHARED

// For MSVC compilers in Windows.

#if (defined _WIN32 || defined _WIN64) && defined _MSC_VER

#ifdef SALAMANDER_BUILD_EXPORT
#define SALAMANDER_API __declspec(dllexport)
#else
#define SALAMANDER_API __declspec(dllimport)
#endif    // SALAMANDER_BUILD_EXPORT

// For other compilers such as Clang or GCC, which does not require extra 
// weird symbols for shared library export/import. 

#else
#define SALAMANDER_API extern
#endif    // Windows and MSVC compilers.

// We do not need extra symbols for static build.

#else
#define SALAMANDER_API
#endif    // SALAMANDER_BUILD_SHARED

#endif    // __SALAMANDER_API_H__