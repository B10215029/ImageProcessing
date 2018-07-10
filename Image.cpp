#include "Image.h"

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

void ImageProcessing::Image::gray() {
	for (int i = 0, n = width * height; i < n; i++) {
		// Gray = 0.299 * Red + 0.587 * Green + 0.114 * Blue
		float color = 0;
		color += data[i * 4 + 0] * 0.299;
		color += data[i * 4 + 1] * 0.587;
		color += data[i * 4 + 2] * 0.114;
		data[i * 4 + 0] = color;
		data[i * 4 + 1] = color;
		data[i * 4 + 2] = color;
		progress = (float)i / (width * height) * 100;
	}
}

void ImageProcessing::Image::over(Image* image) {
	int width = this->width < image->width ? this->width : image->width;
	int height = this->height < image->height ? this->height : image->height;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int index1 = y * this->width + x;
			int index2 = y * image->width + x;
			float alpha1 = (float)this->data[index1 * 4 + 3] / 255;
			float alpha2 = (float)image->data[index2 * 4 + 3] / 255;
			this->data[index1 * 4 + 0] = this->data[index1 * 4 + 0] * (1 - alpha2) + image->data[index2 * 4 + 0] * alpha2;
			this->data[index1 * 4 + 1] = this->data[index1 * 4 + 1] * (1 - alpha2) + image->data[index2 * 4 + 1] * alpha2;
			this->data[index1 * 4 + 2] = this->data[index1 * 4 + 2] * (1 - alpha2) + image->data[index2 * 4 + 2] * alpha2;
			this->data[index1 * 4 + 3] = 255 - (1 - alpha1) * (1 - alpha2) * 255;
			progress = (float)(y * width + x) / (width * height) * 100;
		}
	}
}
