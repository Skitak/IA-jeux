
#include "triggers\Trigger_WeaponGiver.h"
#include "Raven_bot.h"
#include "Raven_Map.h"
class Trigger_WeaponGiverTeam
{
private : 
	Vector2D position;
	Raven_Bot::Team team;
	std::vector<Trigger_WeaponGiver*> weapons;
public:
	Trigger_WeaponGiverTeam( Vector2D pos, Raven_Bot::Team team, Raven_Map* map);
	~Trigger_WeaponGiverTeam();

	Raven_Bot::Team GetTeam() { return team; }
};
