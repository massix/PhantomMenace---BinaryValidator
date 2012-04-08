/*
 * PMBinaryValidator.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: massi
 */

#include <iostream>
#include <cstdlib>
#include <exception>

#include "PMBinaryValidatorApplication.h"
#include <PM_ParsingEnvironment.h>
#include <PM_Validator.h>

#define PRINTUSAGE() {app.printUsage(std::string(argv[0])); exit(EXIT_SUCCESS);}

int main(int argc, char *argv[])
{
	PhantomMenace::ParsingEnvironment parsingEnvironment;
	PhantomMenace::BinaryValidator::Application& app =
			PhantomMenace::BinaryValidator::Application::getInstance();

	for (int i = 0; i < argc; i++)
	{
		std::string arg(argv[i]);

		if (arg == "-f" || arg == "--file")
		{
			if (++i == argc)
				PRINTUSAGE()
			else
				app.setFileName(std::string(argv[i]));
		}

		if (arg == "-d" || arg == "--directory")
		{
			if (++i == argc)
				PRINTUSAGE()
			else
			{
				std::string directory(argv[i]);
				std::cout << "directory: " << directory << std::endl;
			}
		}

		if (arg == "-s" || arg == "--string")
		{
			if (++i == argc)
				PRINTUSAGE()
			else
				app.setString(std::string(argv[i]));
		}

		if (arg == "-h" || arg == "--help")
		{
			PRINTUSAGE()
		}
	}

	try
	{
		if (app.validateString())
			app.printLog();
		else
			std::cout << "String can't be validated against grammar\n";
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	PhantomMenace::BinaryValidator::Application::deleteInstance();

	return 0;
}
