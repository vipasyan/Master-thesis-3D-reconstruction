/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/
#include "E_ExampleRenderer.h"
#include "../EScriptHelper.h"

#include <EScript/EScript.h>

namespace ExampleProject {

// static initialization
EScript::Type* E_ExampleRenderer::typeObject = nullptr;

//! Initializes the EScript type
void E_ExampleRenderer::init(EScript::Namespace* lib) {
	// Create a new EScript type that inherits from NodeRendererState
	typeObject = new EScript::Type(E_NodeRendererState::getTypeObject());
	
	// Assign the Type object to a variable in our namespace (ExampleProject.ExampleRenderer)
	declareConstant(lib,getClassName(),typeObject);
	
	// Create factory for the wrapper class
	addFactory<ExampleRenderer, E_ExampleRenderer>();

	//! [ESMF] new ExampleProject.ExampleRenderer
	ES_CTOR(typeObject, 0, 0, EScript::create(new ExampleProject::ExampleRenderer))
	
	//! [ESMF] self ExampleRenderer.setDrawBoundingBox(Bool)
	ES_MFUN(typeObject, ExampleRenderer, "setDrawBoundingBox", 1, 1, (
		thisObj->setDrawBoundingBox(parameter[0].toBool()), thisEObj))
		
	//! [ESMF] Bool ExampleRenderer.getDrawBoundingBox()
	ES_MFUN(typeObject, ExampleRenderer, "getDrawBoundingBox", 0, 0, 
		EScript::create(thisObj->getDrawBoundingBox()))
}

// ------------------------------------------------------------

// register the initializer method
static bool initRegistered = registerEScriptInit(E_ExampleRenderer::init);

}
