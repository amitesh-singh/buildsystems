#include <iostream>

//Glm headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

int main(int argc, char **argv)
{
	cout << "glm sample:" << endl;

    //Transformations matrices.
    
    //1. translation matrices

    // 1 0 0 10.0  -> X
    // 0 1 0 0     -> Y
    // 0 0 1 0     -> Z
    // 0 0 0 1
    glm::mat4 tr_m = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));
    glm::vec4 myvec1(10.0f, 10.0f, 0.0f, 0.0f);

    glm::mat4 transformedVector = tr_m * myvec1;



	glm::mat4 trans(1.0f); // identity matrix by default.
	//rotate matrix with angle 180 degree around Z axis.
	trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	//This part is get done in vertex shader
	// you will write something like that
	// uniform mat4 trans;
	// gl_Position = trans * vec4(model_position, 1.0);
// and while rendering call...     	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

	//lets roate a vector with this transformation.
	glm::vec4 result = trans * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	cout << result.x << "," << result.y << "," << result.z << endl;
	int i;
	cin >> i;

	return 0;
}