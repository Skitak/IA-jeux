#include "DrunkOwnedStates.h"
#include "fsm/State.h"
#include "Drunk.h"
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

SePromener* SePromener::Instance() {

	static SePromener instance;

	return &instance;
}

void SePromener::Enter(Drunk* drunk) {
	drunk->ChangeLocation(outside);
}

void SePromener::Execute(Drunk* drunk) {
	drunk->SetBoredom(drunk->GetBoredom() + 1);

	if (drunk->Bored()) {
		drunk->GetFSM()->ChangeState(EtancherSoif::Instance());
	}
}

void SePromener::Exit(Drunk* drunk) {
}

bool SePromener::OnMessage(Drunk* agent, const Telegram& msg) {
	return false;
}

EtancherSoif* EtancherSoif::Instance() {

	static EtancherSoif instance;
	return &instance;
}

void EtancherSoif::Enter(Drunk* drunk) {
	cout << "\n" << "Hi y'all! Gimme dat bottle of oll' fine Scotch!";
	drunk->ChangeLocation(saloon);
}

void EtancherSoif::Execute(Drunk* drunk) {
	drunk->SetBoredom(drunk->GetBoredom() - 1);

	if (drunk->GetBoredom() == 0)
		drunk->GetFSM()->ChangeState(SePromener::Instance());

	Miner* bob = static_cast<Miner*>( ( EntityManager::Instance()->GetEntityFromID(ent_Billy) );
	if (bob->Location() == saloon) {
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			drunk->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_Fight,   //the message
			NO_ADDITIONAL_INFO);
		drunk->GetFSM()->ChangeState(SeBattre::Instance());
	}

}

void EtancherSoif::Exit(Drunk* drunk) {
}

bool EtancherSoif::OnMessage(Drunk* drunk, const Telegram& msg) {
	return false;
}

SeBattre* SeBattre::Instance() {

	static SeBattre instance;
	return &instance;
}



void SeBattre::Enter(Drunk* drunk) {
	cout << "Y u lookin' at me you old birch? Imma beat the hell outta you!";
}

void SeBattre::Execute(Drunk* drunk) {
	cout << "humph, you fight like an old man!";

}

void SeBattre::Exit(Drunk* drunk) {
	drunk->GetFSM()->ChangeState(SePromener::Instance());
	cout << "I'm outta here, I'm gonna be walkin' for a while";
}

bool SeBattre::OnMessage(Drunk* drunk, const Telegram& msg) {
	return false;
}