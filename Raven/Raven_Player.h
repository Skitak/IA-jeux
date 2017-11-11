#pragma once
#include "Raven_Bot.h"
#include <vector>
#include <iosfwd>
#include <map>

class Raven_Player :
	public Raven_Bot
{
private :
	Vector2D m_vInputPosition;
	bool m_left, m_right, m_up, m_down;

public:

	Raven_Player(Raven_Game* world, Vector2D pos);
	virtual ~Raven_Player();

	void MoveInput(WPARAM wparam, bool isInputReleased);
	void Update();
};

