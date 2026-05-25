#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>


struct ShaderProgramResource
{
	std::string VertexShader;
	std::string FragmentShader;
};

static ShaderProgramResource ParseShader(std::string filePath)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(filePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	
	std::cout << "文件打开成功" << std::endl;
	if (stream) {

		while (getline(stream, line)) {

			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}

			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}
	}
	else {
		std::cout << "Error :CheakPath" << filePath << std::endl;

	}
	return { ss[0].str(), ss[1].str() };
}
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragemnt") << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;

}
static int CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs =  CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program );
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;

}




int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    } 

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
		std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;


    float position[] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
	};//在内存空间定义了一组数据，后续会发送到GPU中进行处理

    unsigned int a;
	glGenBuffers(1, &a);
	glBindBuffer(GL_ARRAY_BUFFER, a);//指定a缓冲区的类型为GL_ARRAY_BUFFER，并将其绑定到当前上下文中
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);//将数据复制到当前绑定的缓冲区对象中，数据大小为6个float，数据来源于position数组，使用GL_STATIC_DRAW作为使用模式

	glEnableVertexAttribArray(0);//启用顶点属性数组，参数0表示启用索引值为0的顶点属性数组

	//给第0个顶点属性定义读取方式
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	ShaderProgramResource source = ParseShader("res/shaders/BasicalShader.shader");

	unsigned int shader = CreatShader(source.VertexShader ,source.FragmentShader);
	std::cout << source.FragmentShader;
	glUseProgram(shader);
    while (!glfwWindowShouldClose(window))
    {
		//在这里可以进行渲染操作
        glClear(GL_COLOR_BUFFER_BIT);

         
		glDrawArrays(GL_TRIANGLES, 0, 3);//绘制调用。GL_TRIANGLES表示绘制模式，0表示从数组的第一个顶点开始，3表示绘制3个顶点

		//交换前后缓冲区，以显示渲染结果
        glfwSwapBuffers(window);

		  glfwPollEvents();
    }

	glDeleteProgram(shader);
	glfwTerminate();//终止GLFW库，清理资源
    return 0;
}