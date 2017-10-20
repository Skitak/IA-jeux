#pragma once
#include "Vehicle.h"
class ControlledLeader :
	public Vehicle
{
public:
	ControlledLeader(GameWorld* world,
		Vector2D position,
		double    rotation,
		Vector2D velocity,
		double    mass,
		double    max_force,
		double    max_speed,
		double    max_turn_rate,
		double    scale);

	void Rotate(WPARAM direction);

	~ControlledLeader();
};

