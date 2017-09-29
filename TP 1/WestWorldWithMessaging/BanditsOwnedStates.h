#ifndef BANDITS_OWNED_STATES_H
#define BANDITS_OWNED_STATES_H

//------------------------------------------------------------------------
//
//  Name:   BanditsOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Bandits class.
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Bandits;
struct Telegram;

//------------------------------------------------------------------------
// In this state the bandits will walk to the goldmine and wait for a prey
// If they already have gold or they are tired, they'll go to their 
// hideout. If no one is coming then they'll plunder a house.
//------------------------------------------------------------------------
class Ambush : public State<Bandits>
{
private:
	Ambush() {}

	Ambush(const Ambush&);
	Ambush& operator=(const Ambush&);

public:
	static Ambush* Instance();

	virtual void Enter(Bandits* bandits);

	virtual void Execute(Bandits* bandits);

	virtual void Exit(Bandits* bandits);

	virtual bool OnMessage(Bandits* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
// Bandits will go to the hideout and stash their loots. Then they'll rest
// until they are no longer tired.
//------------------------------------------------------------------------
class VisitHideout :public State<Bandits>
{
private:
	VisitHideout(){}

	VisitHideout(const VisitHideout&);
	VisitHideout& operator=(const VisitHideout&);

public:
	static VisitHideout* Instance();

	virtual void Enter(Bandits* bandits);

	virtual void Execute(Bandits* bandits);

	virtual void Exit(Bandits* bandits);

	virtual bool OnMessage(Bandits* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
// Bandits will go to Bob's House to plunder it. If the sherif comes then
// they leave the place with what they could take.
//------------------------------------------------------------------------
class Plunder : public State<Bandits>
{
private:
	Plunder(){}

	Plunder(const Plunder&);
	Plunder& operator=(const Plunder&);

public:
	static Plunder* Instance();

	virtual void Enter(Bandits* bandits);

	virtual void Execute(Bandits* bandits);

	virtual void Exit(Bandits* bandits);

	virtual bool OnMessage(Bandits* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
// Bandits rob the victim coming out of the mine. If the sherif comes then
// they leave the place without taking anything. Else, they take as much
// as they can and leave.
//------------------------------------------------------------------------
class RobAMiner : public State<Bandits>
{
private:
	RobAMiner(){}

	RobAMiner(const RobAMiner&);
	RobAMiner& operator=(const RobAMiner&);

public:
	static RobAMiner* Instance();

	virtual void Enter(Bandits* bandits);

	virtual void Execute(Bandits* bandits);

	virtual void Exit(Bandits* bandits);

	virtual bool OnMessage(Bandits* agent, const Telegram& msg);
};

//------------------------------------------------------------------------
// Bandits are fleeing from the Sherif. Once the danger level is low
// they'll go back to the mine waiting for another victim.
//------------------------------------------------------------------------
class Flee : public State<Bandits>
{
private:
	Flee(){}

	Flee(const Flee&);
	Flee& operator=(const Flee&);

public : 
	static Flee* Instance();

	virtual void Enter(Bandits* bandits);

	virtual void Execute(Bandits* bandits);

	virtual void Exit(Bandits* bandits);

	virtual bool OnMessage(Bandits* agent, const Telegram& msg);
};


#endif