var fileLocator = new Util.FileLocator();
// add search path
var fileName = new Util.FileName();
fileName = "C:/PADrend/build/data/mesh/chair_surfmesh_grd_alpha.ply";
var gnode1 = MinSG.loadModel(fileName, 0, null);


fileName = "C:/PADrend/build/data/mesh/chair_surfels_cn.ply";
var gnode2 = MinSG.loadModel(fileName, 0, null);

var rootNode = new MinSG.ListNode();
rootNode.addChild(gnode1);
rootNode.addChild(gnode2);

//var surfelState = new MinSG.SurfelRenderer();
var gnode1.addState(surfelState);

//Register the root node of the scene graph
PADrend.registerScene(rootNode);
//Selecting the root node to be the active scene
PADrend.selectScene(rootNode);