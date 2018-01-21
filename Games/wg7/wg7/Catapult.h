#pragma once
#include "GameUnit.h"
class Catapult :
	public GameUnit
{
public:
	Catapult(UNIT_TYPE type, TeamBase *base, positionVector* startPos);

	Catapult(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);

	~Catapult();
};

