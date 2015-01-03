// GLEW
//#define GLEW_STATIC
//#pragma comment( lib, "glfw3.lib" )

#include <GL/glew.h>
// GLFW
//The workaround:
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")

//End workaround
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//glutInit(&argc, argv);
	GLFWwindow* window; // (In the accompanying source code, this variable is global) 
	window = glfwCreateWindow( 1024, 768, "Window sample", NULL, NULL); 
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, \
			they are not 3.3 compatible. \
			Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	//Initialize Glew ~ which would load glFunctions :)
	
	glfwMakeContextCurrent(window); // Initialize GLEW 
	glewExperimental=true; // Needed in core profile 

	///NOTE: Always initialize glewinit after this, else glShaderCreate() will be null....
	GLenum err = glewInit();
	
	if (err != GLEW_OK)
	{
		std::cout << "gliew initialized ok\n";
		//return 0;
	}
	//GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	

	std::cout << "glew version using: " << glewGetString(GLEW_VERSION) << std::endl;

 
	do{
		// Draw nothing

		 // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
	

    return 0;
}

