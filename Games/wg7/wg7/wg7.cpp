// wg7.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include "GameUnit.h"
#include "positionVector.h"
#include "UI.h"
#include "TeamBase.h"
#include <string>
#include "Image.h"
#include <thread>
#include <iostream>
#include <cstdlib>
template <class entity, class entityList>
void addEntity(entity entity, std::vector<entityList>  &list) { list.push_back(entity); }


using namespace std;
void initiateIncome(TeamBase * base, long allowancePeriod, int allowance) {
	base->initiateIncome(allowancePeriod, allowance);
}

void initiateUIThread(UI* gi, long graphicsUpdateSpeed) {
	gi->update(graphicsUpdateSpeed);
}
void initiateMovementThread(long visualGameSpeed) {
	GameUnit::moveUnitsTask(visualGameSpeed);
}
void initiateAttackLoopThread(long gameAttackSpeed) {
	GameUnit::attackLoop(gameAttackSpeed);
}

void CPU(UI* gi, TeamBase* enemybase, int width, int height, long speed) { //difficult is measured in gold gain per interval
	
	while (true) {
		int v = rand() % 10;

		if (v == 2) {
			GameUnit::hireUnit(GameUnit::ARCHER, enemybase, new positionVector( enemybase->baseImage->getCenter()->x, enemybase->baseImage->getCenter()->y), Image::getImageCopyByName("Archer", gi->ReusableImageCopies));
		}
		else if (v == 3) {
			GameUnit::hireUnit(GameUnit::MAGE, enemybase, new positionVector(enemybase->baseImage->getCenter()->x, enemybase->baseImage->getCenter()->y), Image::getImageCopyByName("Mage", gi->ReusableImageCopies));
		}
		//GameUnit::moveAllUnits(10, height - 10, enemybase->team);
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}


int main(int argc , char**argv)
{
	string PathBase = "C:\\Users\\GiMu7001\\Desktop\\wgpics\\";
	int _w = 800; //width of window
	int _h = 644; //height
	double hirebt_height = _h *0.06;
	double hirebt_width = _w * 0.07;
	double hirebt_Y = _h*0.05;
	double hirebtX_start = _w*0.3;
	double baseWidth = _w / 4;
	double baseHeight = _h / 4;
	double unit_Height = _h * 0.05;
	double unit_width = _w * 0.03;

	// make a home base
	TeamBase* homebase = new TeamBase(0, new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\homebase.PNG", "homebase", baseWidth, baseHeight, 0, _h - baseHeight), 1000);

// initialize interface

	UI* gi = new UI(_w, _h, "WG", homebase );
	
//// construct enemy base
	TeamBase * enemybase = new TeamBase(1, new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\enemybase.png", "enemybase", baseWidth, baseHeight, _w - baseWidth, 0), 1000);
	gi->addImage(enemybase->baseImage, true);
	

//load static images (background and buttons etc)
	gi->loadOutlinerImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\outlinerimage.PNG", "outlinerimage", 0, 0, 0, 0));
	gi->addImage( new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\hirewarrbt.PNG", "hirewarriorbt", hirebt_width, hirebt_height, hirebtX_start, hirebt_Y)  , true);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\hirearchbt.png", "hirearcherbt", hirebt_width, hirebt_height, hirebtX_start + hirebt_width, hirebt_Y), true);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\hiremagebt.png", "hiremagebt", hirebt_width, hirebt_height, hirebtX_start + 2*hirebt_width, hirebt_Y), true);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\attackbt.png", "attackbt", hirebt_width, hirebt_height, hirebtX_start - 2 * hirebt_width, hirebt_Y), true);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\standby.png", "standby", hirebt_width, hirebt_height, hirebtX_start - 3 * hirebt_width, hirebt_Y), true);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\retreat.png", "retreat", hirebt_width, hirebt_height, hirebtX_start - 4 * hirebt_width, hirebt_Y), true);

// load resuable images

	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\Warrior.png", "Warrior", unit_width, unit_Height, 0, 0), false);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\Archer.png", "Archer", unit_width, unit_Height, 0, 0), false);
	gi->addImage(new Image("C:\\Users\\GiMu7001\\Desktop\\wgpics\\Mage.png", "Mage", unit_width, unit_Height, 0, 0), false);

	///test area


	////
	// initiate movement thread to move units toward target locations
	std::thread movement_Thread { initiateMovementThread, 20 };

	// initiate attack loop thread for unit attack sensing enablement
	std::thread atack_Thread{ initiateAttackLoopThread, 1000 };

	// gui thread to update image positions
	std::thread UI_Thread { initiateUIThread, gi, 20 };


	// initiate CPU
	std::thread CPU_brain { CPU, gi, enemybase, _w, _h, 1000 };


	//initiate income for all bases.
	std::thread homebaseIncome{ initiateIncome, homebase, 5000, 50 };

	std::thread enemyBaseIncome{ initiateIncome, enemybase, 5000, 50 };

	//initiate input/command thread on main thread
	gi->senseInput();
	

    return 0;
}
