#pragma once

enum class EShaderType
{
	UNKNOWN_SHADER,
	VERTEX_SHADER,
	FRAGMENT_SHADER,

};

class Program
{
public:
	Program();

	~Program();

	// Passes in directly the shader code.
	void AddShader(EShaderType InShaderType, const char* ShaderCode);

	void AddShader(string ShaderSource);

	void Compile();

	// Activates and uses this program.
	void Use();

	void SetUniformMatrix4f(const string& UniformName, float* Matrix);

	uint GetProgramID() const { return m_ProgramId; }

protected:

	void ClearShaders();

	uint m_ProgramId = 0;
	vector<uint> ShadersIds;
};