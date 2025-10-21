#pragma once
#include "worker.h"
// Manager class
class Manager : public Worker
{
public:

	Manager(int id, string name, int did);
	virtual void displayInfo();
	virtual string getDeptName();
};