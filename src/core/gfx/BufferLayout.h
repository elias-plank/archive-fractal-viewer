#pragma once
#include <vector>

namespace FractalViewer {

	enum class ShaderDataType {

		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat4
	};

	struct BufferElement {

		uint32_t stride;
		uint32_t count;
		uint32_t type;
		bool normalized;

		BufferElement(ShaderDataType type, bool normalized = false);
	};

	class BufferLayout {

	private:
		std::vector<BufferElement> elements;

	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements);

		std::vector<BufferElement> GetElements() const;
		uint32_t GetTotalStride() const;
	};
}


