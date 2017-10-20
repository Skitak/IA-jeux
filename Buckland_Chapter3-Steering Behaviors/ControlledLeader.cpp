#include "ControlledLeader.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"


ControlledLeader::ControlledLeader(GameWorld* world,
	Vector2D position,
	double    rotation,
	Vector2D velocity,
	double    mass,
	double    max_force,
	double    max_speed,
	double    max_turn_rate,
	double    scale) :Vehicle(world,
		position,
		rotation,
		velocity,
		mass,
		max_force,
		max_speed,
		max_turn_rate,
		scale)
{
	SetScale(Vector2D(10, 10));
	m_pSteering->SeekOn();
	m_pSteering->GoForwardOn();
	SetMaxSpeed(150);
}

void ControlledLeader::Rotate(WPARAM direction)
{
	// ControlledLeader creation
	ControlledLeader* pControlledLeader = new ControlledLeader(this,
		Vector2D(0, 0),            //initial position
		RandFloat()*TwoPi,        //start rotation
		Vector2D(0, 0),           //velocity
		Prm.VehicleMass,          //mass
		Prm.MaxSteeringForce,     //max force
		Prm.MaxSpeed,             //max velocity
		Prm.MaxTurnRatePerSecond, //max turn rate
		Prm.VehicleScale);
	switch (direction)
	{
	case VK_LEFT:
		Vec2DRotateAroundOrigin(Heading(),pi/8.0);
		break;
	case VK_RIGHT:
		Vec2DRotateAroundOrigin(Heading(), -pi / 8.0);
		break;
	default:
		break;
	}
}

ControlledLeader::~ControlledLeader()
{
}
