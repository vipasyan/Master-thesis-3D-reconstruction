Example project for PADrend
===========================

This is an example project for extending PADrend (Platform for Algorithm Development and rendering).
It contains an EScript part and an optional C++ part.
You find the EScript part in the 'plugins/ExampleProject' folder and the C++ part in the 'src' folder.
If you want to use the C++ part you have to build it yourself as described below.

Getting Started
----------------
To include the example project into PADrend, copy the entire 'ExampleProject' folder into your local PADrend folder (e.g., '~/PADrend/ExampleProject/' or 'C:\PADrend\ExampleProject\').

Now, you need to add the ExampleProject to your plugin search path, so that PADrend can find it.
For this, open the file 'config.json' in a text editor (you need to run PADrend once to create it) and search for the following section:
```json
"Paths":{
	"data":"data/",
	"plugins":[
		"extPlugins/",
		"plugins/"
	],
	"scene":"data/scene/",
	"user":"./"
},
```

Here you need to add the 'plugins' folder of your ExampleProject to 'Paths.plugins' (don't forget the trailing '/'):
```json
"Paths":{
	"data":"data/",
	"plugins":[
		"extPlugins/",
		"plugins/",
		"ExampleProject/plugins/"
	],
	"scene":"data/scene/",
	"user":"./"
},
```

Now, you need to activate your plugin in PADrend.
For this, you need to start PADrend.
After you started PADrend, Open the 'Config' menu ![gear](./data/icons/gear.png) and click on 'Plugins'. 
There you should see a list of all plugins with a small 'x' if they are active.
Search for the entry named 'ExampleProject' and click on it to activate it.
To use your plugin you need to restart PADrend.
After you restarted PADrend, you should now find a new menu entry 'ExampleProject' under the 'Plugins' menu ![puzzle](./data/icons/puzzle.png).
When you click on it, a window should open in PADrend with a set of buttons which do various things when you click on them.

Folder Structure
----------------
The folder structure of this example project is as follows:
```
ExampleProject
.
|-- CMakeLists.txt                            # Configuration file for CMake to build C++ library
|-- README.md                                 # This README file
|-- cmake                                     # Contains custom CMake modules
|   `-- FindEScript.cmake                     # CMake module for finding the EScript library
|   `-- FindPADrend.cmake                     # CMake module for finding the PADrend main libraries
|-- data                                      # Contains various resource files for the project
|   |-- icons                                 # Icons used in this README
|   |   |-- gear.png
|   |   `-- puzzle.png
|   |-- mesh                                  # 3D meshes used by the scene 'scene_1.minsg'
|   |   |-- Schwein.low.t.mmf
|   |   |-- tCube.mmf
|   |   |-- tWall_2.mmf
|   |   |-- tree_lite1.mmf
|   |   |-- tree_lite2.mmf
|   |   `-- tree_red.mmf
|   |-- scene
|   |   `-- szene_1.minsg                     # A simple MinSG scene
|   |-- shader                                # Shader files for the renderers
|   |   |-- ShadowShader.shader               # Shader configuration file for shadow rendering
|   |   |-- SimpleShader.vs                   # Vertex shader for ExampleRenderer
|   |   `-- SimpleShader.fs                   # Fragment shader for ExampleRenderer
|   `-- texture                               # Textures used by the scene 'scene_1.minsg'
|       |-- Schwein.low.t.png
|       `-- stone3.bmp
|-- plugins                                   # Folder for PADrend to search for custom plugins
|   `-- ExampleProject                        # Main folder of the plugin 'ExampleProject'
|       |-- Plugin.escript                    # Plugin specification/entry point for the plugin 'ExampleProject'
|       `-- ScriptedExampleRenderer.escript   # Example renderer written in EScript
|-- scripts                                   # Contains scripts to be used by the 'F3' quick dial menu
|   |-- _folder.info                          # Description file for all scripts in the folder
|   `-- MeshBuilderExample.escript            # Constructs a small scene using a MeshBuilder
`-- src
		|-- ELibExamples.cpp                      # Some simple EScript bindings 
		|-- EScriptHelper.h                       # Helper for registering ESCript initializer functions
		|-- ExampleRenderer                       # Example renderer written in C++
		|   |-- E_ExampleRenderer.cpp             # Sets up EScript bindings for the ExampleRenderer
		|   |-- E_ExampleRenderer.h               # Header file for E_ExampleRenderer
		|   |-- ExampleRenderer.cpp               # C++ source of the ExampleRenderer
		|   `-- ExampleRenderer.h                 # Header file for ExampleRenderer
		`-- Main.cpp                              # Main entry point of the library
```

Building the C++ Library
------------------------
To build the C++ library you need a development environment with a C++ compiler and CMake.
See https://padrend.github.io/Tutorials/installation_guide how to set them up for your system.

Now, to build the library do the following:
1. Open a terminal (or PowerShell in windows) and navigate to the ExampleProject folder.
2. create a new folder called 'build' and navigate into it `mkdir build; cd build`
3. run CMake with the following flags: 
	* Windows: `cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo`
	* Linux: `cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo`
4. build the library: `cmake --build .`
	 If everything worked fine, you should now have the file `libExampleProject.so` or `libExampleProject.dll` in your folder.