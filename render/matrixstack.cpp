#include "pch.h"
#include "matrixstack.h"


ZMatrixStack::ZMatrixStack()
	: stack(ZStack<ZMatrix>(100))
{
}


ZMatrixStack::~ZMatrixStack(void)
{
}