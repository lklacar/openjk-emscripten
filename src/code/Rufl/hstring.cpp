/*
===========================================================================
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2013 - 2015, OpenJK contributors

This file is part of the OpenJK source code.

OpenJK is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License version 2 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, see <http://www.gnu.org/licenses/>.
===========================================================================
*/

////////////////////////////////////////////////////////////////////////////////////////
// RAVEN STANDARD USEFUL FUNCTION LIBRARY
//  (c) 2002 Activision
//
//
// Handle String
// -------------
// Handle strings are allocated once in a static buffer (with a hash index), and are
// never cleared out.  You should use these for very common string names which are
// redundant or intended to last a long time.
//
// Handle strings are also good for comparison and storage because they compare only
// the handles, which are simple unique integers.
//
////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////////////
#include "../qcommon/q_shared.h"
#include "hstring.h"
#include <string.h>
#include "../Ratl/hash_pool_vs.h"



////////////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////////////
#define MAX_HASH		16384			// How Many Hash
#define	BLOCK_SIZE		65536			// Size of a string storage block in bytes.







////////////////////////////////////////////////////////////////////////////////////////
// The Hash Pool
////////////////////////////////////////////////////////////////////////////////////////
typedef	ratl::hash_pool<BLOCK_SIZE, MAX_HASH>		TStrPool;


static TStrPool& Pool()
{
    static TStrPool TSP;
    return TSP;
}



////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////
hstring::hstring()
{
    mHandle	= 0;
#ifdef _DEBUG
    mStr	= 0;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////
hstring::hstring(const char *str)
{
    init(str);
}

////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////
hstring::hstring(const hstring &str)
{
    mHandle = str.mHandle;

#ifdef _DEBUG
    mStr	= str.mStr;
#endif
}


////////////////////////////////////////////////////////////////////////////////////////
// Assignment
////////////////////////////////////////////////////////////////////////////////////////
hstring& hstring::operator= (const char *str)
{
    init(str);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////////////
hstring& hstring::operator= (const hstring &str)
{
    mHandle = str.mHandle;

#ifdef _DEBUG
    mStr	= str.mStr;
#endif
    return *this;
}

const char*	hstring::c_str(void) const
{
    if (!mHandle)
    {
        return("");
    }
    return ((const char*)Pool()[mHandle]);
}

////////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////////
const char*	hstring::operator *(void) const
{
    return c_str();
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
int			hstring::length() const
{
    return strlen(c_str());
}

////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
int			hstring::handle() const
{
    return mHandle;
}



////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void		hstring::init(const char *str)
{
    if (!str)
    {
        mHandle = 0;
    }
    else
    {
        mHandle = Pool().get_handle(str, strlen(str)+1);		// +1 for null character
    }
#ifdef _DEBUG
    mStr	= (char*)Pool()[mHandle];
#endif
}


////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
float		hstring::ave_collisions()	{return Pool().average_collisions();}
int			hstring::total_strings()	{return Pool().total_allocs();}
int			hstring::total_bytes()		{return Pool().size();}
int			hstring::total_finds()		{return Pool().total_finds();}
int			hstring::total_collisions()	{return Pool().total_collisions();}
#endif
