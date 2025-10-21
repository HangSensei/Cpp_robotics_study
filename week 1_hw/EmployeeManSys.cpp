#include "EmployeeManSys.h"

EmployeeManagementSys::EmployeeManagementSys()//Constructor implementation
{
	//1. file does not exist
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //read file
	if (!ifs.is_open())
	{
		cout << "File doesn't exist" << endl;
		//initialization
		//initialize employee number
		this->m_EmpNum = 0;
		//initialize array pointer
		this->m_EmpArray = nullptr;
		//if file is empty(default true)
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2. file exist, no content
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//file is empty
		cout << "File is Empty" << endl;
		//initialization
		//initialize employee number
		this->m_EmpNum = 0;
		//initialize array pointer
		this->m_EmpArray = nullptr;
		//if file is empty(default true)
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//3. file exist, have content
	int num = this->get_EmpNum();
	cout << "The Employee Num is: " << num << endl;
	this->m_EmpNum = num;
	//malloc new pointers arr
	this->m_EmpArray = new Worker* [this->m_EmpNum];
	// read the file and put content into the arr
	this->init_Emp();
}


EmployeeManagementSys::~EmployeeManagementSys()//Destructor implementation
{
	if (this->m_EmpArray != nullptr)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != nullptr) 
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}
}

void EmployeeManagementSys::Display_Menu()
{
	cout << "***********************************************************************" << endl;
	cout << "*******      Welcome Using Employee Management System!         ********" << endl;
	cout << "***************   0. Exit Management Program    ***********************" << endl;
	cout << "***************   1. Add Employee Info          ***********************" << endl;
	cout << "***************   2. Display Employee Info      ***********************" << endl;
	cout << "***************   3. Delete Employee Info       ***********************" << endl;
	cout << "***************   4. Edit Employee Info         ***********************" << endl;
	cout << "***************   5. Find Employee Info         ***********************" << endl;
	cout << "***************   6. Sort Employee ID           ***********************" << endl;
	cout << "***************   7. Empty the Info Doc         ***********************" << endl;
	cout << "***********************************************************************" << endl;
	cout << endl;
}

void EmployeeManagementSys::ExitSystem()
{
	cout << "System Exit Successfully" << endl;
	system("pause");
	exit(0);// exit program
}

void EmployeeManagementSys::Add_Emp()
{
	cout << "Please Enter the Number of Employees You Want to Add: " << endl;
	int addNum = 0;
	cin >> addNum;
	
	if (addNum > 0)
	{
		//newSpace employee num
		int newSize = this->m_EmpNum + addNum;
		//allocate new space (new pointer array)
		Worker** newSpace = new Worker*[newSize];

		//shallow copy the origional Worker* pointers to new pointer arr
		if (this->m_EmpArray != nullptr)// despite the first time add, doing shallow copy
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				// shallow copy the pointer to new pointer array
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "Please Enter the ID for NO." << i + 1 << " New Employee" << endl;
			cin >> id;
			//printf("\n");

			cout << "Please Enter the Name for NO." << i + 1 << " New Employee" << endl;
			cin >> name;

			cout << "Please Select the Position for This New Employee" << endl;
			cout << "1. Normal Employee" << endl;
			cout << "2. Manager" << endl;
			cout << "3. Boss" << endl;
			cin >> dSelect;
			// base pointer
			Worker* worker = nullptr;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//Store the pointer of the newly created employee object in the "new part" of the new array.
			newSpace[this->m_EmpNum + i] = worker;

		}
		// release origional space
		delete[] this->m_EmpArray;
		// update new space 
		this->m_EmpArray = newSpace;
		// update new employee number
		this->m_EmpNum = newSize;

		//update file is not empty
		this->m_FileIsEmpty = false;
		// successful add notice
		cout << addNum << " Employees Add Successfully" << endl;
		// save data to file
		this->save();
	}
	else
	{
		cout << "Invalid Input, Please Try Again" << endl;
	}

	system("pause");
	system("cls");
}

void EmployeeManagementSys::save()
{
	ofstream ofs;
	// open file with output mode (write)
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	// close file
	ofs.close();
}

int EmployeeManagementSys::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//open file, read
	int id;
	string name;
	int did;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//update num of employee each read
		num++;
	}
	return num;
}

