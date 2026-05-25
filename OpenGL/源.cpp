#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>

int main(void)
{
    GLFWwindow* window;

	//初始化GLFW库
    if (!glfwInit())
        return -1;

    //创建一个窗口，被window指针接受
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)//如果创建失败
    {
        glfwTerminate();
        return -1;
    } 

	//将窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);


	//初始化GLEW库

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
	glGenBuffers(1, &a);//生成一个缓冲对象，并将其ID存储在变量a中
	glBindBuffer(GL_ARRAY_BUFFER, a);//指定a缓冲区的类型为GL_ARRAY_BUFFER，并将其绑定到当前上下文中
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);//将数据复制到当前绑定的缓冲区对象中，数据大小为6个float，数据来源于position数组，使用GL_STATIC_DRAW作为使用模式


   //循环直到用户关闭窗口

    while (!glfwWindowShouldClose(window))
    {
		//在这里我们可以进行渲染操作
        glClear(GL_COLOR_BUFFER_BIT);

        
		glDrawArrays(GL_TRIANGLES, 0, 3);//绘制调用。GL_TRIANGLES表示绘制模式，0表示从数组的第一个顶点开始，3表示绘制3个顶点

		//交换前后缓冲区，以显示渲染结果
        glfwSwapBuffers(window);

		//检查是否有事件被触发（比如键盘输入、鼠标移动等），并调用相应的回调函数
        glfwPollEvents();
    }

	glfwTerminate();//终止GLFW库，清理资源
    return 0;
}