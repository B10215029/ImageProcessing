#include "Image.h"
#include <cstring>

ImageProcessing::Image::Image(int width, int height, unsigned char* data, bool hasAlpha) {
	this->width = width;
	this->height = height;
	this->progress = 0;
	this->scale = 0;
	this->offsetX = 0;
	this->offsetY = 0;
	this->data = new unsigned char[width * height * 4];
	if (hasAlpha) {
		for (int i = 0, n = width * height; i < n; i++) {
			this->data[i * 4 + 0] = data[i * 4 + 2];
			this->data[i * 4 + 1] = data[i * 4 + 1];
			this->data[i * 4 + 2] = data[i * 4 + 0];
			this->data[i * 4 + 3] = data[i * 4 + 3];
		}
	}
	else {
		int aligmentOffset = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int index = i * width + j;
				this->data[index * 4 + 0] = data[index * 3 + 2 + aligmentOffset];
				this->data[index * 4 + 1] = data[index * 3 + 1 + aligmentOffset];
				this->data[index * 4 + 2] = data[index * 3 + 0 + aligmentOffset];
				this->data[index * 4 + 3] = 255;
			}
			aligmentOffset += width % 4;
		}
	}
}

ImageProcessing::Image::~Image() {
	delete[] this->data;
}
