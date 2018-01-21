#include "stdafx.h"
#include "Worker.h"




Worker::Worker(UNIT_TYPE type, TeamBase* base, positionVector* startPos, Image* unitDiplay)
{
	_Init(type, base, startPos, unitDiplay);
}

Worker::~Worker()
{
}
