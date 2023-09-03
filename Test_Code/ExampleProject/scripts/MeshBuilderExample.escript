/*
Any copyright is dedicated to the Public Domain.
http://creativecommons.org/publicdomain/zero/1.0/
Author: Sascha Brandt <sascha@brandt.graphics>
*/

// A simple script to build meshes using the MeshBuilder (and more)
// You can run it by using the 'F3' Quick-Dial menu or by opening the script using the file menu 'File->Load Script...' 

// Create a new scene
var scene = PADrend.createNewSceneRoot("new MinSG.ListNode");

// activate the scene
PADrend.selectScene(scene);

// Create a mesh vertex description with the vertex attributes (position, normal, color)
var vd = new Rendering.VertexDescription;
vd.appendPosition3D(); // 3xfloat (x,y,z)
vd.appendNormalByte(); // 4xbyte (x,y,z,0)
vd.appendColorRGBAByte(); // 4xbyte (r,g,b,a)

// Create a hexagonal grid of dimensions 100x100 and 128 rows&columns
// The same can be achieved by calling mb.addHexGrid(100, 100, 128, 128) on a MeshBuilder
var grid = Rendering.createHexGrid(vd, 100, 100, 128, 128);

// Let's get some noise
var scale = 10;
var transform = (new Geometry.Matrix4x4).scale(0.01,0.01,0.01); // scale matrix
for(var i=0; i<8; ++i) {
  Rendering.applyNoise(grid, scale*=0.5, transform.scale(2,2,2));
}
// applyNoise doesn't change the normals, therefore we need to recompute them
Rendering.calculateNormals(grid);

// Create a geometry node for the grid
var gridNode = new MinSG.GeometryNode(grid);

// Move the node to (-50,0,-50)
gridNode.setWorldOrigin(new Geometry.Vec3(-50,0,-50));

// Create a material state for the node
var state = new MinSG.MaterialState;
state.setAmbient(new Util.Color4f(0.6,0.6,0.65,1));
state.setDiffuse(new Util.Color4f(0.8,0.8,0.8,1));

// add the state to the node
gridNode += state;

// add the grid to the scene
scene += gridNode;

// ----------------------------------------------------------------

// Create a position accessor for the grid mesh
var pAcc = Rendering.PositionAttributeAccessor.create(grid);

// Get the position of the vertex at index 128*64 (8192) (should be the center of the grid)
var center = pAcc.getPosition(128*64);

// Create a mesh builder with default vertex attributes (position, normal, color, texture-coordinates)
// You can also use 'new Rendering.MeshBuilder(vd)' to set custom vertex attributes.
var mb = new Rendering.MeshBuilder;

// Matrix used for transformations
var m = new Geometry.Matrix4x4;
// Set translation component of the matrix to center
m.translate(gridNode.getWorldOrigin() + center);

// Set the position for all next operations
mb.setTransformation(m.translate(0,0.5,0));

// Add a unit sphere with 16 inclination & azimuth segments
mb.addSphere(new Geometry.Sphere, 16, 16);

// Add sphere with radius 0.7 at pos (0,1.2,0)
mb.addSphere(new Geometry.Sphere(new Geometry.Vec3(0,1.3,0), 0.7), 16, 16);

// Another sphere
mb.addSphere(new Geometry.Sphere(new Geometry.Vec3(0,2.25,0), 0.5), 16, 16);

// translate again
mb.setTransformation(m.translate(0,2.25,0.4).rotate(-90,0,1,0));

// set the color for the next operations
mb.color(new Util.Color4f(1,0.5,0));

// add a cone with radius 0.1, height 0.4 and 16 segments
mb.addCone(0.1, 0.4, 16);

// set the color for the next operations
mb.color(new Util.Color4f(0,0,0));

// translate again
mb.setTransformation(m.rotate(180,0,1,0).translate(-0.05,0.2,0.15));

// add a ring with inner radius 0.02, outer radius 0.05 and 16 segments
mb.addRingSector(0.02, 0.05, 16);

// translate again
mb.setTransformation(m.translate(0,0,-0.3));

// another ring
mb.addRingSector(0.02, 0.05, 16);

// Build the mesh
var mesh = mb.buildMesh();

// Create a geometry node for the mesh & add it to the scene
scene += new MinSG.GeometryNode(mesh);

// ----------------------------------------------------------------
// Set the camera position & orientation

// get the camera dolly
// (the actual camera is below this node but should always be moved using the dolly)
var camera = PADrend.getDolly();

// set the position of the camera
camera.setWorldOrigin(new Geometry.Vec3(-2,2,6));

// look at bounding box center (+2 in y-direction) (camera looks towards negative direction)
camera.rotateToWorldDir(camera.getWorldOrigin() - (gridNode.getWorldBB().getCenter() + new Geometry.Vec3(0,2,0)));


// ----------------------------------------------------------------
// Add a ShadowState to the scene & sets up the necessary shader

// Create a shader state
var shaderState = new MinSG.ShaderState;
// Set the shader configuration file name
shaderState.setStateAttribute(MinSG.ShaderState.STATE_ATTR_SHADER_NAME, "ExampleProject/data/shader/ShadowShader.shader");
// create the shader from the configuration file
shaderState.recreateShader( PADrend.getSceneManager() );
// add shader state to scene
scene += shaderState;

// Create a shadow state
var shadowState = new MinSG.ShadowState(4096);
// set the light source to the global sun
shadowState.setLight(PADrend.getDefaultLight());
// add shadow state to scene
scene += shadowState;

// Get the dynamic sky plugin
var DynamicSky = Util.queryPlugin('Effects_DynamicSky');
// Enable the sky
DynamicSky.setEnabled(true);
// Change the current time 
DynamicSky.setTimeOfDay(15);

// Get the infinite ground plugin
var InfiniteGround = Util.queryPlugin('Effects_InfiniteGround');
// Enable the infinite ground
InfiniteGround.enable();
// Set the type to solid ground
InfiniteGround.setType(4);
// Set ground color
InfiniteGround.groundColorWrapper(new Util.Color4f(0.9,0.9,0.95));