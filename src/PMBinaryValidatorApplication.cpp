/* Copyright (c) 2012, Massimo Gengarelli <massimo.gengarelli@gmail.com>
 *
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "PMBinaryValidatorApplication.h"

#include <string>
#include <iostream>

#include <sys/types.h>
#include <dirent.h>

#include <PM_Validator.h>
#include <PM_TokenElement.h>

namespace PhantomMenace
{
namespace BinaryValidator
{

Application* Application::_instance = 0;


Application::Application()
	: isFileNameSet(false),
	  isInputStringSet(false),
	  aParsingEnvironmentVector(0)
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
	isFileNameSet = true;
}

void Application::setString(const std::string& iString)
{
	anInputString = iString;
	isInputStringSet = true;
}

void Application::setDirectory(const std::string& iDirectory)
{
	aDirectory = iDirectory;
	isDirectorySet = true;
}

bool Application::validateString() throw (std::runtime_error)
{
	if (!isFileNameSet && !isDirectorySet)
	{
		throw std::runtime_error("filename or directory not set");
	}

	if (isFileNameSet && isDirectorySet)
	{
		throw std::runtime_error("both directory and filename can't be set");
	}

	if (!isInputStringSet)
	{
		throw std::runtime_error("string not set");
	}

	if (isFileNameSet)
	{
		if (!parsingEnvironment.parseFromFile(aFileName))
		{
			throw std::runtime_error("couldn't find filename!");
		}
	}

	if (isDirectorySet)
	{
		// Parse the whole directory and build the vector of PE
		DIR* aDirectory;
		struct dirent* aDirent;

		if ((aDirectory = opendir(this->aDirectory.c_str())) == 0)
		{
			throw std::runtime_error("couldn't parse directory");
		}

		while ((aDirent = readdir(aDirectory)) != 0)
		{
			if (aDirent->d_type == DT_DIR)
				continue;

			std::string aFileName = this->aDirectory + "/" + aDirent->d_name;
			if (aFileName.find(".ini") != std::string::npos)
			{
				PhantomMenace::ParsingEnvironment* aPE =
						new PhantomMenace::ParsingEnvironment();
				try
				{
					if (aPE->parseFromFile(aFileName))
					{
						if (aPE->isEnvironmentValid())
						{
							aParsingEnvironmentVector.push_back(aPE);
						}

						else delete aPE;
					}

					else delete aPE;
				}
				catch (...)
				{
					continue;
				}
			}
		}
	}

	try
	{
		if (isFileNameSet)
		{
			PhantomMenace::Validator validator(parsingEnvironment);
			if (validator.validateString(anInputString))
			{
				generateOutputString(parsingEnvironment);
				return true;
			}

			else return false;
		}

		else if (isDirectorySet)
		{
			// Try to validate against every grammar in the vector
			std::vector<PhantomMenace::ParsingEnvironment*>::iterator ite;
			for (ite = aParsingEnvironmentVector.begin();
					ite != aParsingEnvironmentVector.end();
					++ite)
			{
				PhantomMenace::Validator aValidator(**ite);
				if (aValidator.validateString(anInputString))
				{
					generateOutputString(**ite);
					return true;
				}
			}

			return false;
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

void Application::generateOutputString(PhantomMenace::ParsingEnvironment iParsingEnv)
{
	anOutputString += "Grammar name   : ";
	anOutputString += iParsingEnv.getGrammar().getElementName();
	anOutputString += "\n";
	anOutputString += "Grammar created: ";
	anOutputString += iParsingEnv.getGrammar().getCreationDate();
	anOutputString += "\n";
	anOutputString += "Grammar author : ";
	anOutputString += iParsingEnv.getGrammar().getAuthor();
	anOutputString += " <";
	anOutputString += iParsingEnv.getGrammar().getAuthorEmail();
	anOutputString += ">\n\n";

	ElementVector_t::const_iterator ite;
	for (ite = iParsingEnv.getElements().begin();
		 ite != iParsingEnv.getElements().end();
		 ++ite)
	{
		anOutputString += "Element found: ";
		anOutputString += (*ite).getElementName();
		anOutputString += "\n";

		anOutputString += "   with value: ";
		anOutputString += (*ite).getElementValue();
		anOutputString += "\n\n";
	}
}


}
}


