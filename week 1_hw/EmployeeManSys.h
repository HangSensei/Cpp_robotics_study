#pragma once
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;

class EmployeeManagementSys
{
public:

	EmployeeManagementSys();//Constructor declaration
	~EmployeeManagementSys();//Destructor declaration

	void Display_Menu();
	void ExitSystem();

	//current employee number
	int m_EmpNum;

	//worker array pointers
	Worker** m_EmpArray;

	//add worker
	void Add_Emp();

	//save file
	void save();

	// if file is empty
	bool m_FileIsEmpty;

	//get the total num of employees
	int get_EmpNum();

	//employee initialization
	void init_Emp();

	//display employee info
	void display_Emp();

	//delete employee info
	void del_Emp();

	//justify if the employee is exist, if exist, return position, if not return -1
	int isExist(int id);

	//edit employee info
	void mod_Emp();

	//find employee
	void find_Emp();

	//sort
	void sort_Emp();

	//empty file / data
	void clean_File();



};