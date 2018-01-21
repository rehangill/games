#pragma once
#include "stdafx.h"
#include "GameUnit.h"
#include "Worker.h"
#include "Warrior.h"
#include "Archer.h"
#include "Mage.h"
#include "UI.h"
#include "Catapult.h"
#include <thread>
#include <iostream>

template <class entity, class entityList>
void addEntity(entity entity, std::vector<entityList>  &list) { list.push_back(entity); }

static std::vector<GameUnit*> allGameUnits;

void GameUnit::hireUnit(GameUnit::UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image* unitDiplay) {
	if (base->gold > base->UNIT_HIRE_COST[type]) {
		base->gold -= base->UNIT_HIRE_COST[type];
		GameUnit::spawn(type, base, startPos, unitDiplay);
	}
}


void GameUnit::spawn(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image* unitDiplay)
{
	if (base->destroyed) return;
	if (type == WORKER) addEntity(new Worker(type, base, startPos, unitDiplay), allGameUnits);
	else if (type == WARRIOR) addEntity(new Warrior(type, base, startPos, unitDiplay), allGameUnits);
	else if (type == ARCHER) addEntity(new Archer(type, base, startPos, unitDiplay), allGameUnits);
	else if (type == MAGE) addEntity(new Mage(type, base, startPos, unitDiplay), allGameUnits);
	else if (type == CATAPULT) addEntity(new Catapult(type, base, startPos, unitDiplay), allGameUnits);

}


void GameUnit::_Init(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image* unitDiplay) {
	this->unitDisplay = unitDiplay;
	this->unitType = type;
	this->base = base;
	this->unitDisplay->coords = startPos;
	this->targetPosition = startPos;
	this->speed = STEP_SIZE_SCALING_CONSTANT * UNIT_SPEED_RATIOS[this->unitType];
	this->attackDamage = ATTACK_DAMAGE_SCALING_CONSTANT* UNIT_ATTACK_DAMAGE_RATIOS[this->unitType];
	this->hp = HP_SCALING_CONSTANT* UNIT_HP_RATIOS[this->unitType];
	this->range = RANGE_SCALING_CONSTANT* UNIT_RANGE_RATIOS[this->unitType];
	this->unitDisplay->height *= UNIT_SIZE_RATIOS[this->unitType];
	this->unitDisplay->width *= UNIT_SIZE_RATIOS[this->unitType];


}

GameUnit::GameUnit() {

}


GameUnit::~GameUnit()
{
}

std::vector<GameUnit*> GameUnit::getAllUnits() { return allGameUnits; }

void GameUnit::takeDamage(double damage)
{
	this->hp -= damage;
	if (this->hp <= 0) die();
}

void GameUnit::die() {
	/*int pos = this - allGameUnits[0];
	allGameUnits.erase(allGameUnits.begin() + pos);
	delete this;*/
	this->dead = true;
	this->unitDisplay = nullptr;
	this->base = nullptr;


}

void GameUnit::attack(GameUnit* unit) {
	unit->takeDamage(this->attackDamage);
}

positionVector * GameUnit::anyUnitsOnBase(TeamBase * base, int team)
{
	for each (GameUnit* unit in allGameUnits)
	{
		if (unit->dead) continue;
		if (unit->base->team == team & UI::clickedButton(base->baseImage->coords->x,
			base->baseImage->coords->y,
			unit->unitDisplay->coords->x,
			unit->unitDisplay->coords->y,
			base->baseImage->width,
			base->baseImage->height)) {
			return new positionVector(unit->unitDisplay->coords->x, unit->unitDisplay->coords->y);
		}
	}
	return nullptr;
}

void GameUnit::senseAndAttack() {
	for each (GameUnit* unit in allGameUnits)
	{
		if (unit->dead) continue;
		double distance = positionVector::getLength
		(
			this->unitDisplay->getCenter()->x,
			this->unitDisplay->getCenter()->y,
			unit->unitDisplay->getCenter()->x,
			unit->unitDisplay->getCenter()->y
		);

		if (unit->base->team != this->base->team  & distance < this->range)
		{
			this->attack(unit);
			return;
		}

		else {// check if you are in range of any enemy base

			for each (TeamBase* base in TeamBase::getAllBases())
			{
				// check if the unit is in an enemy base
				if (base != unit->base & !base->destroyed  & UI::clickedButton(
					base->baseImage->coords->x,
					base->baseImage->coords->y,
					unit->unitDisplay->getCenter()->x,
					unit->unitDisplay->getCenter()->y,
					base->baseImage->width,
					base->baseImage->height))
				{
					// unit is in enemy base....

					////get copy of defenders location: 
					//positionVector* defLocation = anyUnitsOnBase(base, base->team);

					//if (defLocation == nullptr)// no defenders
					//{
					//	base->takeDamage(unit->attackDamage);	continue;

					//}

					//else { // defenders present

					//	unit->moveUnit(defLocation->x, defLocation->y, unit->unitDisplay->coords->x, unit->unitDisplay->coords->y);
					//}



				}
			}

		}

	}
}

void GameUnit::attackLoop(long gameAttackSpeed) {

	while (true) {
		for each (GameUnit* unit in allGameUnits)
		{
			if (unit->dead) continue;
			unit->senseAndAttack();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(gameAttackSpeed));
	}
}

void GameUnit::takeStep() {
	positionVector * targetDirection = positionVector::subtract(this->targetPosition, this->unitDisplay->coords);
	targetDirection->normalize();
	double dx = targetDirection->x* this->speed;
	double dy = targetDirection->y* this->speed;
	this->unitDisplay->coords->add(dx, dy);

}
void GameUnit::moveUnitsTask(long VISUAL_GAME_SPEED)
{
	while (true) {
		for each (GameUnit* unit in allGameUnits)
		{
			if (unit->dead) continue;
			double xdiff = abs(unit->unitDisplay->coords->x - unit->targetPosition->x);
			double ydiff = abs(unit->unitDisplay->coords->y - unit->targetPosition->y);
			double thresholdy = unit->unitDisplay->height * unit->MOVEMENT_HALT_THRESHOLD_SPACE_OF_SIZE_RATIO;
			double thresholdx = unit->unitDisplay->width *unit->MOVEMENT_HALT_THRESHOLD_SPACE_OF_SIZE_RATIO;

			if (xdiff > thresholdx & ydiff > thresholdy)
			{
				unit->takeStep();
			}

		}
		std::this_thread::sleep_for(std::chrono::milliseconds(VISUAL_GAME_SPEED));
	}
}

void GameUnit::moveAllUnits(double x, double y, int team) {
	for each (GameUnit* unit in allGameUnits)
	{
		if (unit->dead) continue;
		if (unit->base->team == team) { unit->targetPosition = new positionVector(x, y); }
	}
}

void GameUnit::moveUnit(double newX, double newY, double imageX, double imageY) {
	for each (GameUnit* unit in allGameUnits)
	{
		if (unit->dead) continue;
		if (unit->unitDisplay->coords->x == imageX & unit->unitDisplay->coords->y == imageY) unit->targetPosition = new positionVector(newX, newY);
	}
}

