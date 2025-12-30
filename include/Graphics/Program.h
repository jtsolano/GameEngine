#pragma once

enum class EShaderType
{
	VERTEX_SHADER,
	FRAGMENT_SHADER,

};

class Program
{
public:
	Program() {}

	~Program();


	// Specifies a shader path from the shaders folder to load the shader from.
	void AddShader(EShaderType InShaderType, string InShaderPath);

	// Passes in directly the shader code.
	void AddShader(EShaderType InShaderType, const char* ShaderCode);

	void Compile();

	// Activates and uses this program.
	void Use();

	// Destroys the program.
	void Destroy();

	uint GetProgramID() const { return m_ProgramId; }

protected:

	void Init();

	void ClearShaders();

	uint m_ProgramId = 0;
	vector<uint> ShadersIds;
};