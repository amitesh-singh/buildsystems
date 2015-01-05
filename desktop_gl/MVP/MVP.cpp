// In this example, we are drawing a rectangle using ebo and vbo

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "SOIL.lib")

#include <time.h>


//Note: glew header should be included before glfw header else you will get 
//lot of compilation errors.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//Glm headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	GLuint texId;
	GLint loc;
};

void InitGL(UserData *d)
{
	//create our shader 
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//Vertex Shader
	string  vertexShader = "#version 330 core\n"
						   "layout(location = 0) in vec3 position_model; \n"
						   "layout(location = 1) in vec2 vTexCoord; \n"
						    "uniform mat4 trans; \n"
							"uniform mat4 view; \n"
							"uniform mat4 proj; \n"
						   "out vec2 oTexCoord; \n"
						   "void main() {\n"
						   "gl_Position =  proj * view * trans * vec4(position_model, 1.0);\n"
						   " oTexCoord = vTexCoord; \n"
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
	string fragmentShader = "#version 330 core\n"
		"layout(location=0) out vec4 color;\n"
		"in vec2 oTexCoord;\n"
		"uniform sampler2D texSample;\n"
		" void main() { \n"
		"color = texture2D(texSample, oTexCoord); }";

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

	/*static const GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,  1.0f, 0.0f,
	};*/
	static const GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  -0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f,
	};
	static const GLubyte index[] = 
	{
		0, 1, 2, 2, 3, 0
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
	#define BUFFER_OFFSET(x) ((char *)NULL + (x))

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, len, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, len, BUFFER_OFFSET(3 * sizeof(GLfloat)));

	//Get the uniform location
	d->loc = glGetUniformLocation(d->programId, "texSample");

	//unbind vao
	glBindVertexArray(0);

	glGenTextures(1, &d->texId);
	glBindTexture(GL_TEXTURE_2D, d->texId);

	/*unsigned char pixels[] = 
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255,
		255, 255, 0,
	};*/
	unsigned char *pixels = nullptr;
	int w, h;

	pixels = SOIL_load_image("DSCN1310.jpg", &w, &h, 0, SOIL_LOAD_RGBA);
	printf("image loaded: pixels: %p, w: %d, h: %d\n", pixels, w, h);
	// set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	SOIL_free_image_data(pixels);

}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window; // (In the accompanying source code, this variable is global) 
	window = glfwCreateWindow( 700, 600, "Window sample", NULL, NULL); 
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

	//lets rotate image through Z axis using glm apis
	glm::mat4 trans;
	
	GLint uniTrans = glGetUniformLocation(userdata.programId, "trans");
	cout << "ma4 uniform location: " << uniTrans << endl;
	
	glm::mat4 view = glm::lookAt(
		glm::vec3(1.2f, 1.2f, 1.2f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
		);
	GLint uniView = glGetUniformLocation(userdata.programId, "view");
	
	glm::mat4 proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);

	//glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
	GLint uniProj = glGetUniformLocation(userdata.programId, "proj");
	
	do
	{
		//GL Code starts
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(userdata.programId);
		trans = glm::rotate(trans, glm::radians((GLfloat)clock() / (GLfloat)CLOCKS_PER_SEC * 180.0f),
			glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
    	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		
		glBindVertexArray(userdata.vao);

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

