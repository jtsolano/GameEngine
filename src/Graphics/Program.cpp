#include <Program.h>

GLuint GetShaderCode(EShaderType InShaderType)
{
	switch (InShaderType)
	{
	case EShaderType::VERTEX_SHADER:
		return GL_VERTEX_SHADER;

	case EShaderType::FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
	}
}


Program::~Program()
{
	if (m_ProgramId != 0)
	{
		Destroy();
	}
}

void Program::Init()
{
	m_ProgramId = glCreateProgram();
}

void Program::AddShader(EShaderType InShaderType, string InShaderPath)
{


}

void Program::AddShader(EShaderType InShaderType, const char* ShaderCode)
{
	if (m_ProgramId == 0)
	{
		Init();
	}

	uint ShaderId = glCreateShader(GetShaderCode(InShaderType));
	glShaderSource(ShaderId, 1, &ShaderCode, nullptr);
	glCompileShader(ShaderId);

	// Check if it compiled.
	int Ok;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Ok);

	if (!Ok)
	{
		char Log[512];
		glGetShaderInfoLog(ShaderId, 512, nullptr, Log);
		cout << Log << endl;
		glDeleteShader(ShaderId);
	}

	glAttachShader(m_ProgramId, ShaderId);
	ShadersIds.push_back(ShaderId);
}

void Program::Compile()
{
	glLinkProgram(m_ProgramId);

	int Ok;
	glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &Ok);
	if (!Ok)
	{
		char Log[512];
		glGetProgramInfoLog(m_ProgramId, 512, nullptr, Log);
		cout << Log << endl;
	}

	ClearShaders();
}

void Program::Use()
{
	glUseProgram(m_ProgramId);
}

void Program::Destroy()
{
	glDeleteProgram(m_ProgramId);
	m_ProgramId = 0;
	ClearShaders();
}

void Program::ClearShaders()
{
	// Delete all shaders
	for (uint ShaderId : ShadersIds)
	{
		glDeleteShader(ShaderId);
	}
	ShadersIds.clear();
}
