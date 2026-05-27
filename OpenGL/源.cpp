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



	unsigned int index[] = {
				0, 1, 2,
				2,3,0

	};

	VertexArray mvao;
	ElementsLayout layout;
	layout.Push<float>(2);

	VertexBuffer mvbo(position, 8 * sizeof(float));
	IndexBuffer mibo(index, 6);

	mvao.AddBuffer(mvbo, layout);
	
	mibo.Bind();

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
		mibo.Bind();
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