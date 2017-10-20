#include "BanditsOwnedStates.h"
#include "fsm/State.h"
#include "Bandits.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include "Miner.h"
#include "EntityManager.h"

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
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
			"Sneaking to the gold mine, let's hope a nice prey shows up";
		pBandits->ChangeLocation(goldmine);
	}
}

void Ambush::Execute(Bandits* pBandits) {

	pBandits->IncreaseBoredom();
	pBandits->IncreaseFatigue();

	if (rand() % 4 + 1 == 1) pBandits->IncreaseDanger();

	if (pBandits->Endangered()) pBandits->GetFSM()->ChangeState(Flee::Instance());

	if (pBandits->PocketsFull()) pBandits->GetFSM()->ChangeState(VisitHideout::Instance());
	if (pBandits->Fatigued()) pBandits->GetFSM()->ChangeState(VisitHideout::Instance());

	if (pBandits->Bored()) pBandits->GetFSM()->ChangeState(Plunder::Instance());

}

void Ambush::Exit(Bandits* pBandits) {
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
		"Leaving Goldmine";
}

bool Ambush::OnMessage(Bandits* pBandits, const Telegram& msg) {
	switch (msg.Msg)
	{
	case Msg_BobLeavingMine:

		cout << "\nMessage handled by " << GetNameOfEntity(pBandits->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
			pBandits->ID(),
			ent_Miner_Bob,
			Msg_Ambush,
			NO_ADDITIONAL_INFO
			);

			pBandits->GetFSM()->ChangeState(RobAMiner::Instance());
			return true;
	}
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
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
			"Back to the hideout";

		pBandits->ChangeLocation(hideout);
	}
	pBandits->SetFatigue(0);
	pBandits->SetDanger(0);

	if (pBandits->LootsCarried() != 0)
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		pBandits->AddToWealth(pBandits->LootsCarried());
		pBandits->SetLootsCarried(0);
		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": "
			<< "Depositing gold. Total savings now: " << pBandits->Wealth();
	}	
}

void VisitHideout::Execute(Bandits * pBandits)
{
	if (!pBandits->Fatigued())
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": "
			<< "We're ready to go back to work";

		pBandits->GetFSM()->ChangeState(Ambush::Instance());
	}
	else
	{
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " << "ZZZZ... ";
	}
}

void VisitHideout::Exit(Bandits * pBandits)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
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
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
			"Let's raid this house and fill our pockets";

		pBandits->ChangeLocation(shack);
	}
}

void Plunder::Execute(Bandits * pBandits)
{
	pBandits->AddToLootsCarried(1);
	pBandits->DecreaseBoredom();
	pBandits->IncreaseFatigue();
	pBandits->IncreaseDanger();

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " << "We'll take that";
	if (pBandits->Fatigued()) pBandits->GetFSM()->ChangeState(Ambush::Instance());
	if (pBandits->PocketsFull()) pBandits->GetFSM()->ChangeState(Ambush::Instance());
	if (pBandits->Endangered()) pBandits->GetFSM()->ChangeState(Flee::Instance());
}

void Plunder::Exit(Bandits * pBandits)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
		"Leave the shack";
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

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
			"Save yourselves ! Run for your life !";
	}
}

void Flee::Execute(Bandits * pBandits)
{
	pBandits->DecreaseDanger();
	pBandits->IncreaseFatigue();

	if (!pBandits->Endangered()) pBandits->GetFSM()->ChangeState(Ambush::Instance());
}

void Flee::Exit(Bandits * pBandits)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

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
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	if (pBandits->Location() != goldmine) pBandits->ChangeLocation(goldmine);
	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " << 
		"Look at those pockets full of gold, what about we get rich ?";
}

void RobAMiner::Execute(Bandits * pBandits)
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " << "This is a robbery !";

	Miner* bob = static_cast<Miner*>(EntityManager::Instance()->GetEntityFromID(ent_Miner_Bob));

	pBandits->IncreaseFatigue();
	if (bob->GoldCarried() != 0)
	{
		pBandits->AddToLootsCarried(1);

		bob->SetGoldCarried(bob->GoldCarried() - 1);

		cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " << "Gimme that";
	}

	if (pBandits->Fatigued()) pBandits->GetFSM()->ChangeState(Ambush::Instance());
	if (pBandits->PocketsFull()) pBandits->GetFSM()->ChangeState(Ambush::Instance());
}

void RobAMiner::Exit(Bandits * pBandits)
{
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
		pBandits->ID(),
		ent_Miner_Bob,
		Msg_EndAmbush,
		NO_ADDITIONAL_INFO
	);

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	cout << "\n" << GetNameOfEntity(pBandits->ID()) << ": " <<
		"We shall leave";
}

bool RobAMiner::OnMessage(Bandits * pBandits, const Telegram & msg)
{
	switch (msg.Msg)
	{
	case Msg_SherifComing:
		cout << "\nMessage handled by " << GetNameOfEntity(pBandits->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBandits->ID())
			<< ": Damn it !";

		pBandits->GetFSM()->ChangeState(Flee::Instance());
		return true;
	}
	return false;
}
