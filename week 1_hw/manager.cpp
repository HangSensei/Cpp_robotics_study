#include "manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
void Manager::displayInfo()
{
	cout << "Employee ID: " << this->m_Id
		<< "\tEmployee Name: " << this->m_Name
		<< "\tDepartment: " << this->getDeptName()
		<< "\tDuty: " << "Assign work to employee" << endl;
}
string Manager::getDeptName()
{
	return string("Manager");
}