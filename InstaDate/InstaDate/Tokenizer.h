/* ***************************************************************************

Programmer: Todd Pickell

Filename: Tokenizer.h

Requirements: None

Includes: 
#include "StdAfx.h"

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: this file contains a function to split a string into substrings by a token, 
I tried to model this after StringTokenizer in Java that I am familiar with
except without the functionality of the enumerable implementation I couldn't 
figure out how to include hasMoreTokens() && nextToken() so it just crams the results into a vector.

************************************************************************* */

#pragma once
#include "stdafx.h"

#define MAX_32BIT_INT 2147483647

//split strings up by token 
//push substrings to stack

namespace Tokenizer
{
	namespace
	{
		void split_whitespace( const std::string & str, std::vector< std::string > & result, int maxsplit )
		{
			std::string::size_type i, j, len = str.size();
			for (i = j = 0; i < len; )
			{

				while ( i < len && ::isspace( str[i] ) ) i++;
				j = i;

				while ( i < len && ! ::isspace( str[i]) ) i++;



				if (j < i)
				{
					if ( maxsplit-- <= 0 ) break;

					result.push_back( str.substr( j, i - j ));

					while ( i < len && ::isspace( str[i])) i++;
					j = i;
				}
			}
			if (j < len)
			{
				result.push_back( str.substr( j, len - j ));
			}
		}
	}
	//pass in the string to split, the vector to store the substrings in and the token to split with
	void split( const std::string &str, std::vector< std::string > &result, const std::string &sep = "", int maxsplit = -1)
    {
        result.clear();

        if ( maxsplit < 0 ) maxsplit = MAX_32BIT_INT;//result.max_size();


        if ( sep.size() == 0 )
        {
            split_whitespace( str, result, maxsplit );
            return;
        }

        std::string::size_type i,j, len = str.size(), n = sep.size();

        i = j = 0;

        while ( i+n <= len )
        {
            if ( str[i] == sep[0] && str.substr( i, n ) == sep )
            {
                if ( maxsplit-- <= 0 ) break;

                result.push_back( str.substr( j, i - j ) );
                i = j = i + n;
            }
            else
            {
                i++;
            }
        }

        result.push_back( str.substr( j, len-j ) );
    }
}