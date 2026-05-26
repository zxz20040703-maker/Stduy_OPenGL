#include"shaderer.h"




 ShaderProgramResource ParseShader(std::string filePath)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(filePath);	//文件读取流
	std::string line;
	std::stringstream ss[2];	//字符串流数组
	ShaderType type = ShaderType::NONE;

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
 unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);//通过glCreateShader函数创建一个新对象，返回一个唯一的id
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);//把字符串附加给id指定的对象，nullptr表示字符串以null结尾
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);//查看编译状态
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

 int CreatShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;

}
