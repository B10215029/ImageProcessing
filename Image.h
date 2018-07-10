#pragma once
namespace ImageProcessing {
	class Image {
	public:
		Image(int width, int height, unsigned char* data, bool hasAlpha = true);
		~Image();
		int width;
		int height;
		int progress;
		double scale;
		int offsetX;
		int offsetY;
		unsigned char* data;

	public:
		void gray();
		void over(Image* image);
	};

	ref struct ImageVoidArgFunctionObject
	{
		typedef void (Image::*FunctionType)(void);
		FunctionType func;
		ImageVoidArgFunctionObject(FunctionType func) : func(func) {}
	};

	ref struct ImageImageArgFunctionObject
	{
		typedef void (Image::*FunctionType)(Image*);
		FunctionType func;
		Image* image;
		ImageImageArgFunctionObject(FunctionType func, Image* image2) : func(func), image(image2) {}
	};
}
