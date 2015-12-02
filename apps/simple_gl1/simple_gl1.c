#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
	return -1;

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
	glfwTerminate();
	return -1;
    }

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	    glfwSetWindowShouldClose(window, 1);
	
	glfwSwapBuffers(window);
	glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
