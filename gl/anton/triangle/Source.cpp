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

     // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

   /* OTHER STUFF GOES HERE NEXT */

    //Write shaders
    GLuint vs, fs; //Vertex and Fragment shader

    //Note: last component 2.0f is basically perspective .. camera...
    const char *vs_shd_src = 
        "#version 400\n"
        "layout(location = 0) in vec3 pos;\n"
        "void main() {\n"
        "gl_Position = vec4(pos, 2.0f);\n"
        "}\n";

    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_shd_src, NULL);
    glCompileShader(vs);
    
     const char *fs_shd_src = 
        "#version 400\n"
        "out vec4 color;\n"
        "void main() {\n"
        "color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
        "}\n";
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_shd_src, NULL);
    glCompileShader(fs);

    GLuint programId;

    programId = glCreateProgram();
    glAttachShader(programId, vs);
    glAttachShader(programId, fs);
    glLinkProgram(programId);

    glDeleteShader(vs);
    glDeleteShader(fs);

    //Create VBO for our points
    GLfloat points[] = 
    {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    //VBO
    GLuint vbo = 0;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint vao = 0;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    while (!glfwWindowShouldClose(window))
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram (programId);
        glBindVertexArray (vao);
        //draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawArrays (GL_TRIANGLES, 0, 3);
        // update other events like input handling
        glfwPollEvents ();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }

   // close GL context and any other GLFW resources
    glfwTerminate();

    return 0;
}

