#pragma once
#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "DrunkOwnedStates.h"
#include "fsm/StateMachine.h"
#include <string>
#include <cassert>
#include <iostream>

template <class entity_type> class State;
struct Telegram;

const int BoredomLevel = 10;

class Drunk : public BaseGameEntity {
private:

	StateMachine<Drunk>*  m_pStateMachine;
	location_type         m_Location;

	int m_iBoredom;

public:
	Drunk(int id) : 
		m_Location(outside),
		m_iBoredom(0),
		BaseGameEntity(id)
	{
		m_pStateMachine = new StateMachine<Drunk>(this);
		m_pStateMachine->SetCurrentState(SePromener::Instance());
	}

	~Drunk() { delete m_pStateMachine; }

	void Update();

	virtual bool HandleMessage(const Telegram& msg);

	StateMachine<Drunk>* GetFSM()const { return m_pStateMachine; }

	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	void			  SetBoredom(int value);
	int				  GetBoredom() const { return m_iBoredom; }
	bool			  Bored() const { return m_iBoredom > BoredomLevel; }
};

