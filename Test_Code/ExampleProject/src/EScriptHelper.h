/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/

#ifndef ESCRIPT_HELPER_H_
#define ESCRIPT_HELPER_H_

#include <functional>

// Forward declaration.
namespace EScript {
class Namespace;
}

namespace ExampleProject {
	typedef std::function<void (EScript::Namespace* lib)> EScriptInitFunction_t;
	
	bool registerEScriptInit(const EScriptInitFunction_t& initFn);
} /* ExampleProject */

#endif /* end of include guard: ESCRIPT_HELPER_H_ */