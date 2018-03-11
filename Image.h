#pragma once
namespace ImageProcessing {
	class Image {
	public:
		Image(int width, int height, unsigned char* data, bool hasAlpha = true);
		~Image();
		int width;
		int height;
		unsigned char* data;
	};
}
