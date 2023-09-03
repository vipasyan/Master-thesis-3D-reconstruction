/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/

// Create a new Type which inherits from MinSG.ScriptedNodeRendererState
static Renderer = new Type( MinSG.ScriptedNodeRendererState );
// Set the name of the Renderer (for GUI)
Renderer._printableName @(override) ::= $ScriptedExampleRenderer;

// load the shader
var vsFile = __DIR__ + "/../../data/shader/SimpleShader.vs";
var fsFile = __DIR__ + "/../../data/shader/SimpleShader.fs";
static shader = Rendering.Shader.loadShader(vsFile, fsFile);

// When adding @(init) to a variable, the variable gets initialized by the return value of the function.
Renderer.drawBoundingBox @(init) := fn() { return new Std.DataWrapper(true); };
Renderer.rootNode @(private) := void;

//--------------------

// Constructor
Renderer._constructor ::= fn() {
	// nothing to do here
};

//--------------------

/**
 * Gets called before traversal.
 * The return value indicates if the traversal should continue or not.
 */
Renderer.doEnableState @(override) ::= fn(node, params) {
	// Set the root node
	this.rootNode = node;
		
	// enable shader
	renderingContext.pushAndSetShader(shader);
	
	// You can also return MinSG.STATE_SKIP_RENDERING to break the traversal (doDisableState does also not get called)
	return MinSG.STATE_OK;
};

//--------------------

/**
 * Node renderer function.
 * Gets called for each node during traversal (after frustum culling if enabled).
 * The return value indicates if the traversal should continue or not.
 */
Renderer.displayNode @(override) ::= fn(node, params) {
	// get node position in world coordinates
	var pos = node.getWorldOrigin();
	
	// get the bounding of the root node in world coordinates
	var rootBB = rootNode.getWorldBB();
	
	// normalize position to world bounding box
	pos -= rootBB.getMin();
	pos /= rootBB.getExtentMax();
	
	// use normalized position as colors
	var color = new Util.Color4f(pos.x(), pos.y(), pos.z());
	
	// set shader uniform
	shader.setUniform(renderingContext, new Rendering.Uniform("colorOverride", Rendering.Uniform.VEC4F, [color]));
	
	// Draw the bounding box of the current node
	if(drawBoundingBox())
		Rendering.drawWireframeBox(renderingContext, node.getWorldBB());
		
	// You can call MinSG.FrameContext.NODE_HANDLED to break traversal for the subtree
	// (The node also doesn't get drawn in this case)
	return MinSG.FrameContext.PASS_ON; // Continue traversal
};


//--------------------

/**
 * Gets called after traversal.
 */
Renderer.doDisableState @(override) ::= fn(node, params) {
	// disable shader
	renderingContext.popShader();	
};

//----------------------------------------------------------------
// GUI
//----------------------------------------------------------------

// Register the renderer at the NodeEditor
registerExtension( 'NodeEditor_QueryAvailableStates' , Renderer->fn(states){
	if(Renderer!=this)
		return Extension.REMOVE_EXTENSION;
	states[ "[scripted] "+_printableName ] = this->fn(){return new this();};
});

// Create a config gui for the renderer
NodeEditor.registerConfigPanelProvider( Renderer, fn(renderer, panel) {
	panel += {
		GUI.TYPE : GUI.TYPE_BOOL,
		GUI.LABEL : "Draw bounding boxes",
		GUI.DATA_WRAPPER : renderer.drawBoundingBox,
	};
	panel++; // next row
});

// Register an importer for this renderer so that we can load it from a .minsg file
Std.module.on( 'LibMinSGExt/ScriptedStateImportersRegistry',fn(registry){
	registry[Renderer._printableName] = fn(description) {
		var state = new Renderer;
		state.drawBoundingBox(description['drawBoundingBox']);
		return state;
	};
});


// Register an exporter for this renderer so that we can save it in a .minsg file
Std.module.on( 'LibMinSGExt/ScriptedStateExportersRegistry',fn(registry){
	registry[Renderer._printableName] = fn(state,description){	
		description['drawBoundingBox'] = state.drawBoundingBox();
	};
});

// return the renderer so that we can use it as a module
return Renderer;