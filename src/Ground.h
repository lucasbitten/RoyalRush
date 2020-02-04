#pragma once
#ifndef  __Ground__
#define __Ground__

#include  "GameObject.h"

class Ground : public GameObject
{
public:

	Ground();
	~Ground();

	void draw() override;
	void update() override;
	void clean() override;

	bool playerColliding;
	
};



#endif
