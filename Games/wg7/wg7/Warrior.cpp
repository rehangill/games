#include "stdafx.h"
#include "Warrior.h"




Warrior::Warrior(UNIT_TYPE type, TeamBase *base, positionVector* startPos, Image* unitDiplay)
{
	_Init(type, base, startPos, unitDiplay);

}

Warrior::~Warrior()
{
}
