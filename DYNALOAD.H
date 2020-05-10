/*
 * ---------------------------------------------------------------------------
 * DYNALOAD.H : cross-platform dynamic library loader (REQUIRES: HARDFORM)
 * ---------------------------------------------------------------------------
 * Created on:  5 jun 2019
 * Updated on: 10 may 2020
 *     Author: Martin Andreasson
 *    Version: 1.0
 *    License: Mozilla Public License Version 2.0
 * ---------------------------------------------------------------------------
 * Usage:
 * 
 * #define DYNALOAD_IMPLEMENTATION
 * 
 * before including this file in *one* C or C++
 * file to create the implementation.
 * 
 *    // that may look like this
 *    #include ...
 *    #include ...
 *    #include ...
 *    #define DYNALOAD_IMPLEMENTATION
 *    #include "DYNALOAD.H"
 * 
 * You can, (if you want) before the #include, do any of the following:
 * - #define DYNALOAD_ASSERT(x) to avoid using assert.h
 * - #define DYNALOAD_MALLOC(x) to avoid malloc
 * - #define DYNALOAD_REALLOC to avoid realloc
 * - #define DYNALOAD_FREE(x) to avoid free
 * - #define DYNALOAD_MEMCPY(d,p,s) to avoid memcpy
 * - #define DYNALOAD_MEMSET(d,v,s) to avoid memset
 * - #define DYNALOAD_STRLEN(x) to avoid strlen
 * - #define DYNALOAD_LOGF(...) to use your printf instead of stderr fprintf
 * 
 * Std library function(s) will be used if one of the above is not defined.
 */
/*#########################################################################*/
#if defined(_MSC_VER) && (_MSC_VER >= 1020)                  /* MSVC GUARD */
#	pragma once
#endif                                                       /* MSVC GUARD */
/*#########################################################################*/
#ifndef HEADER_DYNALOAD_H_INCLUDED_
#define HEADER_DYNALOAD_H_INCLUDED_               /* STANDARD HEADER GUARD */
/*#########################################################################*/
// #define OVERRIDE_DYNALOAD_MALLOC to provide your own malloc

#include "HARDFORM.H"

