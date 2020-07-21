//============================================================================
// Name        : Rotate Triangle Object
// Professor   : Herminio Paucar
// Version     :
// Description :
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include "Utils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

const float toRadians = 3.14159265f / 180.0f;
#include <glm/glm.hpp>
using namespace glm;

GLuint renderingProgram;

GLfloat* m_Vertices;
GLuint n_Vertices;
GLuint m_VBO;
GLuint m_VAO;
GLuint mVAO1;
int dimensionVertices;
int numeroDeVertices;
float curAngle = 0.0f;

struct vertice{
	vec3 posicion;
	vec3 color;
};

void init (GLFWwindow* window) {

	// Utils
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

	// Cria um ID na GPU para um array de  buffers
	/*glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);*/


    // The first 3 points are to Vertex position of Triangle
	/*m_Vertices = new GLfloat[9] {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	n_Vertices = 9;*/
	// Cria um ID na GPU para nosso buffer
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat z = 0.0;
	GLfloat radius = 0.2;
	GLint numberOfSides =4000; // 50

	numeroDeVertices = numberOfSides+1;

	vertice total[numeroDeVertices];
	GLfloat twicePi = 22.0f * M_PI;

	GLfloat verticesX[numeroDeVertices];
	GLfloat verticesY[numeroDeVertices];
	GLfloat verticesZ[numeroDeVertices];

	verticesX[0] = x;
	verticesY[0] = y;
	verticesZ[0] = z;

	for (int i = 1; i < numeroDeVertices; i++) {
		if(i>(10*numeroDeVertices)/11){
			verticesX[i] = -1.03 + x + ((radius+0.29) * cos(-1.0 + ((i * twicePi / numberOfSides)/5)));
			verticesY[i] = -0.80 + y + ((radius+0.29) * sin(-1.0 + ((i * twicePi / numberOfSides)/5)));
			verticesZ[i] = z;
			total[i].color = vec3(0.0, 0.0, 0.0);
		}else if(i>(9*numeroDeVertices)/11){
			verticesX[i] = 0.2 + x + ((radius+0.29) * cos(2.7 + ((i * twicePi / numberOfSides)/5)));
			verticesY[i] = 1.0 + y + ((radius+0.29) * sin(2.7 + ((i * twicePi / numberOfSides)/5)));
			verticesZ[i] = z;
			total[i].color = vec3(0.0, 0.0, 0.0);
		}else if(i>(8*numeroDeVertices)/11){
			verticesX[i] = 0.622 + x + ((radius+0.29) * cos(1.93 + ((i * twicePi / numberOfSides)/5)));//coma cuarto
			verticesY[i] = -0.93 + y + ((radius+0.29) * sin(1.93 + ((i * twicePi / numberOfSides)/5)));
			verticesZ[i] = z;
			total[i].color = vec3(0.0, 0.0, 0.0);
		}else if(i>(7*numeroDeVertices)/11){
			verticesX[i] = x + ((radius*5.5) * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + ((radius*5.5) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.68, 0.17, 0.17);
		}else if(i>(6*numeroDeVertices)/11){
			verticesX[i] = x + ((radius*6.0) * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + ((radius*6.0) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.61, 0.12, 0.12);
		}else if(i>(5*numeroDeVertices)/11){
			verticesX[i] = x + ((radius*9) * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + ((radius*9) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.68, 0.17, 0.17);
		}else if(i>(4*numeroDeVertices)/11){
			verticesX[i] = x + ((radius*9.45) * cos(i * twicePi / numberOfSides));
			verticesY[i] = y + ((radius*9.45) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.0,0.0,0.0);
		}else if(i>(3*numeroDeVertices)/11){
			verticesX[i] = 0.0 + x + ((radius+0.07) * cos(i * twicePi / numberOfSides));
			verticesY[i] = 1.1 + y + ((radius+0.07) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.0,0.0,0.0);
		}else if(i>(2*numeroDeVertices)/11){
			verticesX[i] = -0.8 + x + ((radius+0.07) * cos(i * twicePi / numberOfSides));//punto 3 cuadrante
			verticesY[i] = -0.8 + y + ((radius+0.07) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.0,0.0,0.0);
		}else if(i>(numeroDeVertices)/11){
			verticesX[i] = 0.8 + x + ((radius+0.07) * cos(i * twicePi / numberOfSides));//punto cuadrante
			verticesY[i] = -0.8 + y + ((radius+0.07) * sin(i * twicePi / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.0,0.0,0.0);
		}else{
			verticesX[i] = x + ((radius) * cos(i * twicePi*1.2 / numberOfSides));//punto central
			verticesY[i] = y + ((radius) * sin(i * twicePi*1.2 / numberOfSides));
			verticesZ[i] = z;
			total[i].color = vec3(0.0,0.0,0.0);
		}
	}
	dimensionVertices = (numeroDeVertices) * 3;
	for (int i = 0; i < numeroDeVertices; i++) {
		total[i].posicion = vec3(verticesX[i],verticesY[i],verticesZ[i]);
	}

	glGenBuffers(1, &m_VBO);

	// Cria um ID na GPU para um array de  buffers
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Reserva memoria na GPU para um TARGET receber dados
	// Copia esses dados pra essa 疵ea de memoria
	glBufferData(
			GL_ARRAY_BUFFER,	// TARGET associado ao nosso buffer
			sizeof(total),	// tamanho do buffer
			total,			// Dados a serem copiados pra GPU
			GL_STATIC_DRAW		// Pol咜ica de acesso aos dados, para otimiza鈬o
		);

	glVertexAttribPointer(
			0,			// Lembra do (layout = 0 ) no vertex shader ? Esse valor indica qual atributo estamos indicando
			3,			// cada vertice � composto de 3 valores
			GL_FLOAT,	// cada valor do v駻tice � do tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, j� esta tudo correto, ent縊 deixamos como FALSE)
			sizeof(vertice),// De quantos em quantos bytes, este atributo � encontrado no buffer ? No nosso caso 3 floats pros vertices + 3 floats pra cor = 6 floats
			(GLvoid*)offsetof(vertice,posicion)	// Onde est� o primeiro valor deste atributo no buffer. Nesse caso, est� no in兤io do buffer
		);

	glEnableVertexAttribArray(0);	// Habilita este atributo

	glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(vertice),
			(GLvoid*)offsetof(vertice,color)
			);

	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	GLuint uniformModel = glGetUniformLocation(renderingProgram, "model");

	curAngle += 2.0f;
	if (curAngle >= 360){
		curAngle -= 360;
	}

	// Matriz con elementos de valor 1
	glm::mat4 model(1.0f);
	//Giro Antihorario
	model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	//Usando UniformMatrix
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//Usando ProgramUniform
	//glProgramUniformMatrix4fv(renderingProgram, uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	// Use este VAO e suas configura鋏es
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_FAN, (4*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (5*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (6*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (7*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (8*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (9*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (10*numeroDeVertices/11)+1, numeroDeVertices/11);

	glDrawArrays(GL_TRIANGLE_FAN, 0, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, numeroDeVertices/11+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (2*numeroDeVertices/11)+1, numeroDeVertices/11);
	glDrawArrays(GL_TRIANGLE_FAN, (3*numeroDeVertices/11)+1, numeroDeVertices/11);

	glBindVertexArray(0);
}

int main(void) {
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            //
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(800, 800, "Pajuelo Cieza Junior Alexis", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
    	exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
