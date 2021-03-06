# SimplexEngine
Game engine with a custom made software renderer (OpenGL-like rendering pipeline)

![Statue rendered with SimplexEngine](Screenshots/Lights.PNG)

## What is this project about ?
This project is a personnal project. My goals for this project are:
- Improving my mathematics skills
- Understanding in depth the rendering pipeline of OpenGL
- Improving my skills in project architecture
- Getting better at producing high-quality code (Well commented and easy to read as much as possible)
- Having fun doing what I like

## Software used
- Visual Studio 2017 to code

## Libraries used
- SDL2 (Window context, events and inputs)
- SDL2_ttf (For the UI, no CPU rasterization for this part)
- GyvrIni (My personal ini library)
- Assimp (3D model loader)
- GLM (Math library)
- Bullet (Physics library)

## Target platforms and configurations
The code source of this project is cross-platform, thanks to the SDL. But the actual project is made and configured with Visual Studio 2017 and target Windows.
32 bits and 64 bits are supported, debug and release

## How to build ?
The build isn't included in this repository. To build this project, the best and easiest way is to use Visual Studio 2017. All you have to do is to build in any configuration you want (Debug/Release) for any platform (x86/x64).
There are 2 projects in this repository, the actual game engine and an example project (Demo scene). You should build the engine first.

## Screenshots
### Bullet integration example
![Screenshot 1](Screenshots/Bullet_Physics_Lambert.gif)
![Screenshot 2](Screenshots/Bullet_Physics_Wireframe.gif)

### Puzzle jump map with Character Controller
![Screenshot 3](Screenshots/Puzzle_Jump.png)

### Material color and alpha blending
![Screenshot 4](Screenshots/Alpha_And_Colors.png)

### Random color entity spawning
![Screenshot 5](Screenshots/Entity_Spawning.png)

### Simple scene with parent/child relations
![Screenshot 6](Screenshots/Demo_Scene.PNG)

### Unreal Engine 4 mannequin with lambert shader
![Screenshot 7](Screenshots/Mannequin.PNG)

### Dynamic rasterization buffer size for pixelized style
![Screenshot 8](Screenshots/pixelized.png)
