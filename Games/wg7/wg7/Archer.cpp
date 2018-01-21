#include "stdafx.h"
#include "Archer.h"
#include "Image.h"



Archer::Archer(UNIT_TYPE type, TeamBase* base, positionVector* startPos, Image* unitDiplay)
{
	_Init(type, base, startPos, unitDiplay);
}

Archer::~Archer()
{
}