#ifdef __cplusplus
extern "C" {
#endif

//! opaque object handle for dynaload
typedef struct S_DYNALOAD s_dynaload;


/**
 * Create a new instance of dynaload, the dynamic module loading library.
 * <br/>
 * @param library_name OPTIONAL name of module ("__.DLL" or NULL, etc.)
 * @param opt_loaded   OPTIONAL boolean indicate whether lib was loaded
 * @return new dynaload instance
 */
s_dynaload* dynaload_create( cstr library_name, hbool * opt_loaded );


/**
 * Destroy an instance of dynaload.
 * <br/>
 * @param dl Instance to destroy
 */
void dynaload_destroy( s_dynaload* dl );


/**
 * Load the given dynamic module.
 * <br/>
 * @param dl           Instance of dynaload
 * @param library_name Name of dynamic module ("__.DLL" or NULL, etc.)
 * @return whether successful
 */
hbool dynaload_loadlibrary(
	s_dynaload * dl,
	cstr         library_name );


/**
 * Close the currently opened dynmic module, if there is one.
 * <br/>
 * @param dl Instance of dynaload
 */
void dynaload_exitlibrary( s_dynaload * dl );


/**
 * Is the dyncamic module loaded?
 * <br/>
 * @param dl Instance of dynaload
 * @return whether loaded
 */
hbool dynaload_is_loaded( const s_dynaload * dl );


/**
 * Get Procedure Address.
 * <br/>
 * @param dl            Instance of dynaload
 * @param name          Name of function
 * @param success       OPTIONAL return value indicating succcess
 */
void* dynaload_procload(
	s_dynaload * dl,
	cstr         function_name,
	hbool      * success );


/****************************************************************************
 *
 * IMPLEMENTATION
 *
 ****************************************************************************/
#ifdef DYNALOAD_IMPLEMENTATION

#ifndef DYNALOAD_MALLOC
#define DYNALOAD_MALLOC( size ) malloc( size )
#ifndef DYNALOAD_USES_STDLIB_H
#define DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_MALLOC

#ifndef DYNALOAD_REALLOC
#define DYNALOAD_REALLOC realloc
#ifndef DYNALOAD_USES_STDLIB_H
#define DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_REALLOC

#ifndef DYNALOAD_FREE
#define DYNALOAD_FREE(x) free(x)
#ifndef DYNALOAD_USES_STDLIB_H
#define DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_FREE

#ifndef DYNALOAD_MEMCPY
#define DYNALOAD_MEMCPY(d,p,s) memcpy(d,p,s)
#ifndef DYNALOAD_USES_STDLIB_H
#define DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_USES_STDLIB_H
#endif //!DYNALOAD_MEMCPY

#ifndef DYNALOAD_LOGF
#define DYNALOAD_LOGF(...) do{fprintf( stderr, __VA_ARGS__ );}while(0)
#ifndef DYNALOAD_USES_STDIO_H
#define DYNALOAD_USES_STDIO_H
#endif //!DYNALOAD_USES_STDIO_H
#endif //!DYNALOAD_LOGF

#ifndef DYNALOAD_MEMSET
#define DYNALOAD_MEMSET(d,v,s) memset(d,v,s)
#ifndef DYNALOAD_USES_STRING_H
#define DYNALOAD_USES_STRING_H
#endif //!DYNALOAD_USES_STRING_H
#endif //!DYNALOAD_MEMSET

#ifndef DYNALOAD_STRLEN
#define DYNALOAD_STRLEN(x) strlen(x)
#ifndef DYNALOAD_USES_STRING_H
#define DYNALOAD_USES_STRING_H
#endif //!DYNALOAD_USES_STRING_H
#endif //!DYNALOAD_MEMSET

#ifdef DYNALOAD_USES_STDLIB_H
#include <stdlib.h>
#endif

#ifdef DYNALOAD_USES_STDIO_H
#include <stdio.h>
#endif

#ifdef DYNALOAD_USES_STRING_H
#include <string.h>
#endif

/*
 * reduce the amount of junk brought in by the windows header
 */
#if HF_PLATFORM == HF_PLATFORM_WIN
#	define NOATOM
//#	define NOGDI
#	define NOGDICAPMASKS
#	define NOMETAFILE
#	define NOMINMAX
#	define NOSYSMETRICS
#	define NOTEXTMETRIC
#	define NORASTEROPS
#	define NOSCROLL
#	define NOCOMM
#	define NOKANJI
#	define NOCRYPT
#	define NOMCX
#	define NOWH
#	define NOSOUND
//#	define NOMSG
//#	define NOOPENFILE
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif

#if HF_PLATFORM == HF_PLATFORM_OSX
#	include <sys/sysctl.h>
#endif

//! memcpy returning pointer to last byte (mempcpy)
static any dynaload_mempcpy(
	void * HF_RES destination, const void * HF_RES source, hf_size size )
{
	DYNALOAD_MEMCPY( destination, source, size );

	return (any) ( ( (u08*) destination ) + size );
}

//! strcpy that guarantees null-terminated strings
static char * dynaload_strcpy(
	char * HF_RES dest, const char * HF_RES src, hf_size size )
{
	hf_count src_len = DYNALOAD_STRLEN( src );
	if ( src_len < size )
	{
		*((char *)dynaload_mempcpy( dest, src, src_len  )) = '\0';
	}
	else // truncate
	{
		*((char *)dynaload_mempcpy( dest, src, size - 1 )) = '\0';
	}
	return dest;
}

//! length of static strings in dynaload
#define DYNALOAD_STRSIZE 512

//! private DYNALOAD data
typedef struct S_DYNALOAD
{
	char libname[ DYNALOAD_STRSIZE ]; // name of library/module (DLL)

	// platform-specific module handle
#	if   HF_PLATFORM == HF_PLATFORM_WIN
	HMODULE module;  // Handle to Module
#	elif HF_PLATFORM == HF_PLATFORM_LINUX || HF_PLATFORM == HF_PLATFORM_OSX
	void*   library; // Handle to dynlib
#	else
#		error "this platform isn't supported by dynaload :-("
#	endif
	
} s_dynaload;


s_dynaload* dynaload_create( cstr library_name, hbool * opt_loaded )
{
	s_dynaload* dl = DYNALOAD_MALLOC( sizeof(s_dynaload) );
	
	if ( dl )
	{
		DYNALOAD_MEMSET( dl, 0, sizeof(s_dynaload) ); // clear the memory
		
		if ( library_name )
		{
			if ( opt_loaded )
				*opt_loaded = dynaload_loadlibrary( dl, library_name );
			else
				dynaload_loadlibrary( dl, library_name );
		}
	}
	
	return dl;
}


void dynaload_destroy( s_dynaload * dl )
{
	if ( dl )
	{
		dynaload_exitlibrary( dl ); // close the library (if open)
		DYNALOAD_FREE( dl );        // deallocate dynaload
	}
}


hbool dynaload_loadlibrary(
	s_dynaload * dl,
	cstr         library_name )
{
	if ( dl )
	{
		dynaload_exitlibrary( dl ); // close the library (if open)
		
		if ( !dynaload_strcpy( dl->libname, library_name, DYNALOAD_STRSIZE ) )
		{
			DYNALOAD_LOGF( "cannot store module name '%s'", library_name );
			return hf_false;
		}
		
		// loading on a Windows platform
#	if HF_PLATFORM == HF_PLATFORM_WIN
		
		dl->module  = LoadLibraryA( dl->libname );
		
		if ( !dl->module )
		{
			DYNALOAD_LOGF( "cannot open dynamic module '%s'", dl->libname );
			return hf_false;
		}
		
		
		// loading on a UNIX-like platform
#	elif HF_PLATFORM == HF_PLATFORM_LINUX || HF_PLATFORM == HF_PLATFORM_OSX
		
		dl->library = dlopen( library_name, RTLD_LAZY );
		
		if ( !dl->library )
		{
			DYNALOAD_LOGF( "cannot open dynamic module '%s' (%s)",
				dl->libname, dlerror() );
			
			return hf_false;
		}
		
#	endif
	}
	
	return dynaload_is_loaded( dl );
}

void dynaload_exitlibrary( s_dynaload * dl )
{
	if ( dl )
	{
		// Library shutdown on the Windows platform (FreeLibrary)
#		if HF_PLATFORM == HF_PLATFORM_WIN
		
		if ( dl->module )               // check for handle, if available,
			FreeLibrary( dl->module ); // closes the library
		
		dl->module = 0;
		
		// Library shutdown on a UNIX-like platform (dlclose)
#		elif HF_PLATFORM == HF_PLATFORM_LINUX || HF_PLATFORM == HF_PLATFORM_OSX
		
		if ( dl->library )
			if ( dlclose( dl->library ) != 0 )
			{
				dl->library = 0;
				DYNALOAD_LOGF( "error calling dlclose: %s", dlerror() );
			}
		
#		endif
		
		// set the name to '<closed>'
		if ( !dynaload_strcpy( dl->libname, "<closed>", DYNALOAD_STRSIZE ) )
			DYNALOAD_LOGF( "cannot store <closed> module name" );
	}
}

hbool dynaload_is_loaded( const s_dynaload * dl )
{
	// Check for a module handle on the Windows platform
#	if HF_PLATFORM == HF_PLATFORM_WIN
	
	return dl && dl->module ? 1 : 0;
	
	// Check for a library handle on a UNIX-like platform
#	elif HF_PLATFORM == HF_PLATFORM_LINUX || HF_PLATFORM == HF_PLATFORM_OSX
	
	return dl && dl->library ? 1 : 0;
	
#	endif
}

void* dynaload_procload(
	s_dynaload * dl,
	cstr         function_name,
	hbool      * success )
{
	void* ret = nullp;
	
	if ( dynaload_is_loaded( dl ) )
	{
		// Procedure loading on the Windows platform (GetProcAddress)
#		if HF_PLATFORM == HF_PLATFORM_WIN
		
		ret = (void*) GetProcAddress( dl->module, function_name );
		if ( ret == nullp )
			DYNALOAD_LOGF( "missing function '%s' in module '%s'",
				            function_name, dl->libname );
		
		// Procedure loading on a UNIX-like platform (dlsym)
#		elif HF_PLATFORM == HF_PLATFORM_LINUX || HF_PLATFORM == HF_PLATFORM_OSX
		
		ret = (void*) dlsym( dl->library, function_name );
		
#		endif
	}
	else
		DYNALOAD_LOGF(
			"module '%s' wasn't loaded; ignoring procload '%s'",
			dl->libname, function_name );
	
	if ( success )
		*success = ret ? 1 : 0;
	
	return ret;
}

#endif // DYNALOAD_IMPLEMENTATION
#ifdef __cplusplus
}
#endif
#endif /* HEADER_DYNALOAD_H_INCLUDED_ */
