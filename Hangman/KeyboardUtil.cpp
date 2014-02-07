#include "KeyboardUtil.h"


KeyboardUtil::KeyboardUtil(void)
{
}


KeyboardUtil::~KeyboardUtil(void)
{
}

char KeyboardUtil::convertKeyCodeToChar(int code)
{
	return (char)(code+65);
}
