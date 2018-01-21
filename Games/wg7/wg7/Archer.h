#pragma once
#include "GameUnit.h"
class Archer :
	public GameUnit
{
public:
	Archer(UNIT_TYPE type, TeamBase* base, positionVector* startPos);
	Archer(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);
	~Archer();
};

