/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/
#include "ExampleRenderer.h"
#include <MinSG/Core/Nodes/GeometryNode.h>
#include <MinSG/Helper/Helper.h>
#include <MinSG/Core/Nodes/ListNode.h>
#include <MinSG/Core/FrameContext.h>
#include <MinSG/SceneManagement/Exporter/ExporterTools.h>
#include <MinSG/SceneManagement/Importer/ImporterTools.h>
#include <MinSG/SceneManagement/SceneDescription.h>
#include <Geometry/Box.h>
#include <Rendering/RenderingContext/RenderingContext.h>
#include <Rendering/Shader/Shader.h>
#include <Rendering/Shader/Uniform.h>
#include <Rendering/Draw.h>
#include <Util/Graphics/Color.h>
#include <Util/IO/FileLocator.h>
#include <iostream>
#include <sstream>
#include <string>
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include <vector>
#include "happly.h"
#include "Camera.h"
#include "Shader.h"

namespace ExampleProject {
	
using namespace MinSG;

// Static method that creates a shader object
static Rendering::Shader* getShader() {
	static Rendering::Shader* shader = nullptr;
	if(shader)
		return shader;
	
	// Try to find shader files in one of these locations
	Util::FileLocator locator;
	locator.addSearchPath("./data/shader/");
	locator.addSearchPath("./ExampleProject/data/shader/");
	locator.addSearchPath("./extModules/ExampleProject/data/shader/");
	
	// Find shader files
	auto vsResult = locator.locateFile(Util::FileName("SimpleShader.vs"));
	auto fsResult = locator.locateFile(Util::FileName("SimpleShader.fs"));
	
	// test if files were found
	if(!vsResult.first || !fsResult.first) {
		WARN("Could not find shader files!");
		return nullptr;
	}
	shader = Rendering::Shader::loadShader(vsResult.second, fsResult.second);
	return shader;
}

// ------------------------------------

/**
 * Gets called before traversal.
 * The return value indicates if the traversal should continue or not.
 */
State::stateResult_t ExampleRenderer::doEnableState(FrameContext& context, Node* node, const RenderParam& rp) {
	// call superclass
	auto result = NodeRendererState::doEnableState(context, node, rp);
	if(result != State::STATE_OK)
		return result;

		
	
	// Try to find model files in one of these locations
	 Util::FileLocator locator;

	 
	 locator.addSearchPath("L:/PADrend/build/data/mesh/");
	
    

	 Util::Reference<MinSG::Node> gNode = MinSG::loadModel(Util::FileName("chair_surfmesh_grd_alpha.ply"), 0, nullptr, locator );
	 MinSG::ListNode *ln = new MinSG::ListNode();
	 ln->addChild(gNode);

	 auto n = dynamic_cast<MinSG::ListNode * > (node);
     n->addChild(ln);
     rootNode = n;
	
     //Add code for attaching VBO data as material state  // TO DO
	

	
	// Get the shader
	Rendering::Shader* shader = getShader();
	
	// enable shader
	context.getRenderingContext().pushAndSetShader(shader);
	
	// You can also return State::STATE_SKIP_RENDERING to break the traversal (doDisableState does also not get called)
	return State::STATE_OK; // Continue traversal
}

// ------------------------------------

/**
 * Node renderer function.
 * Gets called for each node during traversal (after frustum culling if enabled).
 * The return value indicates if the traversal should continue or not.
 */
NodeRendererResult ExampleRenderer::displayNode(FrameContext& context, Node* node, const RenderParam& rp) {
		
	// Get the shader
	Rendering::Shader* shader = getShader();
	
	// get node position in world coordinates
	Geometry::Vec3 pos = node->getWorldOrigin();
	
	// get the bounding of the root node in world coordinates
	Geometry::Box rootBB = rootNode->getWorldBB();
	
	// normalize position to world bounding box
	pos -= rootBB.getMin();
	pos /= rootBB.getExtentMax();
	
	// use normalized position as colors
	Util::Color4f color(pos.x(), pos.y(), pos.z()); 
	
	// set shader uniform
	shader->setUniform(context.getRenderingContext(), Rendering::Uniform("colorOverride", color)); 
	
	// Draw the bounding box of the current node
	if(drawBoundingBox)
		Rendering::drawWireframeBox(context.getRenderingContext(), node->getWorldBB());
		
	// You can call NodeRendererResult::NODE_HANDLED to break traversal for the subtree
	// (The node also doesn't get drawn in this case)
	return NodeRendererResult::PASS_ON; // Continue traversal
}

// ------------------------------------

/**
 * Gets called after traversal.
 */
void ExampleRenderer::doDisableState(FrameContext& context, Node* node, const RenderParam& rp) {
	// call superclass
	NodeRendererState::doDisableState(context, node, rp);
	// disable shader
	context.getRenderingContext().popShader();
}


// ------------------------------------------------------------------------
// Serialization

using namespace MinSG::SceneManagement;

static const std::string STATE_TYPE("ExampleRenderer");
static const std::string ATTR_DRAW_BB("drawBB");

// Exporter function for this renderer so that we can save it in a .minsg file
static void exportState(ExporterContext& ctx, DescriptionMap& desc, State* state) {
	auto s = dynamic_cast<ExampleRenderer*>(state);
	desc.setString(Consts::ATTR_STATE_TYPE, STATE_TYPE);
	desc.setString(ATTR_DRAW_BB, Util::StringUtils::toString(s->getDrawBoundingBox()));
}

// Importer function for this renderer so that we can load it from a .minsg file
static bool importState(ImportContext& ctxt, const std::string& stateType, const DescriptionMap& d, Node* parent) {
	if(stateType != STATE_TYPE)
		return false;
	auto state = new ExampleRenderer;
	state->setDrawBoundingBox(d.getBool(ATTR_DRAW_BB, true));
	ImporterTools::finalizeState(ctxt, state, d);
	parent->addState(state);
	return true;
}

// Register the importer and exporter functions
static bool initExampleRenderer() {
	ExporterTools::registerStateExporter(ExampleRenderer::getClassId(), &exportState);
	ImporterTools::registerStateImporter(&importState);
	return true;
}
// directly register the importer/exporter when the library is loaded
static bool rendererRegistered = initExampleRenderer();

}
