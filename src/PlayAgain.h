#pragma once
#ifndef __PLAY_AGAIN__

#define __PLAY_AGAIN__

#include "Button.h"

class PlayAgain : public Button
{
public:
	PlayAgain();
	~PlayAgain();


	bool ButtonClick() override;
private:
	bool m_isClicked;
};
#endif
