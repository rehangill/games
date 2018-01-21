#pragma once
#include "GameUnit.h"
class Warrior :
	public GameUnit
{
public:
	Warrior(UNIT_TYPE type, TeamBase *base, positionVector *startPos);

	Warrior(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);

	~Warrior();
};

