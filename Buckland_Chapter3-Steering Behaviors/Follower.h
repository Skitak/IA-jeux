#pragma once
#include "Vehicle.h"
class Follower :
	public Vehicle
{
private:
	//Vehicle leader;
	Vector2D offset;
public:
	Follower(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);
	~Follower();

	//void SetLeader(Vehicle _leader) { leader = _leader; };
	void SetOffset(Vector2D _offset) { offset = _offset; };
};

