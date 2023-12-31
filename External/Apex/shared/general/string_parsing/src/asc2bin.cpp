/*
 * Copyright 2009-2011 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>

#include "PsUserAllocated.h"
#include "asc2bin.h"

namespace physx
{
	namespace general_string_parsing2
	{

static inline bool         IsWhitespace(char c)
{
	if ( c == ' ' || c == 9 || c == 13 || c == 10 || c == ',' ) return true;
	return false;
}



static inline const char * SkipWhitespace(const char *str)
{
  if ( str )
  {
	  while ( *str && IsWhitespace(*str) ) str++;
  }
	return str;
}

static char ToLower(char c)
{
	if ( c >= 'A' && c <= 'Z' ) c+=32;
	return c;
}

static inline PxU32 GetHex(PxU8 c)
{
	PxU32 v = 0;
	c = ToLower(c);
	if ( c >= '0' && c <= '9' )
		v = c-'0';
	else
	{
		if ( c >= 'a' && c <= 'f' )
		{
			v = 10 + c-'a';
		}
	}
	return v;
}

static inline PxU8 GetHEX1(const char *foo,const char **endptr)
{
	PxU32 ret = 0;

	ret = (GetHex(foo[0])<<4) | GetHex(foo[1]);

	if ( endptr )
	{
		*endptr = foo+2;
	}

	return (PxU8) ret;
}


static inline unsigned short GetHEX2(const char *foo,const char **endptr)
{
	PxU32 ret = 0;

	ret = (GetHex(foo[0])<<12) | (GetHex(foo[1])<<8) | (GetHex(foo[2])<<4) | GetHex(foo[3]);

	if ( endptr )
	{
		*endptr = foo+4;
	}

	return (unsigned short) ret;
}

static inline PxU32 GetHEX4(const char *foo,const char **endptr)
{
	PxU32 ret = 0;

	for (PxI32 i=0; i<8; i++)
	{
		ret = (ret<<4) | GetHex(foo[i]);
	}

	if ( endptr )
	{
		*endptr = foo+8;
	}

	return ret;
}

static inline PxU32 GetHEX(const char *foo,const char **endptr)
{
	PxU32 ret = 0;

	while ( *foo )
	{
		PxU8 c = ToLower( *foo );
		PxU32 v = 0;
		if ( c >= '0' && c <= '9' )
			v = c-'0';
		else
		{
			if ( c >= 'a' && c <= 'f' )
			{
				v = 10 + c-'a';
			}
			else
				break;
		}
		ret = (ret<<4)|v;
		foo++;
	}

	if ( endptr ) *endptr = foo;

	return ret;
}




#define MAXNUM 32

static inline PxF32        GetFloatValue(const char *str,const char **next)
{
	PxF32 ret = 0;

	if ( next ) *next = 0;

	str = SkipWhitespace(str);

	char dest[MAXNUM];
	char *dst = dest;
	const char *hex = 0;

	for (PxI32 i=0; i<(MAXNUM-1); i++)
	{
		char c = *str;
		if ( c == 0 || IsWhitespace(c) )
		{
			if ( next ) *next = str;
			break;
		}
		else if ( c == '$' )
		{
			hex = str+1;
		}
		*dst++ = ToLower(c);
		str++;
	}

	*dst = 0;

	if ( hex )
	{
		PxU32 iv = GetHEX(hex,0);
		PxF32 *v = (PxF32 *)&iv;
		ret = *v;
	}
	else if ( dest[0] == 'f' )
	{
		if ( strcmp(dest,"fltmax") == 0 || strcmp(dest,"fmax") == 0 )
		{
			ret = FLT_MAX;
		}
		else if ( strcmp(dest,"fltmin") == 0 || strcmp(dest,"fmin") == 0 )
		{
			ret = FLT_MIN;
		}
	}
	else if ( dest[0] == 't' ) // t or 'true' is treated as the value '1'.
	{
		ret = 1;
	}
	else
	{
		ret = (PxF32)atof(dest);
	}
	return ret;
}

static inline PxI32          GetIntValue(const char *str,const char **next)
{
	PxI32 ret = 0;

	if ( next ) *next = 0;

	str = SkipWhitespace(str);

	char dest[MAXNUM];
	char *dst = dest;

	for (PxI32 i=0; i<(MAXNUM-1); i++)
	{
		char c = *str;
		if ( c == 0 || IsWhitespace(c) )
		{
			if ( next ) *next = str;
			break;
		}
		*dst++ = c;
		str++;
	}

	*dst = 0;

	ret = atoi(dest);

	return ret;
}



#ifdef PLAYSTATION3
#include <ctype.h> // for tolower()
#endif

enum Atype {  AT_FLOAT,  AT_INT,  AT_CHAR,  AT_BYTE,  AT_SHORT,  AT_STR,  AT_HEX1,  AT_HEX2,  AT_HEX4,  AT_LAST };

#define MAXARG 64

#if 0
void TestAsc2bin(void)
{
	Asc2Bin("1 2 A 3 4 Foo AB ABCD FFEDFDED",1,"f d c b h p x1 x2 x4", 0);
}
#endif

void * Asc2Bin(const char *source,const PxI32 count,const char *spec,void *dest)
{

	PxI32   cnt = 0;
	PxI32   size  = 0;

	Atype types[MAXARG];

	const char *ctype = spec;

	while ( *ctype )
	{
		switch ( ToLower(*ctype) )
		{
			case 'f': size+= sizeof(PxF32); types[cnt] = AT_FLOAT; cnt++;  break;
			case 'd': size+= sizeof(PxI32);   types[cnt] = AT_INT;   cnt++;  break;
			case 'c': size+=sizeof(char);   types[cnt] = AT_CHAR;  cnt++;  break;
			case 'b': size+=sizeof(char);   types[cnt] = AT_BYTE;  cnt++;  break;
			case 'h': size+=sizeof(short);  types[cnt] = AT_SHORT; cnt++;  break;
			case 'p': size+=sizeof(const char *);  types[cnt] = AT_STR; cnt++;  break;
			case 'x':
				{
					Atype type = AT_HEX4;
					PxI32 sz = 4;
					switch ( ctype[1] )
					{
						case '1':  type = AT_HEX1; sz   = 1; ctype++;  break;
						case '2':  type = AT_HEX2; sz   = 2; ctype++;  break;
						case '4':  type = AT_HEX4; sz   = 4; ctype++;  break;
					}
					types[cnt] = type;
					size+=sz;
					cnt++;
				}
				break;
		}
		if ( cnt == MAXARG ) return 0; // over flowed the maximum specification!
		ctype++;
	}

	bool myalloc = false;

	if ( dest == 0 )
	{
		myalloc = true;
		dest = (char *) PX_ALLOC(sizeof(char)*count*size, PX_DEBUG_EXP("Asc2BinCharArray"));
	}

	// ok...ready to parse lovely data....
	memset(dest,0,count*size); // zero out memory

	char *dst = (char *) dest; // where we are storing the results
	for (PxI32 i=0; i<count; i++)
	{
		for (PxI32 j=0; j<cnt; j++)
		{
			source = SkipWhitespace(source); // skip white spaces.

			if (source == NULL ||  *source == 0 ) // we hit the end of the input data before we successfully parsed all input!
			{
				if ( myalloc )
				{
					PX_FREE(dest);
				}
				return 0;
			}

			switch ( types[j] )
			{
				case AT_FLOAT:
					{
						PxF32 *v = (PxF32 *) dst;
						*v = GetFloatValue(source,&source);
						dst+=sizeof(PxF32);
					}
					break;
				case AT_INT:
					{
						PxI32 *v = (PxI32 *) dst;
						*v = GetIntValue( source, &source );
						dst+=sizeof(PxI32);
					}
					break;
				case AT_CHAR:
					{
						*dst++ = *source++;
					}
					break;
				case AT_BYTE:
					{
						char *v = (char *) dst;
						*v = (char)GetIntValue(source,&source);
						dst+=sizeof(char);
					}
					break;
				case AT_SHORT:
					{
						short *v = (short *) dst;
						*v = (unsigned short)GetIntValue( source,&source );
						dst+=sizeof(short);
					}
					break;
				case AT_STR:
					{
						const char **ptr = (const char **) dst;
						*ptr = source;
						dst+=sizeof(const char *);
						while ( *source && !IsWhitespace(*source) ) source++;
					}
					break;
				case AT_HEX1:
					{
						PxU32 hex = GetHEX1(source,&source);
						PxU8 *v = (PxU8 *) dst;
						*v = (PxU8)hex;
						dst+=sizeof(PxU8);
					}
					break;
				case AT_HEX2:
					{
						PxU32 hex = GetHEX2(source,&source);
						unsigned short *v = (unsigned short *) dst;
						*v = (unsigned short)hex;
						dst+=sizeof(unsigned short);
					}
					break;
				case AT_HEX4:
					{
						PxU32 hex = GetHEX4(source,&source);
						PxU32 *v = (PxU32 *) dst;
						*v = hex;
						dst+=sizeof(PxU32);
					}
					break;
				case AT_LAST: // Make compiler happy
					break;
			}
		}
	}

	return dest;
}

}; // end of namespace
};
