/*
===========================================================================
Copyright (C) 1999 - 2005, Id Software, Inc.
Copyright (C) 2000 - 2013, Raven Software, Inc.
Copyright (C) 2001 - 2013, Activision, Inc.
Copyright (C) 2005 - 2015, ioquake3 contributors
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

#include "../server/exe_headers.h"

// tr_subs.cpp - common function replacements for modular renderer
#include "tr_local.h"

// HUNK

//int Hunk_MemoryRemaining( void ) {
//	return ri.Hunk_MemoryRemaining();
//}

// ZONE

void *R_Malloc( int iSize, memtag_t eTag, qboolean bZeroit ) {
	return ri.Malloc( iSize, eTag, bZeroit, 4 );
}

void R_Free( void *ptr ) {
	ri.Z_Free( ptr );
}

int R_MemSize( memtag_t eTag ) {
	return ri.Z_MemSize( eTag );
}

void R_MorphMallocTag( void *pvBuffer, memtag_t eDesiredTag ) {
	ri.Z_MorphMallocTag( pvBuffer, eDesiredTag );
}

void *R_Hunk_Alloc( int iSize, qboolean bZeroit ) {
	return ri.Malloc( iSize, TAG_HUNKALLOC, bZeroit, 4 );
}
