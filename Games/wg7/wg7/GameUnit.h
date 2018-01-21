#pragma once
#include "Image.h"

#include "positionVector.h"
#include <vector>
#include "TeamBase.h"

class GameUnit
{
public:
	const enum UNIT_TYPE { WORKER, WARRIOR, ARCHER, MAGE, CATAPULT };
//	const enum UNIT_STATUS { STANDBY, ENGAGED, CHARGING, RETREATING };//?????

	static void moveUnitsTask(long VISUAL_GAME_SPEED);

	static void moveAllUnits(double x, double y, int team);

	// void moveAllUnits(double x, double y, TeamBase * homeBase);

	static void moveUnit(double newX, double newY, double imageX, double imageY);

	void die();

	void senseAndAttack();

	static void attackLoop(long gameAttackSpeed);

	static void hireUnit(GameUnit::UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);

	static void spawn(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);
	void _Init(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);
	
	bool dead = false;
	TeamBase* base;

	
	GameUnit();
	~GameUnit();

	static std::vector<GameUnit*> getAllUnits();
	
	Image* unitDisplay;
protected:

	UNIT_TYPE unitType;
//	UNIT_STATUS status;
	void takeDamage(double damage);
	void attack(GameUnit * unit);
	static positionVector * anyUnitsOnBase(TeamBase * base, int team);
	positionVector* targetPosition;
private:
	
	const double STEP_SIZE_SCALING_CONSTANT = 10;
	const double RANGE_SCALING_CONSTANT = 10;
	const double ATTACK_DAMAGE_SCALING_CONSTANT = 2;
	const double HP_SCALING_CONSTANT = 100;
	const double SIZE_SCALING_CONSTANT = 70;
	
	
	const double MOVEMENT_HALT_THRESHOLD_SPACE_OF_SIZE_RATIO = 0.25;// how far units will stop away from each other (overlapping)

	const std::vector<double> UNIT_SPEED_RATIOS = { 0.3, 1, 0.7, 0.25, 0.1 };
	const std::vector<double> UNIT_RANGE_RATIOS = { 1, 1, 10, 12, 20 };
	const std::vector<double> UNIT_ATTACK_DAMAGE_RATIOS = { 0.1, 1, 0.4, 2, 10 };
	const std::vector<double> UNIT_HP_RATIOS = { 0.4, 1, 0.5, 0.25, 3 };
	const std::vector<double> UNIT_SIZE_RATIOS = { 0.8, 1, 0.9, 1.2, 3 };
	const std::vector<double> UNIT_HIRE_COST = { 70, 50, 70, 150, 500 };

	//double hireCost;
	double speed;
	double range; 
	double attackDamage;
	double hp;

	 void takeStep();



};

