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
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "inparser.h"
#include "sutil.h"
#include "PsString.h"
#include "PsString.h"
#include "foundation/PxIntrinsics.h"
#include "foundation/PxAssert.h"


namespace physx
{
	namespace general_string_parsing2
	{

static char ToLower(char c)
{
	if ( c >= 'A' && c <= 'Z' ) c+=32;
	return c;
}

char *stristr(const char *str,const char *key)       // case insensitive str str
{
	PX_ASSERT( strlen(str) < 2048 );
	PX_ASSERT( strlen(key) < 2048 );
	char istr[2048];
	char ikey[2048];
	strncpy(istr,str,2048);
	strncpy(ikey,key,2048);
	physx::string::strlwr(istr);
	physx::string::strlwr(ikey);

	char *foo = strstr(istr,ikey);
	if ( foo )
	{
		PxU32 loc = (PxU32)(foo - istr);
		foo = (char *)str+loc;
	}

	return foo;
}

bool        isstristr(const char *str,const char *key)     // bool true/false based on case insenstive strstr
{
	bool ret = false;
	const char *found = strstr(str,key);
	if ( found ) ret = true;
	return ret;
}

PxU32 GetHex(PxU8 c)
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

PxU8 GetHEX1(const char *foo,const char **endptr)
{
	PxU32 ret = 0;

	ret = (GetHex(foo[0])<<4) | GetHex(foo[1]);

	if ( endptr )
	{
		*endptr = foo+2;
	}

	return (PxU8) ret;
}


PxU16 GetHEX2(const char *foo,const char **endptr)
{
	PxU32 ret = 0;

	ret = (GetHex(foo[0])<<12) | (GetHex(foo[1])<<8) | (GetHex(foo[2])<<4) | GetHex(foo[3]);

	if ( endptr )
	{
		*endptr = foo+4;
	}

	return (PxU16) ret;
}

PxU32 GetHEX4(const char *foo,const char **endptr)
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

PxU32 GetHEX(const char *foo,const char **endptr)
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


bool         IsWhitespace(char c)
{
	if ( c == ' ' || c == 9 || c == 13 || c == 10 || c == ',' ) return true;
	return false;
}


const char * SkipWhitespace(const char *str)
{
	while ( *str && IsWhitespace(*str) ) str++;
	return str;
}

#define MAXNUM 32

PxF32        GetFloatValue(const char *str,const char **next)
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

PxI32          GetIntValue(const char *str,const char **next)
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


bool CharToWide(const char *source,wchar_t *dest,PxI32 maxlen)
{
	bool ret = false;

	ret = true;
	mbstowcs(dest, source, maxlen );

	return ret;
}

bool WideToChar(const wchar_t *source,char *dest,PxI32 maxlen)
{
	bool ret = false;

	ret = true;
	wcstombs(dest, source, maxlen );

	return ret;
}



const char * GetTrueFalse(PxU32 state)
{
	if ( state ) return "true";
	return "false";
};


const char * FloatString(PxF32 v,bool binary)
{
	static char data[64*16];
	static PxI32  index=0;

	char *ret = &data[index*64];
	index++;
	if (index == 16 ) index = 0;

	if ( !physx::intrinsics::isFinite(v) )
  {
    PX_ALWAYS_ASSERT();
    strcpy(ret,"0"); // not a valid number!
  }
/***
	else if ( v == FLT_MAX )
	{
		strcpy(ret,"fltmax");
	}
	else if ( v == FLT_MIN )
	{
		strcpy(ret,"fltmin");
	}
***/
	else if ( v == 1 )
	{
		strcpy(ret,"1");
	}
	else if ( v == 0 )
	{
		strcpy(ret,"0");
	}
	else if ( v == - 1 )
	{
		strcpy(ret,"-1");
	}
	else
	{
		if ( binary )
		{
			PxU32 *iv = (PxU32 *) &v;
			physx::string::sprintf_s(ret,64,"%.4f$%x", v, *iv );
		}
		else
		{
			physx::string::sprintf_s(ret,64,"%.9f", v );
			const char *dot = strstr(ret,".");
			if ( dot )
			{
				PxI32 len = (PxI32)strlen(ret);
				char *foo = &ret[len-1];
				while ( *foo == '0' ) foo--;
				if ( *foo == '.' )
					*foo = 0;
				else
					foo[1] = 0;
			}
		}
	}

	return ret;
}


char * NextSep(char *str,char &c)
{
	while ( *str && *str != ',' && *str != ')' )
	{
		str++;
	}
	c = *str;
	return str;
}

PxI32 GetUserArgs(const char *us,const char *key,const char **args)
{
	PxI32 ret = 0;
	static char arglist[2048];
	strcpy(arglist,us);

	char keyword[512];
	physx::string::sprintf_s(keyword,512,"%s(", key );
	char *found = strstr(arglist,keyword);
	if ( found )
	{
		found = strstr(found,"(");
		found++;
		args[ret] = found;
		ret++;
    static bool bstate = true;
		while ( bstate )
		{
			char c;
			found = NextSep(found,c);
			if ( found )
			{
				*found = 0;
				if ( c == ',' )
				{
					found++;
					args[ret] = found;
					ret++;
				}
				else
				{
					break;
				}
			}
		}
	}
	return ret;
}

bool GetUserSetting(const char *us,const char *key,PxI32 &v)
{
	bool ret = false;

	const char *argv[256];

	PxI32 argc = GetUserArgs(us,key,argv);
	if ( argc )
	{
		v = atoi( argv[0] );
		ret = true;
	}
	return ret;
}

bool GetUserSetting(const char *us,const char *key,const char * &v)
{
	bool ret = false;

	const char *argv[256];
	PxI32 argc = GetUserArgs(us,key,argv);
	if ( argc )
	{
		v = argv[0];
		ret = true;
	}
	return ret;
}

const char **  GetArgs(char *str,PxI32 &count) // destructable parser, stomps EOS markers on the input string!
{
	InPlaceParser ipp;

	return ipp.GetArglist(str,count);
}

const char * GetRootName(const char *fname)
{
	static char scratch[512];

	const char *source = fname;

	const char *start  = fname;

  while ( *source )
  {
  	if ( *source == '/' || *source == '\\' )
  	{
  		start = source+1;
  	}
  	source++;
  }

	strcpy(scratch,start);

  char *dot = strrchr( scratch, '.' );
 
  if ( dot )
  {
  	*dot = 0;
  }

	return scratch;
}

bool IsTrueFalse(const char *c)
{
	bool ret = false;

	if ( physx::string::stricmp(c,"true") == 0 || physx::string::stricmp(c,"1") == 0 ) ret = true;

  return ret;
}


bool IsDirectory(const char *fname,char *path,char *basename,char *postfix)
{
	bool ret = false;

	strcpy(path,fname);
	strcpy(basename,fname);

	char *foo = path;
	char *last = 0;

	while ( *foo )
	{
		if ( *foo == '\\' || *foo == '/' ) last = foo;
		foo++;
	}

	if ( last )
	{
		strcpy(basename,last+1);
		*last = 0;
		ret = true;
	}

	const char *scan = fname;

  static bool bstate = true;
	while ( bstate )
	{
		const char *dot = strstr(scan,".");
		if ( dot == 0 )
				break;
		scan = dot+1;
	}

	strcpy(postfix,scan);
	physx::string::strlwr(postfix);

	return ret;
}

bool hasSpace(const char *str) // true if the string contains a space
{
	bool ret = false;

  while ( *str )
  {
  	char c = *str++;
  	if ( c == 32 || c == 9 )
  	{
  		ret = true;
  		break;
  	}
  }
  return ret;
}


const char * lastDot(const char *src)
{
  const char *ret = 0;

  const char *dot = strchr(src,'.');
  while ( dot )
  {
    ret = dot;
    dot = strchr(dot+1,'.');
  }
  return ret;
}


const char *   lastChar(const char *src,char c)
{
  const char *ret = 0;

  const char *dot = (const char *)strchr(src,c);
  while ( dot )
  {
    ret = dot;
    dot = (const char *)strchr(dot+1,c);
  }
  return ret;
}


const char *         lastSlash(const char *src) // last forward or backward slash character, null if none found.
{
  const char *ret = 0;

  const char *dot = strchr(src,'\\');
  if  ( dot == 0 )
    dot = strchr(src,'/');
  while ( dot )
  {
    ret = dot;
    dot = strchr(ret+1,'\\');
    if ( dot == 0 )
      dot = strchr(ret+1,'/');
  }
  return ret;
}


const char	*fstring(PxF32 v)
{
	static char	data[64	*16];
	static PxI32 index = 0;

	char *ret	=	&data[index	*64];
	index++;
	if (index	== 16)
	{
		index	=	0;
	}

	if (v	== FLT_MIN)
	{
		return "-INF";
	}
	// collada notation	for	FLT_MIN	and	FLT_MAX
	if (v	== FLT_MAX)
	{
		return "INF";
	}

	if (v	== 1)
	{
		strcpy(ret,	"1");
	}
	else if	(v ==	0)
	{
		strcpy(ret,	"0");
	}
	else if	(v ==	 - 1)
	{
		strcpy(ret,	"-1");
	}
	else
	{
		physx::string::sprintf_s(ret,16, "%.9f", v);
		const	char *dot	=	strstr(ret,	".");
		if (dot)
		{
			PxI32	len	=	(PxI32)strlen(ret);
			char *foo	=	&ret[len - 1];
			while	(*foo	== '0')
			{
				foo--;
			}
			if (*foo ==	'.')
			{
				*foo = 0;
			}
			else
			{
				foo[1] = 0;
			}
		}
	}

	return ret;
}


#define MAXNUMERIC 32  // JWR  support up to 16 32 character long numeric formated strings
#define MAXFNUM    16

static	char  gFormat[MAXNUMERIC*MAXFNUM];
static PxI32    gIndex=0;

const char * formatNumber(PxI32 number) // JWR  format this integer into a fancy comma delimited string
{
	char * dest = &gFormat[gIndex*MAXNUMERIC];
	gIndex++;
	if ( gIndex == MAXFNUM ) gIndex = 0;

	char scratch[512];

#if defined (LINUX_GENERIC) || defined(LINUX) || defined(__CELLOS_LV2__) || defined(__APPLE__) || defined(ANDROID) || defined(PX_PS4)
	snprintf(scratch, 10, "%d", number);
#else
	itoa(number,scratch,10);
#endif

	char *str = dest;
	PxU32 len = (PxU32)strlen(scratch);
	for (PxU32 i=0; i<len; i++)
	{
		PxI32 place = (len-1)-i;
		*str++ = scratch[i];
		if ( place && (place%3) == 0 ) *str++ = ',';
	}
	*str = 0;

	return dest;
}


bool fqnMatch(const char *n1,const char *n2) // returns true if two fully specified file names are 'the same' but ignores case sensitivty and treats either a forward or backslash as the same character.
{
  bool ret = true;

  while ( *n1 )
  {
    char c1 = *n1++;
    char c2 = *n2++;
    if ( c1 >= 'A' && c1 <= 'Z' ) c1+=32;
    if ( c2 >= 'A' && c2 <= 'Z' ) c2+=32;
    if ( c1 == '\\' ) c1 = '/';
    if ( c2 == '\\' ) c2 = '/';
    if ( c1 != c2 )
    {
      ret = false;
      break;
    }
  }
  if ( ret )
  {
    if ( *n2 ) ret = false;
  }

  return ret;

}


bool           getBool(const char *str)
{
  bool ret = false;

  if ( physx::string::stricmp(str,"true") == 0 || strcmp(str,"1") == 0 || physx::string::stricmp(str,"yes") == 0 ) ret = true;

  return ret;
}


bool needsQuote(const char *str) // if this string needs quotes around it (spaces, commas, #, etc)
{
  bool ret = false;

  if ( str )
  {
    while ( *str )
    {
      char c = *str++;
      if ( c == ',' || c == '#' || c == 32 || c == 9 )
      {
        ret = true;
        break;
      }
    }
  }
  return ret;
}

void  normalizeFQN(const wchar_t *source,wchar_t *dest)
{
  char scratch[512];
  WideToChar(source,scratch,512);
  char temp[512];
  normalizeFQN(scratch,temp);
  CharToWide(temp,dest,512);
}

void  normalizeFQN(const char *source,char *dest)
{
  if ( source && strlen(source ) )
  {
    while ( *source )
    {
      char c = *source++;
      if ( c == '\\' ) c = '/';
      if ( c >= 'A' && c <= 'Z' ) c+=32;
      *dest++ = c;
    }
    *dest = 0;
  }
  else
  {
    *dest = 0;
  }
}



bool           endsWith(const char *str,const char *ends,bool caseSensitive)
{
  bool ret = false;

  PxI32 l1 = (PxI32) strlen(str);
  PxI32 l2 = (PxI32) strlen(ends);
  if ( l1 >= l2 )
  {
    PxI32 diff = l1-l2;
    const char *echeck = &str[diff];
    if ( caseSensitive )
    {
		if ( strcmp(echeck,ends) == 0 )
      {
        ret = true;
      }
    }
    else
    {
		if ( physx::string::stricmp(echeck,ends) == 0 )
      {
        ret = true;
      }
    }
  }
  return ret;
}

}; // end of namespace
};
