/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/
#include "EScriptHelper.h"

#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <iostream>

namespace ExampleProject {

// Output "Hello World!" to the console.
void helloWorld() {
	std::cout << "Hello World!" << std::endl;
}

// Return "Hello World!".
std::string getHelloWorld() {
	return "Hello World!";
}

// Initializes your EScript bindings
static void initExamples(EScript::Namespace* lib) {	
	
	// EScript macro to create the method ExampleProject.helloWorld()
	ES_FUNCTION(lib, "helloWorld1", 0, 0, {
		helloWorld();
		return thisEObj;
	})
	
	// shorter version
	ES_FUN(lib, "helloWorld2", 0, 0, (helloWorld(), thisEObj))
	
	// get hello world
	ES_FUN(lib, "getHelloWorld", 0, 0, getHelloWorld()) // automatically converts std::string to EScript String
		
	// Function with (optional) parameters (min 1, max 3) and return value
	ES_FUNCTION(lib, "testParam", 1, 3, {
		float p1 = parameter[0].toFloat();
		float p2 = parameter[1].toFloat(1.23); // with default value
		std::string s = parameter[2].toString("test");
		std::cout << "called testParam(" << p1 << ", " << p2 << ", " << s << ")" << std::endl;
		return EScript::Number::create(parameter.count()); // return the number of used parameters
	})
}

// Register the initializer method
static bool initRegistered = registerEScriptInit(initExamples);

}
