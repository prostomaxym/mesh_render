# Mesh rendering engine
This is a simple C++ 3D graphics rendering engine, which can load and display models from .obj files.  
OpenGL 4.6 and GLSL 460 used for graphics rendering and a few other libs for utility.  
Demo video: https://youtu.be/cpHM_UX39hY

## Tools used
* OpenGL 4.6 - rendering.
* GLSL 460 - rendering.
* GLUT - window management, keyboard/mouse input.
* Stb-image - load image files.
* Glatter - load modern OpenGL functions.<br/><br/>
Stb-image and Glatter header libs are included in repo.

## Features made
* Window creation, resizing, fullscreen/windowed mode.
* Keyboard, mouse input.
* Keyboard keybindings.
* FPP camera (WASD - movement, SPACE/C - up/down movement, Mouse - rotation, G - 2x zoom, F - toggle fullscreen).
* Loading and rendering models from .obj files.
* Loading and rendering textures from image files.
* VBO, VAO based mesh rendering.
* Phong, Blinn-Phong shader based lighting.
* Static or dynamic customizable lighting.
* 3 demo levels are included.
