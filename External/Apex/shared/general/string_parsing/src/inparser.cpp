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
#include <assert.h>

#pragma warning(disable:4996)

#include "inparser.h"
#include "PsUserAllocated.h"
#include "foundation/PxAssert.h"

/** @file inparser.cpp
 * @brief        Parse ASCII text, in place, very quickly.
 *
 * This class provides for high speed in-place (destructive) parsing of an ASCII text file.
 * This class will either load an ASCII text file from disk, or can be constructed with a pointer to
 * a piece of ASCII text in memory.  It can only be called once, and the contents are destroyed.
 * To speed the process of parsing, it simply builds pointers to the original ascii data and replaces the
 * seperators with a zero byte to indicate end of string.  It performs callbacks to parse each line, in argc/argv format,
 * offering the option to cancel the parsing process at any time.
 *
 *
 * By default the only valid seperator is whitespace.  It will not treat commas or any other symbol as a separator.
 * However, you can specify up to 32 'hard' seperators, such as a comma, equal sign, etc. and these will act as valid
 * seperators and come back as part of the argc/argv data list.
 *
 * To use the parser simply inherit the pure virtual base class 'InPlaceParserInterface'.  Define the method 'ParseLine'.
 * When you invoke the Parse method on the InPlaceParser class, you will get an ARGC - ARGV style callback for each line
 * in the source file.  If you return 'false' at any time, it will abort parsing.  The entire thing is stack based, so you
 * can recursively call multiple parser instances.
 *
 * It is important to note.  Since this parser is 'in place' it writes 'zero bytes' (EOS marker) on top of the whitespace.
 * While it can handle text in quotes, it does not handle escape sequences.  This is a limitation which could be resolved.
 * There is a hard coded maximum limit of 512 arguments per line.
 *
 * Here is the full example usage:
 *
 *  InPlaceParser ipp("parse_me.txt");
 *
 *    ipp.Parse(this);
 *
 *  That's it, and you will receive an ARGC - ARGV callback for every line in the file.
 *
 *  If you want to parse some text in memory of your own. (It *MUST* be terminated by a zero byte, and lines seperated by carriage return
 *  or line-feed.  You will receive an assertion if it does not.  If you specify the source data than *you* are responsible for that memory
 *  and must de-allocate it yourself.  If the data was loaded from a file on disk, then it is automatically de-allocated by the InPlaceParser.
 *
 *  You can also construct the InPlaceParser without passing any data, so you can simply pass it a line of data at a time yourself.  The
 *  line of data should be zero-byte terminated.
*/

//==================================================================================

