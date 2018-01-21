#include "stdafx.h"
#include "Image.h"
#include <SDL_image.h>
#include <vector>
#include <string>
template <class entity, class entityList>
void addEntity(entity entity, std::vector<entityList>  &list) { list.push_back(entity); }
//static std::vector<Image*> allImages;


Image::Image(char * path, char * name,  double width, double height, double x, double y)
{
	this->path = path;
	this->name = name;
	this->width = width;
	this->height = height;
	this->surface = IMG_Load(path);
	this->coords = new positionVector(x, y);
}

Image::Image(){}

Image::~Image()
{
}
Image* Image::getImageByName(char * name, std::vector<Image*> list) {
	for each (Image* image in list)
	{
		if (name == image->name) { return image; }
	}
	return nullptr;
}
Image* Image::getImageCopyByName(char * name, std::vector<Image*> list) {
	for each (Image* image in list)
	{
		if (name == image->name) { return new Image(image->path, image->name, image->width, image->height, image->coords->x, image->coords->y); }
	}
	return nullptr;
}

void Image::changeImageAttributes(double width, double height, double x, double y) { //enter new attributes
	this->width = width;
	this->height = height;
	this->coords->x = x;
	this->coords->y = y;
}
void Image::shrinkToDisappear() {
	this->width = 0;
	this->height = 0;
}

positionVector * Image::getCenter() {
	return new positionVector(this->coords->x + this->width / 2.0, this->coords->y + this->height / 2.0);
}