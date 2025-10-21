#include "EmployeeManSys.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

int main()
{
	//polymorphism testing
	/*Worker* worker = nullptr;
	worker = new Employee(1, "zhangsan", 1);
	worker->displayInfo();
	delete worker;
	worker = new Manager(2, "lisi", 2);
	worker->displayInfo();
	delete worker;

	worker = new Boss(0, "wangwu", 0);
	worker->displayInfo();
	delete worker;*/

	EmployeeManagementSys ems;
	
	int choice = 0;
	while (1)
	{
		ems.Display_Menu();
		cout << "Please Enter Your Choice: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 0 : // Exit Management Program
			ems.ExitSystem();
			break;
		case 1:  // Add Employee Info
			ems.Add_Emp();
			break;
		case 2:	 // Display Employee Info
			ems.display_Emp();
			break;
		case 3:  // Delete Employee Info
			ems.del_Emp();
			break;
		case 4:  // Edit Employee Info
			ems.mod_Emp();
			break;
		case 5:  // Find Employee Info  
			ems.find_Emp();
			break;
		case 6:  // Sort Employee ID
			ems.sort_Emp();
			break;
		case 7:  // Empty the Info Doc
			ems.clean_File();
			break;
		default:
			system("cls"); // clear screen
			break;
		}
	}

	return 0;
}