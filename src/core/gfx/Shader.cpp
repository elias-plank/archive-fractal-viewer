#include "Shader.h"
#include "../util/File.h"
#include <glm/gtc/type_ptr.hpp>

namespace FractalViewer {

	Shader::~Shader() {

		glDeleteShader(rendererId);
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
	}

	void Shader::Load(const std::string& vertexPath, const std::string& fragmentPath) {

		auto vertex = Util::ReadFile(vertexPath);
		auto fragment = Util::ReadFile(fragmentPath);

		vertexId = compileShader(vertex, GL_VERTEX_SHADER);
		fragmentId = compileShader(fragment, GL_FRAGMENT_SHADER);

		auto program = glCreateProgram();
		glAttachShader(program, vertexId);
		glAttachShader(program, fragmentId);
		glLinkProgram(program);


		GLint is_success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &is_success);
		if (is_success == 0) {

			std::string info;
			GLint length;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			info.resize(length);
			glGetProgramInfoLog(program, length, &length, &info[0]);
			glDeleteProgram(program);
			glDeleteProgram(vertexId);
			glDeleteProgram(fragmentId);

			ASSERT(false, info.c_str());
		}

		rendererId = program;
	}

	void Shader::Bind() const {

		glUseProgram(rendererId);
	}

	void Shader::Unbind() const {

		glUseProgram(0);
	}

	void Shader::SetInt(const std::string& uniformName, int value) {

		glUseProgram(rendererId);
		glUniform1i(uniformLocation(uniformName), value);
	}

	void Shader::SetFloat(const std::string& uniformName, float value) {

		glUseProgram(rendererId);
		glUniform1f(uniformLocation(uniformName), value);
	}

	void Shader::SetFloat2(const std::string& uniformName, const glm::vec2& value) {

		glUseProgram(rendererId);
		glUniform2f(uniformLocation(uniformName), value.x, value.y);
	}

	void Shader::SetFloat3(const std::string& uniformName, const glm::vec3& value) {

		glUseProgram(rendererId);
		glUniform3f(uniformLocation(uniformName), value.x, value.y, value.z);
	}

	void Shader::SetFloat4(const std::string& uniformName, const glm::vec4& value) {

		glUseProgram(rendererId);
		glUniform4f(uniformLocation(uniformName), value.x, value.y, value.z, value.w);
	}

	void Shader::SetDouble(const std::string& uniformName, double value) {

		glUseProgram(rendererId);
		glUniform1d(uniformLocation(uniformName), value);
	}

	void Shader::SetDouble2(const std::string& uniformName, const glm::dvec2& value) {

		glUseProgram(rendererId);
		glUniform2d(uniformLocation(uniformName), value.x, value.y);
	}

	void Shader::SetDouble3(const std::string& uniformName, const glm::dvec3& value) {

		glUseProgram(rendererId);
		glUniform3d(uniformLocation(uniformName), value.x, value.y, value.z);
	}

	void Shader::SetDouble4(const std::string& uniformName, const glm::dvec4& value) {

		glUseProgram(rendererId);
		glUniform4d(uniformLocation(uniformName), value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat4(const std::string& uniformName, const glm::mat4& value) {

		glUseProgram(rendererId);
		glUniformMatrix4fv(uniformLocation(uniformName), 1, GL_FALSE, glm::value_ptr(value));
	}

	const std::string& Shader::GetName() const {

		return name;
	}

	uint32_t Shader::compileShader(const std::string& source, uint32_t type) {

		GLuint shader = glCreateShader(type);
		const GLchar* csource = source.c_str();
		glShaderSource(shader, 1, &csource, NULL);

		glCompileShader(shader);

		GLint is_success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &is_success);

		if (is_success == 0) {

			std::string info;
			GLint length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			info.resize(length);
			glGetShaderInfoLog(shader, length, NULL, &info[0]);
			glDeleteShader(shader);
			ASSERT(false, info.c_str());
		}

		return shader;
	}

	int32_t Shader::uniformLocation(const std::string& uniformName) {

		if (uniformLocationCache.find(uniformName) != uniformLocationCache.end()) {

			return uniformLocationCache[uniformName];
		}

		auto location = glGetUniformLocation(rendererId, uniformName.c_str());

		// uniform doesn't exist
		if (location == -1) {

			ASSERT(false, std::string("Uniform " + uniformName + " doesn't exist.").c_str());
		}
		else {

			uniformLocationCache[uniformName] = location;
		}

		return location;
	}
}