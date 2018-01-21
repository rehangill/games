#pragma once
#include "stdafx.h"
#include <SDL_image.h>
#include "Image.h"
#include <vector>
#include <math.h>
#include <SDL.h>
#include "TeamBase.h"
class UI
{
public:
	
	SDL_Window* _window = nullptr;
	std::vector<Image*> staticImagesToDisplay;
	std::vector<Image*> ReusableImageCopies;
	Image* _selectedImage;
	std::vector<TeamBase*> teamBases;
	TeamBase * homeBase;

	static bool clickedButton(double btCenterX, double btCenterY, double clickX, double clickY, double width, double height);


	UI(int width, int height, char * name, TeamBase * homeBase);

	void UI::senseInput();
	void renderText(char * text, SDL_Color color, double width, double height, double x, double y);
	void renderUnits();
	void renderBaseHealth();
	void update(long GRAPHICS_UPDATE_PERIOD);


	void addImage(Image * image, bool staticImage);

	void loadOutlinerImage(Image * image);



private:
	//fields		
	double _windowWidth;
	double _windowHeight;
	SDL_Renderer* renderer = nullptr;
	Image* _outlineForSelectedImages = nullptr;
	//func
	

	void renderSurface(Image * image);
	void render(SDL_Texture * texture, double width, double height, double x, double y);
	void renderList(std::vector<Image*> items);
	void OnKeyPress(SDL_KeyboardEvent key);
	void OnClick(SDL_MouseButtonEvent click);
	Image * getClickedImage(double x, double y);
	~UI();

	void outline(Image * image);
	bool _imageSelected = false;


};

