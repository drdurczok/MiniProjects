# Rhythm_Minigame
A rhythm based minigame written in C++ and OpenGL.

OpenGL = Open Graphics Library
GLU = Graphic Library Utility
GLUT = Graphic Library Utility Toolkit


## Installation

# GLEW

GLEW is a cross-platform open-source C/C++ extension loading library. It contains no implementations, only links to the proper funtions in the respective binary files for each platform.

Build from scratch, follow glew ReadMe.

```git clone https://github.com/nigels-com/glew.git glew```

Install for Ubuntu.

```sudo apt-get install libglew-dev```


# FreeGlut

```sudo apt-get freeglut3```

It will install the following header files (*.h) inside /usr/include/GL:

*glext.h*
*gl.h*
*gl_mangle.h*
*glu.h*
*glu_mangle.h*
*glxext.h*
*glx.h*
*glx_mangle.h*
*internal*

```sudo apt-get freeglut3-dev```

It will install specific header files to develop software with OpenGL in the same directory as before (/usr/include/GL):

*freeglut_ext.h*
*freeglut.h*
*freeglut_std.h*
*glut.h*
