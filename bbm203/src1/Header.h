#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> split(const string& s);
class Date {
	public:
		Date(int d, int m, int y);
		int getDay();
		int getMonth();
		int getYear();
		bool operator == (string yea);
		bool operator >= (string date);
		bool operator <= (string date);
		friend ostream& operator << (ostream& out, const Date& c);
	private:
		int day;
		int month;
		int year;
};
ostream& operator << (ostream& out, const Date& c);
class Employee {

	public:
		Employee(string name, string surname, string title, int eN, int eT, float sC, int d1, int m1, int y1, int d2, int m2, int y2, int serviceDay);
		Employee* operator == (int empNumb);
		Employee* operator == (string titl);
		friend ostream& operator << (ostream& out, const Employee& c);

		int getEmployeeNumber();
		int getEmployeeType();
		string getName();
		string getSurname();
		string getTitle();
		float getSalaryCoefficent();
		Date getBirthDate();
		Date getAppointmentDate();
		int getServiceDay();
		void setSalaryCoefficent(float sal);
		void setTitle(string titl);
	private:
		const int employeeNumber;
		const int employeeType;
		const string name;
		const string surname;
		string title;
		float salaryCoefficent;
		Date birthDate;
		Date appointmentDate;
		const int serviceDay;
};
ostream& operator << (ostream& out, const Employee& c);
class TemporaryEmployee : public Employee{};
class PermanentEmployee : public Employee {};
template<class T >
class DoubleDynamicLinkedList {
	struct Node{};
	Node* head, * tail;

	public:
		DoubleDynamicLinkedList() {};
		Node* getNode(T value);
		void freeNode(Node* p);
		void insertAtBeginning(T value);
		void insertAtEnd(T value);
		Node* findNode(T value);
		void deleteNode(T value);
		void deleteNode(Node* node);
		void insertAfter(T value, T x);
		T deleteAfter(Node* node);
		T SearchByEmpNumber(int value);
		void SearchByEmpNumberToDelete(int value);
		T SearchByEmpTitle(string title);
		void ListAllByMonth(int month);
		void ListAll();
		void ListAllByDate(string date);
		void ListAllByBornDate(string date);
		void ListAllByYear(int year);
};
template<class T>
class CircularArrayLinkedList {
	int current;
	struct nodetype{};
	vector<nodetype*> node;
	public:
		CircularArrayLinkedList() { };
		int addNode(T* inf);
		void freeNode(int p);
		T SearchByEmpNumber(int value);
		void SearchByEmpNumberToDelete(int value);
		T SearchByEmpTitle(string title);
		void ListAllByMonth(int month);
		void ListAll();
		void ListAllByDate(string date);
		void ListAllByBornDate(string date);
		void ListAllByYear(int year);
};
PermanentEmployee IsListIncludeEmp(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, int empNumb);
TemporaryEmployee IsListIncludeEmp(CircularArrayLinkedList<TemporaryEmployee>& tempEmployees, int empNumb);
PermanentEmployee IsListIncludeEmp(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, string title);
TemporaryEmployee IsListIncludeEmp(CircularArrayLinkedList<TemporaryEmployee>& tempEmployees, string title);
void Choices();
int AskForNumber() { int x; };
string AskForInput(string text) { string x;  };
void _1and2(int _1or2, DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int empNumber;
	int empType;
	string name;
	string surName;
	string title;
	float salaryCoef;
	string birthDate;
	string appDate;
	int serviceDays;
	vector<int> BD;
	vector<int> AD;
};
void _3(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int empNumber;
	string title;
	float salaryCoef;
	bool isPer;
};
void _4(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int empNumber;
	bool isPer;
};
void _5(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int empNumber;
	bool isPer;
};
void _6(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees);
void _7(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees);
void _8(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	string appDate;
};
void _9(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int year;
};
void _10(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	string birthDate;
};
void _11(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int month;
};
void _12(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) {
	int empNumber;
	string title;
};