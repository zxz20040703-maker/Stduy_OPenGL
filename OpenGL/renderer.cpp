#include"renderer.h"

void __stdcall debugCallback(GLenum source, GLenum type, GLuint id,GLenum severity, GLsizei length,const GLchar* message, const void* userParam)
{
	if (type == GL_DEBUG_TYPE_ERROR || type == GL_DEBUG_TYPE_PERFORMANCE) {
		std::cerr << "OpenGL Debug Message:" << std::endl;
		std::cerr << "ID: " << id << std::endl;
		std::cerr << "Message: " << message << std::endl;

	}

	__debugbreak();
}

static void DebugerEnable() 
{

	if (glDebugMessageCallback) {
		glEnable(GL_DEBUG_OUTPUT);

		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(debugCallback, nullptr);
		std::cout << "OpenGL debug callback registered." << std::endl;
	}
	else {
		std::cout << "glDebugMessageCallback not supported!" << std::endl;
	}


	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
}

void  GLInit(GLFWwindow* & window)
{
	if (!glfwInit())
		return;
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); // 请求调试上下文
	window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(window);//一切函数调用都在创建上下文之后进行

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return ;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	DebugerEnable();
	
}

