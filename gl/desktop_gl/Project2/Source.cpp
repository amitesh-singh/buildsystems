//In this example, we are drawing a point on surface with point size 10.0f.

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
 
//Include glew header before glfw3.h
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct UserData
{
	GLuint programId;
	GLuint vao;
	GLuint vbo, ebo;
};

void InitGL(UserData *d)
{
	//create our shader 
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//Vertex Shader
	string  vertexShader = "#version 400 core\n"
						   "layout(location = 0) in vec3 position_model; \n"
						   "void main() {\n"
						   "gl_Position = vec4(position_model.x, -position_model.y, position_model.z, 1.0); }\n";

	char const * cVertexShader = vertexShader.c_str();
	glShaderSource(vertexShaderId, 1, &cVertexShader, NULL);
	glCompileShader(vertexShaderId);
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Check Vertex Shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(vertexShaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "\nvertex: %s\n", &FragmentShaderErrorMessage[0]);

	//Fragment shader
	string fragmentShader = "#version 400 core\n"
		"out vec3 color;\n"
		" void main() { \n"
		"color = vec3(1, 0, 0); }";

	char const * cFragmentShader = fragmentShader.c_str();
	glShaderSource(fragmentShaderId, 1, &cFragmentShader, NULL);
	glCompileShader(fragmentShaderId);
	
	
	// Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    //std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(fragmentShaderId, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "\nfragment: %s\n", &FragmentShaderErrorMessage[0]);


	d->programId = glCreateProgram();
	glAttachShader(d->programId, vertexShaderId);
	glAttachShader(d->programId, fragmentShaderId);
	glLinkProgram(d->programId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	//create our VAO
	glGenVertexArrays(1, &d->vao);
	glBindVertexArray(d->vao);

	static const GLfloat vertices[] =
	{
		0.5f, 0.5f, 0.0f,
	};

	//create vbo
	glGenBuffers(1, &d->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, d->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

	//Set the point size
	//Note:  This functon is absent in Opengl ES 2.0
	//You need to define this in vertex Shader. gl_PointSize = 10.0; 
	glPointSize(10.0f); //Only present in Dekstop GL.
	//TODO: Check if glPointSize is present in Opengl ES 3.0.
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

	UserData userdata;
	//Call opengl init functions
	cout << "OpenGL version: " << glGetString(GL_VERSION); 
	cout << "\n Vendor: " << glGetString(GL_VENDOR);
	InitGL(&userdata);

	cout << "vao: " << userdata.vao;
 
	do{
		//GL Code starts
		//Clear the color buffer before drawing.
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(userdata.programId);
		
		glBindVertexArray(userdata.vao);

		//Draw our point
		glDrawArrays(GL_POINTS, 0, 1);

		//GL Code ends

		 // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
	

    return 0;
}

