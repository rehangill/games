#include "stdafx.h"
#include "Mage.h"



Mage::Mage(UNIT_TYPE type, TeamBase *base, positionVector *startPos, Image* unitDiplay)
{
	_Init(type, base, startPos, unitDiplay);
}

Mage::~Mage()
{
}
