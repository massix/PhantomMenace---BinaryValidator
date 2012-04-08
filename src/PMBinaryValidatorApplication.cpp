/*
 * PMBinaryValidatorApplication.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: massi
 */

#include "PMBinaryValidatorApplication.h"

#include <string>
#include <iostream>

#include <PM_Validator.h>
#include <PM_TokenElement.h>

namespace PhantomMenace
{
namespace BinaryValidator
{

Application* Application::_instance = 0;


Application::Application()
	: isFileNameSet(false),
	  isInputStringSet(false)
{
}

Application::Application(const Application& right)
{
}

Application& Application::operator=(const Application& right)
{
	return *this;
}

Application::~Application()
{

}

Application& Application::getInstance()
{
	if (_instance == 0)
		_instance = new Application();

	return (*_instance);
}

Application* Application::getInstancePtr()
{
	if (_instance == 0)
		_instance = new Application();

	return _instance;
}

void Application::deleteInstance()
{

}

void Application::printUsage(const std::string& iAppName)
{
	std::cout << "Usage: " << iAppName << " [options]\n"
			  << "    -f <filename>  -  Parse grammar from <filename>\n"
			  << "    -s <string>    -  Validate <string>\n"
			  << "    -d <directory> -  Tries to parse all the grammars in that"
					  " <directory>\n"
			  << "    -h             -  Print this page and exits\n";
}


void Application::setFileName(const std::string& iFileName)
{
	aFileName = iFileName;
}

void Application::setString(const std::string& iString)
{
	anInputString = iString;
}

bool Application::validateString() throw (std::runtime_error)
{
	if (aFileName.length() < 1)
		throw std::runtime_error("filename not set");

	if (anInputString.length() < 1)
		throw std::runtime_error("string not set");

	if (!parsingEnvironment.parseFromFile(aFileName))
		throw std::runtime_error("couldn't find filename!");

	try
	{
		PhantomMenace::Validator validator(parsingEnvironment);
		if (validator.validateString(anInputString))
		{
			anOutputString += "Grammar name   : ";
			anOutputString += parsingEnvironment.getGrammar().getElementName();
			anOutputString += "\n";
			anOutputString += "Grammar created: ";
			anOutputString += parsingEnvironment.getGrammar().getCreationDate();
			anOutputString += "\n";
			anOutputString += "Grammar author : ";
			anOutputString += parsingEnvironment.getGrammar().getAuthor();
			anOutputString += " <";
			anOutputString += parsingEnvironment.getGrammar().getAuthorEmail();
			anOutputString += ">\n\n";

			ElementVector_t::const_iterator ite;
			for (ite = parsingEnvironment.getElements().begin();
				 ite != parsingEnvironment.getElements().end();
				 ++ite)
			{
				anOutputString += "Element found: ";
				anOutputString += (*ite).getElementName();
				anOutputString += "\n";

				anOutputString += "   with value: ";
				anOutputString += (*ite).getElementValue();
				anOutputString += "\n\n";
			}

			return true;
		}

		else return false;
	}
	catch (...)
	{
		return false;
	}

	/* We should never arrive here! */
	return false;
}

void Application::printLog() const
{
	std::cout << anOutputString << std::endl;
}


}
}


