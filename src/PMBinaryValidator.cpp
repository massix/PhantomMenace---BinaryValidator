/*
 * PMBinaryValidator.cpp
 *
 *  Created on: Apr 2, 2012
 *      Author: massi
 */

#include <iostream>

#include "PMBinaryValidatorApplication.h"
#include <PM_ParsingEnvironment.h>
#include <PM_Validator.h>

int main(int argc, char *argv[])
{
	PhantomMenace::ParsingEnvironment parsingEnvironment;
	PhantomMenace::BinaryValidator::Application& app =
			PhantomMenace::BinaryValidator::Application::getInstance();

	for (int i = 0; i < argc; i++)
	{
		std::string arg(argv[i]);

		if (arg == "-f")
		{
			if (++i == argc)
				std::cout << "which file?" << std::endl;
			else
			{
				std::string file(argv[i]);
				std::cout << "file: " << file << std::endl;
			}
		}

		else if (arg == "-d")
		{
			if (++i == argc)
				std::cout << "which directory?" << std::endl;
			else
			{
				std::string directory(argv[i]);
				std::cout << "directory: " << directory << std::endl;
			}
		}

		else if (arg == "-s")
		{
			if (++i == argc)
				std::cout << "which string?" << std::endl;
			else
			{
				std::string string(argv[i]);
				std::cout << "string: " << string << std::endl;
			}
		}

		else if (arg == "-h")
		{
			std::cout << "print usage\n";
		}
	}

	PhantomMenace::BinaryValidator::Application::deleteInstance();

	return 0;
}
