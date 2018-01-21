#pragma once
#include "GameUnit.h"
class Worker :
	public GameUnit
{
public:
	Worker(UNIT_TYPE type, TeamBase* base, positionVector *startPos);

	Worker(UNIT_TYPE type, TeamBase * base, positionVector * startPos, Image * unitDiplay);

	~Worker();
};

