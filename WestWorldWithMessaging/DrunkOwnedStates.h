#pragma once
#include "fsm/State.h"

class Drunk;
struct Telegram;


class SePromener : public State<Drunk> {

private:

	SePromener();
	SePromener(const SePromener&);
	SePromener& operator=(const SePromener&);

public:
	static SePromener* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

class EtancherSoif : public State<Drunk> {

private:

	EtancherSoif();
	EtancherSoif(const EtancherSoif&);
	EtancherSoif& operator=(const EtancherSoif&);

public:
	static EtancherSoif* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

class SeBattre : public State<Drunk> {

private:

	SeBattre();
	SeBattre(const SeBattre&);
	SeBattre& operator=(const SeBattre&);

public:
	static SeBattre* Instance();
	virtual void Enter(Drunk* drunk);
	virtual void Execute(Drunk* drunk);
	virtual void Exit(Drunk* drunk);
	virtual bool OnMessage(Drunk* agent, const Telegram& msg);

};

