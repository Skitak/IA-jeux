#pragma once
#include "Vehicle.h"
class Follower :
	public Vehicle
{
private:
	Vehicle* leader;
	Vector2D v_offset;
public:
	Follower(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale,
		Vector2D  offset);
	~Follower();

	void SetLeader(Vehicle* _leader);
};

