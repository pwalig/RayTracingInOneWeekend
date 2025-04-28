#pragma once
#include "types.hpp"

#include <glm/glm.hpp>

namespace rt {
	struct pixel {
		u8 r, g, b;
		inline pixel() : r(0), g(0), b(0) {}
		inline pixel(u8 R, u8 G, u8 B) : r(R), g(G), b(B) {}
		inline pixel(const glm::vec3& vec)
			: r(u8(255.999f * vec.x)), g(u8(255.999f * vec.y)),
			b(u8(255.999f * vec.z)) {}
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
