#include "Raven_Player.h"


Raven_Player::Raven_Player(Raven_Game * world, Vector2D pos):Raven_Bot(world, pos)
{
	//GetSteering()->WallAvoidanceOn();
	//GetSteering()->SeekOn();
}

Raven_Player::~Raven_Player()
{
}

void Raven_Player::MoveInput(WPARAM wparam, bool isInputReleased)
{
	switch (wparam)
	{
	case 'w':
		m_vInputPosition.y += isInputReleased ? -1 : 1;
		break;
	case 'a':
		m_vInputPosition.x += isInputReleased ? 1 : -1;
		break;
	case 's':
		m_vInputPosition.y += isInputReleased ? 1 : -1;
		break;
	case 'd':
		m_vInputPosition.x += isInputReleased ? -1 : 1;
		break;
	default:
		break;
	}
}

void Raven_Player::Update()
{
base:Update();
	GetBrain();
	UpdateMovement();
	Vector2D futurPosition = Vector2D(Pos().x + m_vInputPosition.x, Pos().y + m_vInputPosition.y);
	//m_pSteering->SetTarget(futurPosition);
}
