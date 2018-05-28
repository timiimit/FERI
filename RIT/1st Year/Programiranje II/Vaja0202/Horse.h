#pragma once

class Horse
{
private:
	bool canRun;
	float speed;
	char* name;

public:
	Horse();
	~Horse();

	bool GetCanRun() const;
	void SetCanRun(bool canRun);

	float GetSpeed() const;
	void SetSpeed(float speed);

	const char* GetName() const;
	void SetName(const char* name);
};

