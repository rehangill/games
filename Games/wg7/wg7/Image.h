#pragma once
#include "stdafx.h"
#include "Image.h"
#include <SDL_image.h>
#include <vector>
#include "positionVector.h"
class Image
{
public:
	Image(char * path, char * name,  double width, double height, double x, double y);
	Image();
	~Image();
	static Image * getImageByName(char * name, std::vector<Image*> list);
	static Image * getImageCopyByName(char * name, std::vector<Image*> list);
	void changeImageAttributes(double width, double height, double x, double y);
	void shrinkToDisappear();
	positionVector * getCenter();
	Image * getImageFromLocation(double x, double y, std::vector<Image*> list);
	char * path;
	char * name;
	/*double x;
	double y;*/
	double width;
	double height;
	SDL_Surface* surface;
	positionVector * coords;
};

