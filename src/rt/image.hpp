#pragma once
#include "types.hpp"

#include <algorithm>
#include <glm/glm.hpp>

namespace rt {
	struct pixel {
		u8 r, g, b;
		inline pixel() : r(0), g(0), b(0) {}
		inline pixel(u8 R, u8 G, u8 B) : r(R), g(G), b(B) {}
		inline pixel(const glm::vec3& vec)
			: r(u8(256 * std::clamp(vec.x, 0.0f, 0.99999f))), g(u8(256 * std::clamp(vec.y, 0.0f, 0.99999f))),
			b(u8(256 * std::clamp(vec.z, 0.0f, 0.99999f))) {}
	};

	class image {
		pixel* pdata;
	public:
		const u32 width;
		const u32 height;

		pixel& at(u32 X, u32 Y);
		const pixel& at(u32 X, u32 Y) const;

		image(u32 Width, u32 Height);
		~image();

		void to_png(const char* filename) const;
		void to_jpg(const char* filename) const;
	};
}
