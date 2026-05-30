#include<iostream>
#include"renderer.h"
#include"shaderer.h"
#include"DrawCallData.h"
#include<thread>
#include "entt/entt.hpp"  

int Render() {
#pragma region Render



	GLFWwindow* window = nullptr;
	GLInit(window);

	if (window == nullptr)
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
	mvao.Bind();
	ElementsLayout layout;
	layout.Push<float>(2);

	VertexBuffer mvbo(position, 8 * sizeof(float));
	

	mvao.AddBuffer(mvbo, layout);
	IndexBuffer mibo(index, 6);
	mibo.Bind();

	Shader shader("res/shaders/BasicalShader.shader");
	shader.Bind();

	Texture mTexture("res/Textures/test1.png");
	mTexture.Bind();

	const int location = shader.GetUniformLocation("u_Color");
	float r = 0.0f;

	mvao.Unbind();
	mibo.Unbind();

	Renderer mRender;
	while (!glfwWindowShouldClose(window))
	{

		mRender.Clear(GL_COLOR_BUFFER_BIT);
	
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
	
		mRender.Draw(mvao, shader, mibo);
		glfwSwapBuffers(window);

		if (r > 1.0f)r = 0.0f;
		glfwPollEvents();
		r += 0.05f;
	}

	glfwTerminate();//终止GLFW库，清理资源
	return 0;
#pragma endregion
}
int GameLog() {
	//基于ecs
	return 1;
}

int main()
{
	std::thread enderThread(Render);
	std::thread gameLogThread(GameLog);
	enderThread.join();
	gameLogThread.join();
}