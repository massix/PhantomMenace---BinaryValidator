/*
 * PMBinaryValidatorApplication.h
 *
 *  Created on: Apr 3, 2012
 *      Author: massi
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
	static Application* getInstancePtr();
	static void deleteInstance();
	static void printUsage(const std::string& iAppName);

	void setFileName(const std::string& iFileName);
	void setString(const std::string& iString);
	void setDirectory(const std::string& iDirectory);

	bool validateString() throw (std::runtime_error);
	void printLog() const;

private:
	static Application* _instance;

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
