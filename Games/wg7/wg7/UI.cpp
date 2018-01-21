#pragma once
#include "stdafx.h"
#include "UI.h"
#include <SDL_image.h>
#include "Image.h"
#include <vector>
#include <math.h>
#include <SDL.h>
#include "TeamBase.h"
#include <stdlib.h>
#include "GameUnit.h"
#include <thread>
#include <iostream>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
using namespace std;

template <class entity, class entityList>
void addEntity(entity entity, std::vector<entityList>  &list) { list.push_back(entity); }

UI::UI(int width, int height, char * name, TeamBase * homeBase)/// creates a UI window, please assign an outliner Image...
{
	this->homeBase = homeBase;
	_windowHeight = height;
	_windowWidth = width;
	addImage(homeBase->baseImage, true);
	SDL_Init(SDL_INIT_EVERYTHING);
	_window =
		SDL_CreateWindow
		(
			name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL
		);

	TTF_Init();
	renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

}

void UI::senseInput()
{
	SDL_Event e;
	while (SDL_WaitEvent(&e))
	{

		if (e.type == SDL_MOUSEBUTTONUP) {
			OnClick(e.button);
		}

		else if (e.type = SDL_KEYUP) {
			OnKeyPress(e.key);
		}
		else if (e.type = SDL_QUIT) {
			SDL_Quit();
		}
	}
}


void UI::renderText(char * text, SDL_Color color, double width, double height, double x, double y ) {

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(TTF_OpenFont("C:\\windows\\fonts\\calibri.ttf", 3*height), text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	render( texture, width, height, x, y);
	
}

void UI::renderUnits() {
	for each (GameUnit* unit in GameUnit::getAllUnits())
	{
		if (unit->dead) continue;
		renderSurface(unit->unitDisplay);
	}
}


void UI::renderBaseHealth() {
	for each (TeamBase* base in TeamBase::getAllBases())
	{
		char health[64];
		sprintf_s(health, "%d", (int)((base->hp/base->totalHp)* 100 ));
		renderText(health, SDL_Color{ 0,120,0 }, _windowWidth* 0.06, _windowHeight * 0.05, base->baseImage->coords->x, base->baseImage->coords->y);

	}
}

void UI::update(long GRAPHICS_UPDATE_PERIOD) { // enter a high value for smoother gameplay
	while (true) {
		SDL_RenderClear(renderer);

		char gold[64];
		sprintf_s(gold, "%d", homeBase->gold);

		renderList(staticImagesToDisplay);
		renderUnits();
		renderText(gold, SDL_Color{ 255,244,0 }, _windowWidth* 0.06, _windowHeight * 0.05, _windowWidth* 0.66, _windowHeight * 0.046);
		renderText("Gold:", SDL_Color { 255,244,0 }, _windowWidth* 0.07, _windowHeight * 0.06, _windowWidth* 0.59, _windowHeight * 0.04);

		if (_outlineForSelectedImages != nullptr) {
			renderSurface //////
			(
				_outlineForSelectedImages
			);
		}


		renderBaseHealth();

		SDL_RenderPresent(renderer);
		std::this_thread::sleep_for(std::chrono::milliseconds(GRAPHICS_UPDATE_PERIOD));
	}
	
}
void UI::renderSurface(Image * image) {
	if (image == nullptr) return;
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image->surface);
		render(texture, image->width, image->height, image->coords->x, image->coords->y);
}

void UI::render(SDL_Texture* texture, double width, double height, double x, double y) {
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	destination.h = height;
	destination.w = width;
	SDL_RenderCopy(renderer, texture, NULL, &destination);
	SDL_DestroyTexture(texture);
}

void UI::renderList(std::vector<Image*> items) {
	for each (Image* image in items)
	{
		renderSurface(image);
	}
}
bool UI::clickedButton(double btTopLeftCornerX, double btTopLeftCornerY, double clickX, double clickY, double width, double height) {

	if ((clickX > btTopLeftCornerX) & (clickY > btTopLeftCornerY) &  (clickX - btTopLeftCornerX <= width) & (clickY - btTopLeftCornerY <= height)) {
		return true;
	}
	return false;
}

void UI::OnKeyPress(SDL_KeyboardEvent key)
{

}

