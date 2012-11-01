#pragma once
#include "stdafx.h"

//split strings up by token 
//push substrings to stack

namespace Tokenizer
{
	//pass in the sring to split, the vector to store the substrings in and the token to split with
	void splitIt(const std::string &str, std::vector<std::string> &strStack, const std::string &token)
    {
        std::string::size_type i, j, len, n;

		len = str.size();
		n = token.size();
        i = 0; 
		j = 0;

        while ( i+n <= len )
        {
			//find begining of next token and see if that matches whole token
            if (str[i] == token[0] && str.substr(i, n) == token)
            {
				//add substring before token to stack
                strStack.push_back(str.substr( j, i - j ));
				//after split reset trackers to begining of next word
                i = j = i + n;
            }
            else
            {
				//move to next char if token not found
                i++;
            }
        }

		//grab last substring and add it to stack
        strStack.push_back(str.substr( j, len-j ));
    }
}