namespace physx
{
	namespace general_string_parsing2
	{

void InPlaceParser::SetFile(const char *fname)
{
	if ( mMyAlloc )
	{
		PX_FREE(mData);
	}
	mData = 0;
	mLen  = 0;
	mMyAlloc = false;

	FILE *fph = fopen(fname,"rb");
	if ( fph )
	{
		fseek(fph,0L,SEEK_END);
		mLen = ftell(fph);
		fseek(fph,0L,SEEK_SET);

		if ( mLen )
		{
			mData = (char *) PX_ALLOC(sizeof(char)*(mLen+1), PX_DEBUG_EXP("InPlaceParser"));
			PxI32 read = (PxI32)fread(mData,mLen,1,fph);
			if ( !read )
			{
				PX_FREE(mData);
				mData = 0;
			}
			else
			{
				mData[mLen] = 0; // zero byte terminate end of file marker.
				mMyAlloc = true;
			}
		}
		fclose(fph);
	}
}

//==================================================================================
InPlaceParser::~InPlaceParser(void)
{
	if ( mMyAlloc )
	{
		PX_FREE(mData);
	}
}

//==================================================================================
bool InPlaceParser::IsHard(char c)
{
	return mHard[(unsigned char)c] == ST_HARD;
}

//==================================================================================
char * InPlaceParser::AddHard(PxI32 &argc,const char **argv,char *foo)
{
	while ( IsHard(*foo) )
	{
		const char *hard = &mHardString[*foo*2];
		if ( argc < MAXARGS )
		{
			argv[argc++] = hard;
		}
		++foo;
	}
	return foo;
}

//==================================================================================
bool   InPlaceParser::IsWhiteSpace(char c)
{
	return mHard[(unsigned char)c] == ST_SOFT;
}

//==================================================================================
char * InPlaceParser::SkipSpaces(char *foo)
{
	while ( !EOS(*foo) && IsWhiteSpace(*foo) ) 
		++foo;
	return foo;
}

//==================================================================================
bool InPlaceParser::IsNonSeparator(char c)
{
	return ( !IsHard(c) && !IsWhiteSpace(c) && c != 0 );
}

//==================================================================================
PxI32 InPlaceParser::ProcessLine(PxI32 lineno,char *line,InPlaceParserInterface *callback)
{
	PxI32 ret = 0;

	const char *argv[MAXARGS];
	PxI32 argc = 0;

	char *foo = line;

	while ( !EOS(*foo) && argc < MAXARGS )
	{
		foo = SkipSpaces(foo); // skip any leading spaces

		if ( EOS(*foo) ) 
			break;

		if ( *foo == mQuoteChar ) // if it is an open quote
		{
			++foo;
			if ( argc < MAXARGS )
			{
				argv[argc++] = foo;
			}
			while ( !EOS(*foo) && *foo != mQuoteChar ) 
				++foo;
			if ( !EOS(*foo) )
			{
				*foo = 0; // replace close quote with zero byte EOS
				++foo;
			}
		}
		else
		{
			foo = AddHard(argc,argv,foo); // add any hard separators, skip any spaces

			if ( IsNonSeparator(*foo) )  // add non-hard argument.
			{
				bool quote  = false;
				if ( *foo == mQuoteChar )
				{
					++foo;
					quote = true;
				}

				if ( argc < MAXARGS )
				{
					argv[argc++] = foo;
				}

				if ( quote )
				{
					while (*foo && *foo != mQuoteChar ) 
						++foo;
					if ( *foo ) 
						*foo = 32;
				}

				// continue..until we hit an eos ..
				while ( !EOS(*foo) ) // until we hit EOS
				{
					if ( IsWhiteSpace(*foo) ) // if we hit a space, stomp a zero byte, and exit
					{
						*foo = 0;
						++foo;
						break;
					}
					else if ( IsHard(*foo) ) // if we hit a hard separator, stomp a zero byte and store the hard separator argument
					{
						const char *hard = &mHardString[*foo*2];
						*foo = 0;
						if ( argc < MAXARGS )
						{
							argv[argc++] = hard;
						}
						++foo;
						break;
					}
					++foo;
				} // end of while loop...
			}
		}
	}

	if ( argc )
	{
		ret = callback->ParseLine(lineno, argc, argv );
	}

	return ret;
}


PxI32  InPlaceParser::Parse(const char *str,InPlaceParserInterface *callback) // returns true if entire file was parsed, false if it aborted for some reason
{
  PxI32 ret = 0;

  mLen = (PxI32)strlen(str);
  if ( mLen )
  {
    mData = (char *)PX_ALLOC(mLen+1, PX_DEBUG_EXP("InPlaceParser"));
    strcpy(mData,str);
    mMyAlloc = true;
    ret = Parse(callback);
  }
  return ret;
}

//==================================================================================
// returns true if entire file was parsed, false if it aborted for some reason
//==================================================================================
PxI32  InPlaceParser::Parse(InPlaceParserInterface *callback)
{
	PxI32 ret = 0;
	PX_ASSERT( callback );
	if ( mData )
	{
		PxI32 lineno = 0;

		char *foo   = mData;
		char *begin = foo;

		while ( *foo )
		{
			if ( isLineFeed(*foo) )
			{
				++lineno;
				*foo = 0;
				if ( *begin ) // if there is any data to parse at all...
				{
          bool snarfed = callback->preParseLine(lineno,begin);
          if ( !snarfed )
          {
  					PxI32 v = ProcessLine(lineno,begin,callback);
  					if ( v )
  						ret = v;
          }
				}

				++foo;
				if ( *foo == 10 )
					++foo; // skip line feed, if it is in the carraige-return line-feed format...
				begin = foo;
			}
			else
			{
				++foo;
			}
		}

		lineno++; // lasst line.

		PxI32 v = ProcessLine(lineno,begin,callback);
		if ( v )
			ret = v;
	}
	return ret;
}

//==================================================================================
void InPlaceParser::DefaultSymbols(void)
{
	SetHardSeparator(',');
	SetHardSeparator('(');
	SetHardSeparator(')');
	SetHardSeparator('=');
	SetHardSeparator('[');
	SetHardSeparator(']');
	SetHardSeparator('{');
	SetHardSeparator('}');
	SetCommentSymbol('#');
}

//==================================================================================
// convert source string into an arg list, this is a destructive parse.
//==================================================================================
const char ** InPlaceParser::GetArglist(char *line,PxI32 &count)
{
	const char **ret = 0;

	PxI32 argc = 0;

	char *foo = line;

	while ( !EOS(*foo) && argc < MAXARGS )
	{
		foo = SkipSpaces(foo); // skip any leading spaces

		if ( EOS(*foo) )
			break;

		if ( *foo == mQuoteChar ) // if it is an open quote
		{
			++foo;
			if ( argc < MAXARGS )
			{
				argv[argc++] = foo;
			}
			while ( !EOS(*foo) && *foo != mQuoteChar ) 
				++foo;
			if ( !EOS(*foo) )
			{
				*foo = 0; // replace close quote with zero byte EOS
				++foo;
			}
		}
		else
		{
			foo = AddHard(argc,argv,foo); // add any hard separators, skip any spaces

			if ( IsNonSeparator(*foo) )  // add non-hard argument.
			{
				bool quote  = false;
				if ( *foo == mQuoteChar )
				{
					++foo;
					quote = true;
				}

				if ( argc < MAXARGS )
				{
					argv[argc++] = foo;
				}

				if ( quote )
				{
					while (*foo && *foo != mQuoteChar ) 
						++foo;
					if ( *foo ) 
						*foo = 32;
				}

				// continue..until we hit an eos ..
				while ( !EOS(*foo) ) // until we hit EOS
				{
					if ( IsWhiteSpace(*foo) ) // if we hit a space, stomp a zero byte, and exit
					{
						*foo = 0;
						++foo;
						break;
					}
					else if ( IsHard(*foo) ) // if we hit a hard separator, stomp a zero byte and store the hard separator argument
					{
						const char *hard = &mHardString[*foo*2];
						*foo = 0;
						if ( argc < MAXARGS )
						{
							argv[argc++] = hard;
						}
						++foo;
						break;
					}
					++foo;
				} // end of while loop...
			}
		}
	}

	count = argc;
	if ( argc )
	{
		ret = argv;
	}

	return ret;
}


}; // end of namespace
};