#pragma once
#include "GameUnit.h"
class Mage :
	public GameUnit
{
public:
	Mage(UNIT_TYPE type, TeamBase *base, positionVector* startPos);

	Mage(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);

	~Mage();
};

