#include "Follower.h"
#include "SteeringBehaviors.h"



Follower::Follower(GameWorld* world,
	Vector2D  position,
	double    rotation,
	Vector2D  velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale,
	Vector2D  offset) :Vehicle(world,
		position,
		rotation,
		velocity,
		mass,
		max_force,
		max_speed,
		max_turn_rate,
		scale)
{

}


Follower::~Follower()
{
}

void SetLeader(Vehicle* _leader)
{
	m_pSteering->OffsetPursuitOn(_leader, offset);
}