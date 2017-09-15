#include "Bandits.h"

bool Bandits::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}


void Bandits::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_iFatigue += 1;
	m_iBoredom += 1;

	if (rand() % 2 + 1 == 1) m_iDanger++;

	m_pStateMachine->Update();
}

void Bandits::AddToLootsCarried(int val) 
{
	m_iLootsCarried += val;

	if (m_iLootsCarried < 0) m_iLootsCarried = 0;
}

void Bandits::AddToWealth(int val) {
	m_iMoneyInHideout += val;

	if (m_iMoneyInHideout < 0) m_iMoneyInHideout = 0;
}

bool Bandits::Fatigued()const
{
	if (m_iFatigue > TirednessThreshold)
	{
		return true;
	}

	return false;
}



