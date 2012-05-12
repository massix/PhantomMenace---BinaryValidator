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
	static Application _instance;
	return _instance;
}

void Application::printUsage(const std::string& iAppName)
{
	std::cout << "Usage: " << iAppName << " [options]\n"
			  << "    -f <filename>  -  Parse grammar from <filename>\n"
			  << "    -s <string>    -  Validate <string>\n"
			  << "    -d <directory> -  Tries to parse all the grammars in that"
					  " <directory>\n"
			  << "    -h             -  Print this page and exits\n"
			  << "    -v             -  Print the version and exits\n";
	std::cout << std::endl;
}

void Application::printVersion()
{
	std::cout
		<< "PhantomMenace Binary Validator version "
		<< VALIDATORVERSIONMAJ << "."
		<< VALIDATORVERSIONBIN << "-"
		<< VALIDATORVERSIONMIN << std::endl;
}

void Application::setFileName(const std::string& iFileName)
{
	aFileName = iFileName;
	isFileNameSet = true;
}

void Application::setString(const std::string& iString)
{
	aVectorString.push_back(iString);
	isInputStringSet = true;
}

void Application::setDirectory(const std::string& iDirectory)
{
	aDirectory = iDirectory;
	isDirectorySet = true;
}

bool Application::validateString() throw (std::runtime_error)
{
	bool return_value = true;

	/* Check consistency of the request */
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

	/* Get the parsing environments */
	if (isFileNameSet)
	{
		boost::shared_ptr<PhantomMenace::ParsingEnvironment> aParsingEnvironment(
				new PhantomMenace::ParsingEnvironment());

		if (!aParsingEnvironment->parseFromFile(aFileName))
		{
			throw std::runtime_error("couldn't find filename!");
		}

		aParsingEnvironmentVector.push_back(aParsingEnvironment);
	}

	else
	{
		// Parse the whole directory and build the vector of PE
		DIR* aDirectoryPtr = opendir(aDirectory.c_str());
		struct dirent* aDirent;

		if ((aDirectoryPtr = opendir(this->aDirectory.c_str())) == 0)
		{
			throw std::runtime_error("couldn't parse directory");
		}

		while ((aDirent = readdir(aDirectoryPtr)) != 0)
		{
			if (aDirent->d_type == DT_REG)
			{
				std::string aFileName(aDirectory + aDirent->d_name);
				if (aFileName.find(".ini") != std::string::npos)
				{
					boost::shared_ptr<PhantomMenace::ParsingEnvironment> aPE(
							new PhantomMenace::ParsingEnvironment());
					try
					{
						if (aPE->parseFromFile(aFileName))
						{
							if (aPE->isEnvironmentValid())
							{
								aParsingEnvironmentVector.push_back(aPE);
							}
						}
					}

					catch (...)
					{
						continue;
					}
				}
			}
		}
	}


	/* Validate strings! */
	std::vector<std::string>::const_iterator string_iterator;
	std::vector<boost::shared_ptr<PhantomMenace::ParsingEnvironment> >::iterator parsing_iterator;

	for (string_iterator = aVectorString.begin(); string_iterator != aVectorString.end(); ++string_iterator)
	{
		for (parsing_iterator = aParsingEnvironmentVector.begin(); parsing_iterator != aParsingEnvironmentVector.end(); ++parsing_iterator)
		{
			PhantomMenace::Validator aValidator(**parsing_iterator);
			if (aValidator.validateString(*string_iterator))
			{
				generateOutputString(*string_iterator, **parsing_iterator);
			}
		}
	}

	return return_value;
}

void Application::printLog() const
{
	std::cout << anOutputString << std::endl;
}

void Application::generateOutputString(
		const std::string& iString,
		const PhantomMenace::ParsingEnvironment& iParsingEnv)
{
	anOutputString += "\n\nString \"" + iString + "\" validated\n";
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


