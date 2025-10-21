#pragma once
#include <iostream>
#include "worker.h"
using namespace std;

class Employee : public Worker
{
public:
	Employee(int id, string name, int did);
	// Display Info
	virtual void displayInfo();
	// Get Department Name
	virtual string getDeptName();
};