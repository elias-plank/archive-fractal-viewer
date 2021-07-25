#pragma once
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace FractalViewer {

	class Shader {

	private:
		std::string name;
		uint32_t rendererId;
		uint32_t vertexId;
		uint32_t fragmentId;

		std::unordered_map<std::string, int32_t> uniformLocationCache;

	public:
		Shader() = default;
		~Shader();

		void Load(const std::string& vertexPath, const std::string& fragmentPath);

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& uniformName, int value);
		void SetFloat(const std::string& uniformName, float value);
		void SetFloat2(const std::string& uniformName, const glm::vec2& value);
		void SetFloat3(const std::string& uniformName, const glm::vec3& value);
		void SetFloat4(const std::string& uniformName, const glm::vec4& value);
		void SetDouble(const std::string& uniformName, double value);
		void SetDouble2(const std::string& uniformName, const glm::dvec2& value);
		void SetDouble3(const std::string& uniformName, const glm::dvec3& value);
		void SetDouble4(const std::string& uniformName, const glm::dvec4& value);
		void SetMat4(const std::string& uniformName, const glm::mat4& value);

		const std::string& GetName() const;

	private:
		uint32_t compileShader(const std::string& source, uint32_t type);
		int32_t uniformLocation(const std::string& uniformName);
	};
}