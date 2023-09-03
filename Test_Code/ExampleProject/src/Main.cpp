/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/

//============================================
// Do not modify this file!!!
//============================================

#include "EScriptHelper.h" 
#include <EScript/EScript.h>
#include <iostream>

#ifndef LIBRARY_NAME
#define LIBRARY_NAME "Unknown" // Will be set by CMake
#endif

#ifndef LIBRARY_API
#define LIBRARY_API // Will be set by CMake
#endif

// get the static registry for all init-functions
static std::vector<ExampleProject::EScriptInitFunction_t>& getInitRegistry() {
	static std::vector<ExampleProject::EScriptInitFunction_t> registry;
	return registry;
}

// implementation of the 'registerEScriptInit' function declared in 'EScriptHelper.h'
bool ExampleProject::registerEScriptInit(const EScriptInitFunction_t& initFn) {
	getInitRegistry().emplace_back(initFn);
	return true;
}

/**
 * Main entry point for this library.
 * This function is called from EScript using the 'LibUtilExt/LibraryLoader' module.
 * The 'lib' parameter is usually the GLOBALS namespace from EScript.
 *
 * The 'extern "C"' signalizes the compiler that it should tread this function as a plain C function
 * which can be easily found during dynamic linking (otherwise the compiler mangles the name).
 * The LIBRARY_API macro is replaced by '__declspec(dllexport)' on windows, or '' on linux/mingw.
 * This is required for dlls when we want to call this method from the outside.
 */
extern "C" LIBRARY_API void initLibrary(EScript::Namespace* lib) {
	std::cout << "Loading Library: " << LIBRARY_NAME << "..." << std::endl;
	if(lib->getAttribute(LIBRARY_NAME).isNotNull()) {
		std::cerr << LIBRARY_NAME << " Library already loaded!" << std::endl;
	} else {
		// create a new namespace under the GLOBALS namespace with the name of this library
		auto * ns = new EScript::Namespace;
		declareConstant(lib, LIBRARY_NAME, ns);
		
		// Initialize EScript
		for(auto& initFn : getInitRegistry())
			initFn(ns);
	}
}