void EmployeeManagementSys::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;
	int i = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = nullptr;

		if (did == 1)
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)
		{
			worker = new Manager(id, name, did);
		}
		else
		{
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[i] = worker;
		i++;
	}
	ifs.close();
}

void EmployeeManagementSys::display_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "NO Info in File or File Does Not Exist" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//polymophism, using different object in arr
			this->m_EmpArray[i]->displayInfo();
		}
	}
	//
	system("pause");
	system("cls");
}

void EmployeeManagementSys::del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "NO Info in File or File Does Not Exist" << endl;
	}
	else
	{
		//delete employee based on ID
		cout << "Please Enter the ID for Deleting" << endl;
		int id = 0;
		cin >> id;
		//justify if the employee exist
		int index = this->isExist(id);
		//indicate the delete postion in pointer array
		if (index != -1)
		{
			//[i] [i+1] [EmpNum]
			for (int i = index; i < this->m_EmpNum - 1; i++) 
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//update emp num
			//save data to file
			this->save();
			cout << "Successfully Delete" << endl;
		}
		else
		{
			cout << "No Relevant Data Found" << endl;
		}
	}
	system("pause");
	system("cls");
}
int EmployeeManagementSys::isExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}	
	}
	return index;
}

void EmployeeManagementSys::mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "NO Info in File or File Does Not Exist" << endl;
	}
	else
	{
		cout << "Please Enter the ID for Employee Info Need Adjust" << endl;
		int id;
		cin >> id;

		int ret = this->isExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "Employee ID: " << id << " Exist" << ", Please Enter New ID" << endl;
			cin >> newId;

			cout << "Please Enter New Name" << endl;
			cin >> newName;

			cout << "Please Select the Position for This New Employee" << endl;
			cout << "1. Normal Employee" << endl;
			cout << "2. Manager" << endl;
			cout << "3. Boss" << endl;
			cin >> dSelect;
			// base pointer
			Worker* worker = nullptr;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}
			//update info to array
			this->m_EmpArray[ret] = worker;
			cout << "Modify Successfully" << endl;
			this->save();
		}
		else
		{
			cout << "Employee Does Not Exist" << endl;
		}
	}
	system("pause");
	system("cls");
}

void EmployeeManagementSys::find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "NO Info in File or File Does Not Exist" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Please Enter the Method for Looking Up" << endl;
		cout << "1. Look Up Based on ID" << endl;
		cout << "2. Look Up Based on Name" << endl;
		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//look up based on ID
			int id;
			cout << "Please Enter the ID for Looking Up" << endl;
			cin >> id;
			int ret = isExist(id);
			if (ret != -1)
			{
				//exist
				cout << "Find Successfully, the Information is Below: " << endl;
				this->m_EmpArray[ret]->displayInfo();
			}
			else
			{
				cout << "Fail to Find, No Info Found" << endl;
			}
		}
		else if (select == 2)
		{
			//look up based on name
			string name;
			cout << "Please Enter the Name for Looking Up" << endl;
			cin >> name;
			//defalt fail found
			bool flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "Looking UP Successfully, the ID is: " 
						<< this->m_EmpArray[i]->m_Id 
						<< endl;
					this->m_EmpArray[i]->displayInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "No Relevant Info Found" << endl;

			}
		}
		else
		{
			cout << "Invalid Input, Please Select the Correct Input" << endl;
		}
	}
	system("pause");
	system("cls");
}

void EmployeeManagementSys::sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "NO Info in File or File Does Not Exist" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "Please Select the Sort Ways: " << endl;
		cout << "1. ascending order" << endl;
		cout << "2. decending order" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					//ascending
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)
				{
					//decending
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
			
		}
		cout << "Sort Successfully! The Result is: " << endl;
		this->save();
		this->display_Emp();
	}
}

void EmployeeManagementSys::clean_File()
{
	cout << "Are You Sure to Clean All Data?" << endl;
	cout << "1. YES" << endl;
	cout << "2. BACK TO MENU" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//clean up
		ofstream ofs(FILENAME, ios::trunc);//delete file and re-create a empty one
		ofs.close();

		if (this->m_EmpArray != nullptr)
		{
			//delete all Worker object
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = nullptr;
			}
			//delete arr ptr
			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;

		}
		cout << "Clean UP Successfully" << endl;
	}

	system("pause");
	system("cls");
}