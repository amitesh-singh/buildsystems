// In this example, we are drawing a rectangle using ebo and vbo

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SOIL.lib")
 

//Note: glew header should be included before glfw header else you will get 
//lot of compilation errors.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <SOIL.h>

using namespace std;

struct UserData
{
	GLuint programId;
	GLuint vao;
	GLuint vbo, ebo;
	GLuint tex;
};

void InitGL(UserData *d)
{
	//create our shader 
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//Vertex Shader
	string  vertexShader = "#version 400 core\n"
						   "layout(location = 0) in vec3 position_model; \n"
						   "layout(location = 1) in vec2 texCoord; \n"
						   "smooth out vec2 TexCoord; \n"
						   "void main() {\n"
						   "gl_Position = vec4(position_model, 1.0);\n"
						   " TexCoord = texCoord; \n"
						   "}\n";

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
		"out vec4 color;\n"
		"smooth in vec2 TexCoord; \n"
		"uniform sampler2D s; \n"
		" void main() { \n"
		"color = texture(s, TexCoord); }";

	char const * cFragmentShader = fragmentShader.c_str();
	glShaderSource(fragmentShaderId, 1, &cFragmentShader, NULL);
	glCompileShader(fragmentShaderId);
	
	// Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
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
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  -0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
	};
	static const GLubyte index[] = 
	{
		0, 1, 2, 0, 3, 2
	};
	//create ebo
	glGenBuffers(1, &d->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, d->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	//create vbo
	glGenBuffers(1, &d->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, d->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	int len = 5 * sizeof(GLfloat);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, len, (void *) 0);

	#define BUFFER_OFFSET(x) ((char *)NULL + (x))

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, len, BUFFER_OFFSET(3 * sizeof(GLfloat)));

	//Texture
	glGenTextures(1, &d->tex);
	glBindTexture(GL_TEXTURE_2D, d->tex);
	/*GLubyte pixels[] = 
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255,
		255, 255, 0,
	};*/
	int w = 2, h = 2;
	unsigned char *pixels = SOIL_load_image("DSCN1310.jpg", &w, &h, 0, SOIL_LOAD_RGB);
	fprintf(stderr, "pixel: %p,, w:%d, h: %d\n", pixels, w, h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	SOIL_free_image_data(pixels);

	int loc = glGetUniformLocation(d->programId, "s");
	glUniform1i(loc, 0);
	cout << "location of sampler: " << loc << endl;
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

	//Initialize Glew ~ which would load glFunctions pointers. :)
	//Note: You must declare glew here only else most of gl functions won't get initialized.
	// glCreateShader function pointer would be 0.
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

		glClear(GL_COLOR_BUFFER_BIT);
		//glViewport ( 0, 0, 100,100);


		glUseProgram(userdata.programId);
		
		glBindVertexArray(userdata.vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, userdata.tex);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 
			//We already passed indices to EBO, so no need to pass indices here. ;)
			(void *) 0);

		//GL Code ends

		 // Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
 
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
	

    return 0;
}

