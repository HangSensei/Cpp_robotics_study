#include "employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}
// Display Info
void Employee::displayInfo()
{
	cout << "Employee ID: " << this->m_Id
		<< "\tEmployee Name: " << this->m_Name
		<< "\tDepartment: " << this->getDeptName()
		<< "\tDuty: " << "Finish the daily assignment" << endl;
}
// Get Department Name
string Employee::getDeptName()
{
	return string("N_Employee");
}