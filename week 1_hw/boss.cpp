#include "boss.h"

Boss::Boss(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
void Boss::displayInfo()
{
	cout << "Employee ID: " << this->m_Id
		<< "\tEmployee Name: " << this->m_Name
		<< "\tDepartment: " << this->getDeptName()
		<< "\tDuty: " << "Make Major Decisions" << endl;
}
string Boss::getDeptName()
{
	return string("Boss");
}