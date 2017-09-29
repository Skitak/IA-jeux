#include "Bandits.h"

bool Bandits::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Bandits::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

void Bandits::AddToLootsCarried(int val) 
{
	m_iLootsCarried += val;

	if (m_iLootsCarried < 0) m_iLootsCarried = 0;
}

void Bandits::AddToWealth(int val) {
	if (m_iMoneyInHideout < 0) m_iMoneyInHideout = 0;
	m_iMoneyInHideout += val;
}

bool Bandits::Endangered() const
{
	if (m_iDanger >= BanditsDangerThreshold) return true;

	return false;
}

bool Bandits::Bored() const
{
	if (m_iBoredom >= BanditsBoredomThreshold) return true;

	return false;
}

bool Bandits::Fatigued()const
{
	if (m_iFatigue > BanditsTirednessThreshold)
	{
		return true;
	}

	return false;
}



