/* ***************************************************************************

Programmer: Todd Pickell

Filename: fileHandler.h

Requirements: None

Includes: 
#include "StdAfx.h"

Course: CISS-350A

Date: 11-1-12

Assignment: Week 2

Description: this is the file handler class that opens, read from, writes to and closes the files.

************************************************************************* */


#pragma once
class fileHandler
{
public:
	/*constructor that takes in a string for 
	the file name the object will have a handle to */
	fileHandler(std::string);

	~fileHandler(void);

	/* this method returns a vector<string> that
	contains one string for each line in the file */
	std::vector<std::string> getFile();

	/* this method takes a vector<string> and then writes
	each string on a separate line out to the file*/
	void putFile(std::vector<std::string> &);

private:
	std::string theFileName;
};