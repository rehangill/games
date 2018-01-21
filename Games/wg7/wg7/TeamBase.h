#pragma once

#include "Image.h"
#include <vector>

class TeamBase
{
public:




	TeamBase(int team, Image * baseImage, double baseHealth);

	void takeDamage(double damage);

	void destroy();


	void initiateIncome(long bankAllowanceSpeed, int increment);

	~TeamBase();

	static std::vector<TeamBase*> getAllBases();


	bool destroyed = false;

	int gold;
	int team;
	double hp;
	
	const std::vector<double> UNIT_HIRE_COST = { 70, 50, 70, 150, 500 };
	const double STARTING_GOLD = 500;

	 Image * baseImage;
	  double totalHp;
};

