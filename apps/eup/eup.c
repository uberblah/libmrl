#include <GLFW/glfw3.h>

int main(int argc, char** argv)
{
    GLFWwindow* window;

    if (!glfwInit())
	return -1;

    window = glfwCreateWindow(800, 600, "Data Mastery", NULL, NULL);
    if (!window)
    {
	glfwTerminate();
	return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    glfwSetWindowShouldClose(window, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glRotatef(glfwGetTime() * 90.0f, 0.0f, 1.0f, 0.0f);
	
	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	    
	glPopMatrix();
	
	glfwSwapBuffers(window);
	glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
