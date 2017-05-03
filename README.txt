Welcome to Hurricane!

Date Created: Jan 20, 2016
Last Updated: May 03, 2017

Primary Author:
-----------------
Edwin Chen


*Special Thanks: 
-----------------
Scott Fielder
Mathieu Violette
James Sholdice
Nathan Senter
Nick Whalen
Raymond Micheau
Mark Seaman
Daniel Argento
Rob Spongale
Adam Hermosa
Aiden Dearing
Domenic Caronzo
Kris Alexander
House Yokeswaran
Nicco Jacinto
Unity


Introduction:
-----------------
This is my first ever game engine. It is mainly focused on building 3rd person platformer-like games.
Hurricane is programmed purely in C++ to allow for fast memory management and efficiency.
Most of the features implemented in this engine are modelled after the Unity game engine. 
Component-based objects allow for quick and efficient processing and highly avoids being too 
object-oriented focused.


Dependencies:
-----------------
Hurricane makes use of many different 3rd party APIs to allow for ease of use, production time reduction, etc.
I do not own any of the APIs listed below and all rights and credits belong to their repsective owners.


Dependency				Purpose in Engine
----------------------------------------------------------------------------------------------------------------
TinyXML					- XML parsing, loading in properties and information for games

OpenGL (GLEW)			- 3D Graphics

Assimp					- Model loading (.fbx, .obj, etc.)
						- Vertices, UV coordinates, normals importation

Win32					- Windowing system
						- Some event handling

DirectX11				- 3D Graphics
						- Audio
						- Shaders

IMGUI					- Simple UI system


Notes:
-----------------
*Thank you to everybody mentioned in the Special Thanks list above! Without you guys, Hurricane would not be possible!