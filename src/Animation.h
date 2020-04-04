#pragma once
#ifndef __ANIMATION__
#define __ANIMATION__
#include "Frame.h"
#include <vector>

struct Animation
{
	std::string name;
	std::vector<Frame> frames;
};

#endif /* defined (__ANIMATION__) */