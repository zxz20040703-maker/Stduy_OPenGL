#include<iostream>
#include"renderer.h"
#include"shaderer.h"
#include"DrawCallData.h"

int main()
{
	GLFWwindow* window = nullptr;
	 GLInit(window);

	if(window == nullptr)
		return -1;

	glfwSwapInterval(1);

    float position[] = {
        -0.5f, -0.5f,
         0.5f,  -0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f

	};//在内存空间定义了一组数据，后续会发送到GPU中进行处理


	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);



	unsigned int index[] = {
				0, 1, 2,
				2,3,0

	};


	VertexBuffer mvbo(position, 8 * sizeof(float));
	glEnableVertexAttribArray(0);//启用顶点属性0
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);//设置顶点属性指针，告诉OpenGL如何解析顶点数据
	IndexBuffer mibo(index, 6);

	ShaderProgramResource source = ParseShader("res/shaders/BasicalShader.shader");

	unsigned int shader = CreatShader(source.VertexShader ,source.FragmentShader);
	glUseProgram(shader);
	std::cout << source.FragmentShader;

	int location = glGetUniformLocation(shader, "u_Color"); 
	float r = 0.0f;

	
    while (!glfwWindowShouldClose(window))
    {
		
        glClear(GL_COLOR_BUFFER_BIT);

		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
        glfwSwapBuffers(window);

		if (r > 1.0f)r = 0.0f;
		  glfwPollEvents();
		  r += 0.05f;
    }

	glDeleteProgram(shader);
	glfwTerminate();//终止GLFW库，清理资源
    return 0;
}