Image* UI::getClickedImage(double x, double y) {
	
	for each (GameUnit* unit in GameUnit::getAllUnits())
	{
		if (unit->dead) continue;
		if (clickedButton(unit->unitDisplay->coords->x, unit->unitDisplay->coords->y, x, y, unit->unitDisplay->width, unit->unitDisplay->height))
		{
			return unit->unitDisplay;
		}
	}
	for each (Image* bt in staticImagesToDisplay)
	{
		if (clickedButton(bt->coords->x, bt->coords->y, x, y, bt->width, bt->height))
		{
			return bt;
		}
	}

	_outlineForSelectedImages->shrinkToDisappear();
	return nullptr;
}

UI::~UI()
{
}
void UI::outline(Image * image) {
	_outlineForSelectedImages->changeImageAttributes(image->width, image->height, image->coords->x, image->coords->y);
}
void UI::addImage(Image* image, bool staticImage ) {
	if (staticImage) { addEntity(image, staticImagesToDisplay); }
	else { addEntity(image, ReusableImageCopies); }
}
void UI::loadOutlinerImage(Image * image) {
	this->_outlineForSelectedImages = image;
}

void UI::OnClick(SDL_MouseButtonEvent click) {
	_outlineForSelectedImages->shrinkToDisappear();

	Image * clickedImage = getClickedImage(click.x, click.y); // new image selected	

	if (_selectedImage == nullptr & clickedImage == nullptr) return;

	else if (_selectedImage == nullptr) { // nothing selected b4
		_selectedImage = new Image(clickedImage->path, clickedImage->name, clickedImage->width, clickedImage->width, clickedImage->coords->x, clickedImage->coords->y);
		outline(clickedImage);
	}

	else if (_selectedImage != nullptr) { // something selected (no need to outline anything now)
		if (clickedImage != nullptr) { // 2 images clicked
			if (clickedImage->name == "homebase" & _selectedImage->name == "hireworkerbt") { GameUnit::hireUnit(GameUnit::WORKER, homeBase, new positionVector(click.x, click.y), Image::getImageCopyByName("Worker", ReusableImageCopies)); }
			else if (clickedImage->name == "homebase" & _selectedImage->name == "hirewarriorbt") { GameUnit::hireUnit(GameUnit::WARRIOR, homeBase, new positionVector(click.x, click.y), Image::getImageCopyByName("Warrior", ReusableImageCopies)); }
			else if (clickedImage->name == "homebase" & _selectedImage->name == "hirearcherbt") { GameUnit::hireUnit(GameUnit::ARCHER, homeBase, new positionVector(click.x, click.y), Image::getImageCopyByName("Archer", ReusableImageCopies)); }
			else if (clickedImage->name == "homebase" & _selectedImage->name == "hiremagebt") { GameUnit::hireUnit(GameUnit::MAGE, homeBase, new positionVector(click.x, click.y), Image::getImageCopyByName("Mage", ReusableImageCopies)); }
			else if (clickedImage->name == "homebase" & _selectedImage->name == "hirecatapultbt") { GameUnit::hireUnit(GameUnit::CATAPULT, homeBase, new positionVector(click.x, click.y), Image::getImageCopyByName("Catapult", ReusableImageCopies)); }
			else if (clickedImage->name == "enemybase" & _selectedImage->name == "attackbt") { GameUnit::moveAllUnits(click.x, click.y, this->homeBase->team); }
			else if (clickedImage->name == "homebase" & _selectedImage->name == "retreat") { GameUnit::moveAllUnits(click.x, click.y, this->homeBase->team); }
		}
		else if (clickedImage == nullptr) // image then map is clicked
		{
			if (_selectedImage->name == "standby") { GameUnit::moveAllUnits(click.x, click.y, this->homeBase->team); }
			else if ( _selectedImage->name == "Worker" || _selectedImage->name == "Warrior" || _selectedImage->name == "Archer" || _selectedImage->name == "Mage" || _selectedImage->name == "Catapult")
			{			
				GameUnit::moveUnit(click.x, click.y, _selectedImage->coords->x, _selectedImage->coords->y);
			}
			
		}
		_selectedImage = nullptr;
	}
	clickedImage == nullptr;
}


