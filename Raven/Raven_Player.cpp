#include "Raven_Player.h"
#include "Raven_SteeringBehaviors.h"
#include <iostream>


Raven_Player::Raven_Player(Raven_Game * world, Vector2D pos):Raven_Bot(world, pos)
{
	GetSteering()->WallAvoidanceOn();
	GetSteering()->SeekOn();
	m_vInputPosition = Vector2D(0, 0);
	m_iWeapon = 0;
}

Raven_Player::~Raven_Player()
{
}

void Raven_Player::MoveInput(WPARAM wparam, bool isInputPressed)
{
	switch (wparam)
	{
	case 'Z':
		m_up = isInputPressed;
		//m_vInputPosition.y += isInputReleased ? 1 : -1;
		break;
	case 'Q':
		m_left = isInputPressed;
		//m_vInputPosition.x += isInputReleased ? 1 : -1;
		break;
	case 'S':
		m_down = isInputPressed;
		//m_vInputPosition.y += isInputReleased ? -1 : 1;
		break;
	case 'D':
		m_right = isInputPressed;
		//m_vInputPosition.x += isInputReleased ? -1 : 1;
		break;
	default:
		break;
	}
}

void Raven_Player::Update()
{
	GetBrain();
	UpdateMovement();
	m_vInputPosition = Pos();
	m_vInputPosition.y -= m_up ? 100 : 0;
	m_vInputPosition.y += m_down ? 100 : 0;
	m_vInputPosition.x += m_right ? 100 : 0;
	m_vInputPosition.x -= m_left ? 100 : 0;

	std::cout << m_vInputPosition.x << " " << m_vInputPosition.y << std::endl;
	//Vector2D futurPosition = Vector2D(Pos().x + m_vInputPosition.x, Pos().y + m_vInputPosition.y);
	GetSteering()->SetTarget(m_vInputPosition);
}

void Raven_Player::Spawn(Vector2D pos) {
	Raven_Bot::Spawn(pos);
}

void Raven_Player::SetWeapon(unsigned int weapon) {
	m_iWeapon = weapon;
	ChangeWeapon(weapon);
}
