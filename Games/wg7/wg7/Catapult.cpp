#include "stdafx.h"
#include "Catapult.h"



Catapult::Catapult(UNIT_TYPE type, TeamBase *base, positionVector* startPos, Image* unitDiplay)
{
	_Init( type,   base,   startPos, unitDiplay);
}

Catapult::~Catapult()
{
}
