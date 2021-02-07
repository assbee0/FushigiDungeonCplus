#pragma once

class AIState
{
public:
	AIState(class AIComponent* component);
	virtual void Update();
	virtual void OnEnter();
	virtual void OnExit();

	virtual const char* GetName() const = 0;

protected:
	class AIComponent* mComponent;

};

class AIIdle : public AIState
{
public:
	AIIdle(class AIComponent* component);
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Idle"; }
};

class AIWander : public AIState
{
public:
	AIWander(class AIComponent* component);
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Wander"; }
};

class AIChase : public AIState
{
public:
	AIChase(class AIComponent* component);
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Chase"; }
};

class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* component);
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Attack"; }
};

class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* component);
	void Update() override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Death"; }
};