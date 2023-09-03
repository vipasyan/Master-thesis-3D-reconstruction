/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/
#ifndef E_EXAMPLE_RENDERER_H_
#define E_EXAMPLE_RENDERER_H_

#include <E_MinSG/Core/States/E_NodeRendererState.h>

#include "ExampleRenderer.h"

namespace ExampleProject {

/**
 * EScript Wrapper class for ExampleRenderer 
 */
class E_ExampleRenderer : public E_MinSG::E_NodeRendererState {
		ES_PROVIDES_TYPE_NAME(ExampleRenderer) // For RTTI
	public:
		// allows wrappers for subclasses
		template<class, class, class> friend class Util::PolymorphicWrapperCreator;
	
		// Constructor
		E_ExampleRenderer(ExampleProject::ExampleRenderer* state) : E_NodeRendererState(state, typeObject) { }

		// Destructor
		virtual ~E_ExampleRenderer() = default;
		
		// ---
		static EScript::Type* typeObject; // the EScript type of this class
		
		// initialize EScript bindings
		static void init(EScript::Namespace* lib);

		// Allows accessing the wrapped class using the * operator
		const ExampleProject::ExampleRenderer* operator*() const { return static_cast<const ExampleProject::ExampleRenderer*>(ref().get()); }
		ExampleProject::ExampleRenderer* operator*() { return static_cast<ExampleProject::ExampleRenderer*>(ref().get()); }
};

}


// Provides conversion methods between the EScript wrapper class and the original class
ES_CONV_EOBJ_TO_OBJ(ExampleProject::E_ExampleRenderer, ExampleProject::ExampleRenderer*, **eObj)

#endif // E_EXAMPLE_RENDERER_H_
