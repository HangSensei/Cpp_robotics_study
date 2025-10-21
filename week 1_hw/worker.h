#pragma once
#include <iostream>
#include <string>
using namespace std;

//worker abstract class

class Worker
{
public:
	virtual ~Worker() = default;
	// Display Info
	virtual void displayInfo() = 0;
	// Get Department Name
	virtual string getDeptName() = 0;
	// ID
	int m_Id;
	// Name
	string m_Name;
	// Department
	int m_DeptId;
};

