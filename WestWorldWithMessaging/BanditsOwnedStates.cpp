#include "BanditsOwnedStates.h"
#include "fsm/State.h"
#include "Bandits.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------------------------------------------------Methods for Ambush
Ambush* Ambush::Instance()
{
	static Ambush instance;

	return &instance;
}


void Ambush::Enter(Bandits* pBandits) {
	//if the bandits are not already located at the ambush site, they must
	//change location to the gold mine.
	if (pBandits->Location() != goldmine)
	{
		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ":" <<
			"Sneaking to the gold mine, let's hope a nice prey shows up";
		pBandits->ChangeLocation(goldmine);
	}
}

void Ambush::Execute(Bandits* pBandits) {

}

void Ambush::Exit(Bandits* pBandits) {
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ":" <<
		"We better get out from this place";
}

bool Ambush::OnMessage(Bandits* pBandits, const Telegram& msg) {
	return false;
}

//------------------------------------------------------------------------Methods for VisitHideout

VisitHideout * VisitHideout::Instance()
{
	static VisitHideout instance;

	return &instance;
}

void VisitHideout::Enter(Bandits * pBandits)
{
	if (pBandits->Location() != hideout)
	{
		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ":" <<
			"Let's go back to the hideout";

		pBandits->ChangeLocation(hideout);
	}
}

void VisitHideout::Execute(Bandits * pBandits)
{
}

void VisitHideout::Exit(Bandits * pBandits)
{
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ":" <<
		"Bye bye home sweet home";
}

bool VisitHideout::OnMessage(Bandits * pBandits, const Telegram & msg)
{
	return false;
}

//------------------------------------------------------------------------Methods for Plunder

Plunder * Plunder::Instance()
{
	static Plunder instance;

	return &instance;
}

void Plunder::Enter(Bandits * pBandits)
{
	if (pBandits->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
			"Let's raid this house and fill our pockets";

		pBandits->ChangeLocation(shack);
	}
}

void Plunder::Execute(Bandits * pBandits)
{
	
}

void Plunder::Exit(Bandits * pBandits)
{
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
		"Hurry ! We gotta leave";
}

bool Plunder::OnMessage(Bandits * pBandits, const Telegram & msg)
{
	return false;
}

//------------------------------------------------------------------------Methods for Flee
Flee* Flee::Instance()
{
	static Flee instance;

	return &instance;
}

void Flee::Enter(Bandits * pBandits)
{
	if (pBandits->Location() != outside)
	{
		pBandits->ChangeLocation(outside);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
			"Save yourselves ! Run for your life !";
	}
}

void Flee::Execute(Bandits * pBandits)
{
}

void Flee::Exit(Bandits * pBandits)
{
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
		"Looks like we'll get away with it... Now, Back to work !";
}

bool Flee::OnMessage(Bandits * pBandits, const Telegram & msg)
{
	return false;
}

//------------------------------------------------------------------------Methods for RobAMiner

RobAMiner * RobAMiner::Instance()
{
	static RobAMiner instance;

	return &instance;
}

void RobAMiner::Enter(Bandits * pBandits)
{
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " << 
		"Look at those pockets full of gold, what about we get rich ?";
}

void RobAMiner::Execute(Bandits * pBandits)
{
}

void RobAMiner::Exit(Bandits * pBandits)
{
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
		"We shall leave";
}

bool RobAMiner::OnMessage(Bandits * pBandits, const Telegram & msg)
{
	return false;
}
