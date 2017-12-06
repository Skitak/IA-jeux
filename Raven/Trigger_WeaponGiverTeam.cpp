#include "trigger_WeaponGiverTeam.h"
#include "debug/DebugConsole.h"



Trigger_WeaponGiverTeam::Trigger_WeaponGiverTeam(Vector2D pos, Raven_Bot::Team team, Raven_Map* map)
{
	this->position = pos;
	this->team = team;
	int numberOfWeapons = 3, startingWeaponEntityType = 7;
	for (int i = 0; i < numberOfWeapons; ++i) {
		weapons.push_back(new Trigger_WeaponGiver(pos, team));
		map->AddWeapon_Giver(weapons.at(i), i + startingWeaponEntityType);
	}
}


Trigger_WeaponGiverTeam::~Trigger_WeaponGiverTeam()
{
	Trigger_WeaponGiver* trigger;
	while (!weapons.empty()) {
		trigger = weapons.back();
		//delete trigger;
		weapons.pop_back();
	}
}