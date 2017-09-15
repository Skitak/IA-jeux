#ifndef BANDIT_H
#define BANDIT_H
//------------------------------------------------------------------------
//
//  Name:   Bandits.h
//
//  Desc:   A class defining bandits.
//
//------------------------------------------------------------------------


#include <string>
#include <cassert>
#include <iostream>
#include <stdlib.h>    
#include <time.h>      

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "BanditsOwnedStates.h"
#include "fsm/StateMachine.h"


template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

//the amount of loots bandits must have before they feel can go home
const int LootLevel = 10;
//the amount of nuggets a miner can carry
const int MaxLoots = 5;
//above this value bandits are sleepy
const int TirednessThreshold = 10;
//above this value bandits are fleeing
const int DangerThreshold = 5;
//the threshold of boredom for bandits
const int BoredomThreshold = 5;

class Bandits : public BaseGameEntity
{
private:
	//an instance of the state machine class
	StateMachine<Bandits>*  m_pStateMachine;

	location_type			m_Location;

	//how many loots the bandits are carrying
	int						m_iLootsCarried;

	int						m_iMoneyInHideout;
	//the higher the value, the more tired the bandits
	int						m_iFatigue;

	int						m_iDanger;

	int						m_iBoredom;


public:
	Bandits(int id) :m_Location(hideout),
		m_iLootsCarried(0),
		m_iFatigue(0),
		m_iDanger(0),
		BaseGameEntity(id)
	{
		//set up state machine
		m_pStateMachine = new StateMachine<Bandits>(this);

		m_pStateMachine->SetCurrentState(GoToHideoutAndSleepTillRested::Instance());
	}

	~Bandits() { delete m_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Bandits>* GetFSM()const { return m_pStateMachine; }
	
	
	//-------------------------------------------------------------accessors
	location_type Location()const { return m_Location; }
	void          ChangeLocation(location_type loc) { m_Location = loc; }

	int           LootsCarried()const { return m_iLootsCarried; }
	void          SetLootsCarried(int val) { m_iLootsCarried = val; }
	void          AddToLootsCarried(int val);
	bool          PocketsFull()const { return m_iLootsCarried >= MaxLoots; }

	bool          Fatigued()const;
	void          DecreaseFatigue() { m_iFatigue -= 1; }
	void          IncreaseFatigue() { m_iFatigue += 1; }

	int           Wealth()const { return m_iMoneyInHideout; }
	void          SetWealth(int val) { m_iMoneyInHideout = val; }
	void          AddToWealth(int val);

	int			  Danger()const { return m_iDanger; }
	void		  SetDanger(int val) { m_iDanger = val; }
	void		  DecreaseDanger() { m_iDanger -= 1; }

	int			  Boredom()const { return m_iBoredom; }
	void		  SetBoredom(int val) { m_iBoredom = val; };
	void		  IncreaseBoredom() { m_iBoredom += 1; }
	void		  DecreaseBoredom() { m_iBoredom -= 1; }
};

#endif