#include <Program.h>

GLuint GetShaderCode(EShaderType InShaderType)
{
	switch (InShaderType)
	{
	case EShaderType::VERTEX_SHADER:
		return GL_VERTEX_SHADER;

	case EShaderType::FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
	default:
		return 0;
	}
}


Program::Program()
{
	m_ProgramId = glCreateProgram();
}

Program::~Program()
{
	if (m_ProgramId != 0)
	{
		glDeleteProgram(m_ProgramId);
		m_ProgramId = 0;
	}

	ClearShaders();
}

void Program::AddShader(EShaderType InShaderType, const char* ShaderCode)
{
	GLuint ShaderType = GetShaderCode(InShaderType);
	if (ShaderType == 0)
	{
		cout << "Invalid shader enum while adding shader" << endl;
		return;
	}

	uint ShaderId = glCreateShader(ShaderType);
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
		return;
	}

	glAttachShader(m_ProgramId, ShaderId);
	ShadersIds.push_back(ShaderId);
}

void Program::AddShader(string ShaderSource)
{
	unordered_map<EShaderType, string> ShaderStagesMap;

	EShaderType CurrentStaderType;
	
	bool bHasStage = false;

	size_t Pos = 0;
	while (Pos < ShaderSource.size())
	{
		// Find next line end
		size_t LineEndPos = ShaderSource.find('\n', Pos);

		// Handles last line where there might not be a \n
		if (LineEndPos == string::npos)
		{
			LineEndPos = ShaderSource.size();
		}

		// Get current line
		string CurrentLine = ShaderSource.substr(Pos, LineEndPos - Pos);

		// Windows line endings can have \r at end and it breaks comparisons, remove it.
		if (!CurrentLine.empty() && CurrentLine.back() == '\r')
		{
			CurrentLine.pop_back();
		}

		// Detect stage
		if (CurrentLine.rfind("#stage ", 0) == 0)
		{
			// Get substring that starts at 7 and up to the end of CurrentLine.
			string stageName = CurrentLine.substr(7);

			if (stageName == "vertex")
			{
				CurrentStaderType = EShaderType::VERTEX_SHADER;
			}
			else if (stageName == "fragment")
			{
				CurrentStaderType = EShaderType::FRAGMENT_SHADER;
			}
			else
			{
				cout << "Unknown shader stage: " + stageName << endl;
			}

			bHasStage = true;
			ShaderStagesMap[CurrentStaderType].clear();
		}
		else if (bHasStage) {
			ShaderStagesMap[CurrentStaderType] += CurrentLine;
			ShaderStagesMap[CurrentStaderType] += '\n';
		}

		Pos = (LineEndPos < ShaderSource.size()) ? LineEndPos + 1 : LineEndPos;
	}

	for (const pair<EShaderType, string>& ShaderStage : ShaderStagesMap)
	{
		AddShader(ShaderStage.first, ShaderStage.second.c_str());
	}
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

void Program::SetUniformMatrix4f(const string& UniformName, float* Matrix)
{
	int UniformLocation = glGetUniformLocation(m_ProgramId, UniformName.c_str());
	glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, Matrix);
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
