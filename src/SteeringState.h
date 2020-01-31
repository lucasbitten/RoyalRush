#pragma once
#ifndef __STEERING_STATE__
#define __STEERING_STATE__

enum SteeringState {
	NO_STATE = -1,
	IDLE,
	SEEK,
	ARRIVE,
	AVOID,
	FLEE,
	NUM_OF_STATES
};

#endif /* defined (__STEERING_STATE__)*/