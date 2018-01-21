#include "stdafx.h"
#include "TeamBase.h"
#include <SDL_image.h>
#include <vector>
#include <thread>
template <class entity, class entityList>
void addEntity(entity entity, std::vector<entityList>  &list) {list.push_back(entity);}
static std::vector <TeamBase*> allbases;
TeamBase::TeamBase(int team, Image* baseImage, double baseHealth) // put the increment higher and keep allowance speed low
{
	this->gold = this->STARTING_GOLD;
	this->team = team;
	this->baseImage = baseImage;
	this->totalHp = baseHealth;
	this->hp = baseHealth;



	addEntity(this, allbases);
}

void TeamBase::takeDamage(double damage)
{
	this->hp -= damage;
	if (this->hp <= 0) this->destroy();

	
}

void TeamBase::destroy() {
	this->destroyed = true;
	this->gold = 0;
	this->baseImage->height = 0;
	this->baseImage->width = 0;
}

void TeamBase::initiateIncome(long bankAllowanceSpeed, int increment) {
	
	while (!this->destroyed)
	{
		this->gold += increment;
		std::this_thread::sleep_for(std::chrono::milliseconds(bankAllowanceSpeed));
	}
}
TeamBase::~TeamBase()
{
}

std::vector<TeamBase*> TeamBase::getAllBases() { return allbases; }
