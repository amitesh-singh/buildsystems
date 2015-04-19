// In this example, we are drawing a rectangle using ebo and vbo

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
 

//Note: glew header should be included before glfw header else you will get 
//lot of compilation errors.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    glfwInit();

    //The below lines are required to make your code compatible to available GL version.
   
   // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//glutInit(&argc, argv);
	GLFWwindow* window; // (In the accompanying source code, this variable is global) 
	window = glfwCreateWindow( 500, 500, "Window sample", NULL, NULL); 
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, \
			they are not 3.3 compatible. \
			Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW 
	glewExperimental = true; // Needed in core profile 

	//Initialize Glew ~ which would load glFunctions :)
	GLenum err = glewInit();
	
	if (err == GLEW_OK)
	{
		std::cout << "Glew initialized ok\n";
	}

	std::cout << "glew version using: " << glewGetString(GLEW_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Get OpenGL Version informations
    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte *openglversion = glGetString(GL_VERSION);
    const GLubyte *vendor = glGetString(GL_VENDOR);

    cout << "OpenGL version: " << openglversion << "\n";
    cout << "Renderer: " << renderer << "\n";
	cout << "Vendor: " << vendor << endl;

    //Lets print out the GL extensions
    const GLubyte *extensions = NULL;

    extensions = glGetString(GL_EXTENSIONS);

    cout << "Extensions: \n" << extensions;

     // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

   /* OTHER STUFF GOES HERE NEXT */

   // close GL context and any other GLFW resources
    glfwTerminate();


    return 0;
}

