//============================================================================
// Name        : Dibujo de Triangulo por puntos ingresados en Codigo
// Professor   : Herminio Paucar
// Version     :
// Description : Utilizamos los Vertex y Fragment Shaders
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <glm/glm.hpp>
using namespace glm; // @suppress("Symbol is not resolved")

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>

GLuint renderingProgram;

GLfloat* m_Vertices;
GLuint m_VBO;
GLuint m_VAO;

using namespace std;

// displays the contents of OpenGL's log when GLSL compilation failed
void printShaderLog(GLuint shader) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(shader, len, &chWrittn, log);
        cout << "Shader Info Log: " << log << endl;
        free(log);
    }
}

// displays the contents of OpenGL's log when GLSL linking failed
void printProgramLog(int prog) {
    int len = 0;
    int chWrittn = 0;
    char* log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(prog, len, &chWrittn, log);
        cout << "Program Info Log: " << log << endl;
        free(log);
    }
}

// checks the OpenGL error flag for the occurrrence of an OpenGL error
// detects both GLSL compilation errors and OpenGL runtime errors
bool checkOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cout << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }
    return foundError;
}

string readShaderSource(const char *filePath) {
    string content = "";
    ifstream fileStream(filePath, ios::in);
//    cerr << "Error: " << strerror(errno) << endl;  // No such file or directory
//    cout << fileStream.is_open() << endl;  // 0
    string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

GLuint createShaderProgram() {
    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    string vertShaderStr = readShaderSource("src/vertShader.glsl");
    string fragShaderStr = readShaderSource("src/fragShader.glsl");

    const char* vertShaderSrc = vertShaderStr.c_str();
    const char* fragShaderSrc = fragShaderStr.c_str();

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vertShaderSrc, NULL);
    glShaderSource(fShader, 1, &fragShaderSrc, NULL);

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if (vertCompiled != 1) {
        cout << "vertex compilation failed" << endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if (fragCompiled != 1) {
        cout << "fragment compilation failed" << endl;
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
    if (linked != 1) {
        cout << "linking failed" << endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}


void init (GLFWwindow* window) {
    renderingProgram = createShaderProgram();
    // The first 3 points are to Vertex position of Triangle
    // The other 3 points are to Vertex color


    	GLfloat k=0.2;
    	int numberOfVertices = 15;
    	int DimVertices;

    	GLfloat x0= -0.8;
    	GLfloat y0= 0.8;
    	GLfloat z0= 0;

    	GLfloat x1= 0.5;
    	GLfloat y1= 0.8;
     	GLfloat z1= 0;

      	GLfloat x2= -0.5;
      	GLfloat y2= -0.2;
    	GLfloat z2= 0;

    	GLfloat x3= 0.2;
    	GLfloat y3= -0.2;
    	GLfloat z3= 0;

    	GLfloat verticesX[numberOfVertices];
    	GLfloat verticesY[numberOfVertices];
    	GLfloat verticesZ[numberOfVertices];
		for (int i = 0;  i< numberOfVertices; i++) {

			verticesX[i]= x0 + k*glm::vec3(x0*y0, 0.0, 0.0);
			verticesX[i]= y0 + k*glm::vec3(0.0, x0*y0, 0.0);
			verticesX[i]= z0;

			verticesX[i]= x1 + k*glm::vec3(x1*y1, 0.0, 0.0);
			verticesX[i]= y1 + k*glm::vec3(0.0, x1*y1, 0.0);
			verticesX[i]= z1;

			verticesX[i]= x2 + k*glm::vec3(x2*y2, 0.0, 0.0);
			verticesX[i]= y2 + k*glm::vec3(0.0, x2*y2, 0.0);
			verticesX[i]= z2;

			verticesX[i]= x3 + k*glm::vec3(x3*y3, 0.0, 0.0);
			verticesX[i]= y3+ k*glm::vec3(0.0, x3*y3, 0.0);
			verticesX[i]= z3;
		}
		DimVertices = numberOfVertices*4;
		GLfloat m_Vertices[DimVertices];

		for (int i = 0;  i< DimVertices; i++) {
			m_Vertices[i * 3] = verticesX[i];
			m_Vertices[i * 3 + 1] = verticesY[i];
			m_Vertices[i * 3 + 2] = verticesZ[i];
		}


	// Cria um ID na GPU para nosso buffer
	glGenBuffers(1, &m_VBO);

	// Cria um ID na GPU para um array de  buffers
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// Reserva memoria na GPU para um TARGET receber dados
	// Copia esses dados pra essa �rea de memoria
	glBufferData(
			GL_ARRAY_BUFFER,	// TARGET associado ao nosso buffer
			90 * sizeof(GLfloat),	// tamanho do buffer
			m_Vertices,			// Dados a serem copiados pra GPU
			GL_STATIC_DRAW		// Pol�tica de acesso aos dados, para otimiza��o
		);

	// Nesse ponto, ja copiamos nossos dados pra GPU.
	// Mas, OpenGL nao faz ideia do que eles representam
	// Sao 6 v�rtices ? 3 v�rices e 3 cores ?
	// Os vertices vem antes ou depois das cores ?
	// Ou est�o intercalados v�rtices depois cores, depois vertices, depois cores novamente....
	// Precisamos dizer com nossos dados precisam ser interpretados:
	glVertexAttribPointer(
			0,			// Lembra do (layout = 0 ) no vertex shader ? Esse valor indica qual atributo estamos indicando
			3,			// cada vertice � composto de 3 valores
			GL_FLOAT,	// cada valor do v�rtice � do tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, j� esta tudo correto, ent�o deixamos como FALSE)
			6 * sizeof(GLfloat),// De quantos em quantos bytes, este atributo � encontrado no buffer ? No nosso caso 3 floats pros vertices + 3 floats pra cor = 6 floats
			(GLvoid*) 0	// Onde est� o primeiro valor deste atributo no buffer. Nesse caso, est� no in�cio do buffer
		);

	glEnableVertexAttribArray(0);	// Habilita este atributo

	// Faremos a mesma coisa pra cor de cada v�rtice
	glVertexAttribPointer(
			1,			// Lembra do (layout = 1 ) no vertex shader ? Esse valor indica qual atributo estamos indicando
			3,			// cada vertice � composto de 3 valores
			GL_FLOAT,	// cada valor do v�rtice � do tipo GLfloat
			GL_FALSE,	// Quer normalizar os dados e converter tudo pra NDC ? ( no nosso caso, j� esta tudo correto, ent�o deixamos como FALSE)
			6 * sizeof(GLfloat),// De quantos em quantos bytes, este atributo � encontrado no buffer ? No nosso caso 3 floats pros vertices + 3 floats pra cor = 6 floats
			(GLvoid*) (3 * sizeof(GLfloat))	// Onde est� o primeiro valor deste atributo no buffer. Nesse caso, 3 floats ap�s o in�cio do buffer
		);

	glEnableVertexAttribArray(1);		// Habilita este atributo


	glBindVertexArray(0);
}

void display(GLFWwindow* window, double currentTime) {

		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

		glClear( GL_COLOR_BUFFER_BIT);


    glUseProgram(renderingProgram);

	// Use este VAO e suas configura��es
	glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 15);
	glBindVertexArray(0);

}

int main(void) {
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            //
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(800, 500, "PAJUELO CIEZA, Junior Alexis", NULL, NULL);
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
