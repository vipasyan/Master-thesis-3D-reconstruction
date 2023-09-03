/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/
#ifndef EXAMPLE_RENDERER_H
#define EXAMPLE_RENDERER_H

#include <MinSG/Core/FrameContext.h>
#include <MinSG/Core/States/NodeRendererState.h>

// forward declaration
namespace MinSG {
class GeometryNode;
class Node;
}

namespace ExampleProject {

/**
 * A simple state that extends NodeRendererState.
 * If you don't need the displayNode method, just inherit from MinSG::State (and remove the method)
 */
class ExampleRenderer : public MinSG::NodeRendererState {
	PROVIDES_TYPE_NAME(ExampleRenderer) // For RTTI
	public:
		
		// default constructor
		ExampleRenderer() : MinSG::NodeRendererState(MinSG::FrameContext::DEFAULT_CHANNEL) {}
		// copy constructor
		ExampleRenderer(const ExampleRenderer& source) : MinSG::NodeRendererState(source) {}
		// destructor
		virtual ~ExampleRenderer() = default;
		// clones the object
		ExampleRenderer* clone() const override { return new ExampleRenderer(*this); }

		// getter/setter for drawBoundingBox
		void setDrawBoundingBox(bool v) { drawBoundingBox = v; }
		bool getDrawBoundingBox() const { return drawBoundingBox; }
	private:
		bool drawBoundingBox = true; // draw a bounding box around a node if enabled
		MinSG::Node* rootNode; // store the active root node
		
		/**
		 * Gets called before traversal.
		 * The return value indicates if the traversal should continue or not.
		 */
		stateResult_t doEnableState(MinSG::FrameContext& context, MinSG::Node* node, const MinSG::RenderParam& rp) override;
		
		/**
		 * Node renderer function.
		 * Gets called for each node during traversal (after frustum culling if enabled).
		 * The return value indicates if the traversal should continue or not.
		 */
		MinSG::NodeRendererResult displayNode(MinSG::FrameContext& context, MinSG::Node* node, const MinSG::RenderParam& rp) override;
		
		/**
		 * Gets called after traversal.
		 */
		void doDisableState(MinSG::FrameContext& context, MinSG::Node* node, const MinSG::RenderParam& rp) override;
};

}

#endif /* EXAMPLE_RENDERER_H */
