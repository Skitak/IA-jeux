#include "Drunk.h"

bool Drunk::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Drunk::Update()
{
	SetTextColor( 0x0005 | FOREGROUND_INTENSITY);

	m_iBoredom += 1;

	m_pStateMachine->Update();
}

void Drunk::SetBoredom(int value) {

	if (value < 0)
		return;
	m_iBoredom = value;
}