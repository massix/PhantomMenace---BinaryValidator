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


#ifndef PMBINARYVALIDATORAPPLICATION_H_
#define PMBINARYVALIDATORAPPLICATION_H_

#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <PM_ParsingEnvironment.h>

namespace PhantomMenace
{
namespace BinaryValidator
{


class Application
{
public:
	virtual ~Application();

	static Application& getInstance();
	static void printUsage(const std::string& iAppName);

	void setFileName(const std::string& iFileName);
	void setString(const std::string& iString);
	void setDirectory(const std::string& iDirectory);

	bool validateString() throw (std::runtime_error);
	void printLog() const;

private:
	std::string aFileName;
	std::string anInputString;
	std::string anOutputString;
	std::string aDirectory;

	bool isFileNameSet;
	bool isInputStringSet;
	bool isDirectorySet;

	void generateOutputString(PhantomMenace::ParsingEnvironment iParsingEnv);

	PhantomMenace::ParsingEnvironment parsingEnvironment;

	std::vector<PhantomMenace::ParsingEnvironment*> aParsingEnvironmentVector;



protected:
	Application();
	Application(const Application& right);
	Application& operator=(const Application& right);
};


} /* namespace BinaryValidator */
} /* namespace PhantomMenace */


#endif /* PMBINARYVALIDATORAPPLICATION_H_ */
