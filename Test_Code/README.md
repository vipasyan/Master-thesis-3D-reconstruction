The test code is written to transform the models into MinSG format.
The code is non-functional.

Modifed code is indicated below with '''Modified''' 


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

'''Modified''' 
|   |-- mesh                                  # Added Mesh files and Point cloud models generated from NeRF
|   |   |-- Schwein.low.t.mmf


'''Modified''' 
|   |-- scene
|   |   `-- szene_1.minsg                     # A simple MinSG scene
|   |-- shader                                # Shader files for the renderers
|   |   |-- ShadowShader.shader               # Shader configuration file for shadow rendering
|   |   |-- SimpleShader.vs                   # Vertex shader for ExampleRenderer
|   |   `-- SimpleShader.fs                   # Fragment shader for ExampleRenderer
|   `-- texture                               # Textures used by the scene 'scene_1.minsg'
|       |-- Schwein.low.t.png

'''Modified'''   

|-- plugins                                   # Folder for PADrend to search for custom plugins
|   `-- ExampleProject                        # Main folder of the plugin 'ExampleProject'
|       |-- Plugin.escript                    # Plugin specification/entry point for the plugin 'ExampleProject'
|       `-- ScriptedExampleRenderer.escript   # Example renderer written in EScript
|-


- scripts                                   # Contains scripts to be used by the 'F3' quick dial menu
|   |-- _folder.info                          # Description file for all scripts in the folder
|   `-- MeshBuilderExample.escript            # Constructs a small scene using a MeshBuilder


'''Modified''' 
-- src
		|-- ELibExamples.cpp                      # Some simple EScript bindings 
		|-- EScriptHelper.h                       # Helper for registering ESCript initializer functions
		|-- ExampleRenderer                       # Example renderer written in C++
		|   |-- E_ExampleRenderer.cpp             # Sets up EScript bindings for the ExampleRenderer
		|   |-- E_ExampleRenderer.h               # Header file for E_ExampleRenderer
		|   |-- ExampleRenderer.cpp               # C++ source of the ExampleRenderer
		|   `-- ExampleRenderer.h                 # Header file for ExampleRenderer
		`-- Main.cpp                              # Main entry point of the library
```