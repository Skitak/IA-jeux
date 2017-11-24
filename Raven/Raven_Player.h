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
	unsigned int m_iWeapon;
	bool m_left = false, m_right = false, m_up = false, m_down = false;

public:

	Raven_Player(Raven_Game* world, Vector2D pos);
	virtual ~Raven_Player();

	void MoveInput(WPARAM wparam, bool isInputReleased);
	void Update();
	void Spawn(Vector2D pos);
	void SetWeapon(unsigned int weapon);
	unsigned int GetWeapon() { return m_iWeapon; }
};

