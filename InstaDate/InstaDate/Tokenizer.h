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


//split strings up by token 
//push substrings to stack

namespace myTokenizer
{
	namespace
	{
		void split_by_whitespace( const std::string & myStr, std::vector< std::string > & result, int maxsplit )
		{
			std::string::size_type i, j, len = myStr.size();
			for (i = j = 0; i < len; )
			{

				while ( i < len && ::isspace( myStr[i] ) ) i++;
				j = i;

				while ( i < len && ! ::isspace( myStr[i]) ) i++;



				if (j < i)
				{
					if ( maxsplit-- <= 0 ) break;

					result.push_back( myStr.substr( j, i - j ));

					while ( i < len && ::isspace( myStr[i])) i++;
					j = i;
				}
			}
			if (j < len)
			{
				result.push_back( myStr.substr( j, len - j ));
			}
		}
	}
	//pass in the string to split, the vector to store the substrings in and the token to split with
	void split_by_token( const std::string &myStr, std::vector< std::string > &result, const std::string &sep = "", int maxsplit = -1)
    {
        result.clear();

        if ( maxsplit < 0 ) maxsplit = 2147483647;//result.max_size();


        if ( sep.size() == 0 )
        {
            split_by_whitespace( myStr, result, maxsplit );
            return;
        }

        std::string::size_type i,j, len = myStr.size(), n = sep.size();

        i = j = 0;

        while ( i+n <= len )
        {
            if ( myStr[i] == sep[0] && myStr.substr( i, n ) == sep )
            {
                if ( maxsplit-- <= 0 ) break;

                result.push_back( myStr.substr( j, i - j ) );
                i = j = i + n;
            }
            else
            {
                i++;
            }
        }

        result.push_back( myStr.substr( j, len-j ) );
    }
}