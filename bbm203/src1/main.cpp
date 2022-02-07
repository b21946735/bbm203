#include <iostream>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

vector<int> SplitString(string str) { // split string
    istringstream iss(str);
    vector<int> result;
    for (string s; iss >> s;)
        result.push_back(stoi(s));
    return result;
}

vector<int> split(const string& s) // split string
{
    vector<int> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, '-'))
    {
        tokens.push_back(stoi(token));
    }
    return tokens;
}


class Date {  
public:
    Date(int d, int m, int y) :day(d), month(m), year(y) {}

    int getDay() { return day; }
    int getMonth() { return month; }
    int getYear() { return year; }

    bool operator == (string yea) {
        if (yea == to_string(year))
        {
            return true;
        }
        return false;
    }

    bool operator >= (string date) {
        if (split(date)[2] < year)
        {
            return true;
        }
        else if(split(date)[2] == year) {
            if (split(date)[1] < month)
            {
                return true;
            }
            else if (split(date)[1] == month) {
                if (split(date)[0] <= day)
                {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
        
    }

    bool operator <= (string date) {
        if (split(date)[2] > year)
        {
            return true;
        }
        else if (split(date)[2] == year) {
            if (split(date)[1] > month)
            {
                return true;
            }
            else if (split(date)[1] == month) {
                if (split(date)[0] >= day)
                {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }

    }

    friend ostream& operator << (ostream& out, const Date& c);
    

private:
    int day;
    int month;
    int year;
};

ostream& operator << (ostream& out, const Date& c)
{
    out << c.day <<"-"<<c.month<<"-"<<c.year;
    return out;
}


class Employee {

    public:
        Employee(string name, string surname,string title, int eN,int eT,float sC,int d1,int m1,int y1, int d2, int m2, int y2,int serviceDay )
            : employeeNumber(eN),employeeType(eT),name(name),title(title),surname(surname),salaryCoefficent(sC),
            serviceDay(serviceDay), birthDate{ d1, m1, y1 }, appointmentDate{ d2, m2, y2 }{
            
        }


        Employee* operator == (int empNumb) {
            if (employeeNumber== empNumb)
            {
                return this;
            }
            else {
                return nullptr;
            }
        }

        Employee* operator == (string titl) {
            if (title == titl)
            {
                return this;
            }
            else {
                return nullptr;
            }
        }

        friend ostream& operator << (ostream& out, const Employee& c);


       

        int getEmployeeNumber() { return employeeNumber; }
        int getEmployeeType() { return employeeType; }
        string getName() { return name; }
        string getSurname() { return surname; }
        string getTitle() { return title; }
        float getSalaryCoefficent() { return salaryCoefficent; }
        Date getBirthDate() { return birthDate; }
        Date getAppointmentDate() { return appointmentDate; }
        int getServiceDay() { return serviceDay; }
 





        void setSalaryCoefficent(float sal) { salaryCoefficent = sal; };
        void setTitle(string titl) { title = titl; };



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

ostream& operator << (ostream& out, const Employee& c)
{
    out << "Employee Number: " << c.employeeNumber << endl << "Employee Type: " << c.employeeType << endl << "Employee Name: " << c.name << endl << "Employee Surname: " << c.surname << endl << "Employee Title: " << c.title << endl << "Salary Coefficient: " << c.salaryCoefficent << endl << "Date of Birth: " << c.birthDate << endl << "Date of Appointment: " << c.appointmentDate << endl<< "Length of Service: "<<c.serviceDay<<endl;
    return out;
}

class TemporaryEmployee : public Employee {
    using Employee::Employee;
   
};

class PermanentEmployee : public Employee {
    using Employee::Employee;


};



template<class T >
class DoubleDynamicLinkedList {

    struct Node
    {
        T data;
        Node* next;
        Node* prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };


    Node* head, * tail;

    public:
        DoubleDynamicLinkedList() : head(nullptr), tail(nullptr) {}


        Node* getNode(T value) {
            Node* p;
            p = new Node(value);
            return p;
        }
        void freeNode(Node* p)
        {
            delete p;
        }

        void insertAtBeginning(T value) {
            Node* newNode = getNode(value);
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }
        void insertAtEnd(T value) {
            Node* newNode = getNode(value);
            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        Node* findNode(T value) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data == value)
                {
                    return temp;
                }
                temp = temp->next;
            }
            return nullptr;
        }

        void deleteNode(T value) {
            Node* find = findNode(value);
            find->prev->next = find->next;
            freeNode(find);
        }
        void deleteNode(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            
            freeNode(node);
        }

        void insertAfter(T value,T x) {
            Node* newNode = getNode(value);
            Node* xNode = findNode(x);
            xNode->next->prev = newNode;
            newNode->next = xNode->next;
            newNode->prev = xNode;
            xNode->next = newNode;
        }

        T deleteAfter(Node* node) {
            node->next->next->prev = node;
            node->next = node->next->next;
            T x = node->next->data;
            freeNode(node);
            return x;
        }

        T SearchByEmpNumber(int value) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data == value)
                {
                    return temp->data;
                }
                temp = temp->next;
            }
            return *new PermanentEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);

        }

        void SearchByEmpNumberToDelete(int value) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data == value)
                {
                    deleteNode(temp);
                    return;
                }
                temp = temp->next;
            }
        }
     

        T SearchByEmpTitle(string title) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data == title)
                {
                    return temp->data;
                }
                temp = temp->next;
            }
            return *new PermanentEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);

        }

        void ListAllByMonth(int month) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data.getBirthDate().getMonth()==month)
                {
                    cout << temp->data << endl;
                }
                temp = temp->next;
            }
        }

        void ListAll() {
            Node* temp = head;
            while (temp != nullptr) {

                cout << temp->data << endl;
               
                temp = temp->next;
            }
        }

        void ListAllByDate(string date) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data.getAppointmentDate() >= date)
                {
                    cout << temp->data << endl;
                }
                temp = temp->next;
            }
        }

        void ListAllByBornDate(string date) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data.getBirthDate() <= date)
                {
                    cout << temp->data << endl;
                }
                temp = temp->next;
            }
        }


        void ListAllByYear(int year) {
            Node* temp = head;
            while (temp != nullptr) {
                if (temp->data.getAppointmentDate().getYear() == year)
                {
                    cout << temp->data << endl;
                }
                temp = temp->next;
            }
        }


};


template<class T>
class CircularArrayLinkedList {

    
    
    int current = -1;

    struct nodetype {
        T* data;
        nodetype(T* inf):data(inf) {}
       
    };
    vector<nodetype*> node;
    

    

   


    public:
        CircularArrayLinkedList() { }


       

        int addNode(T* inf)
        {
            if (current == 20-1)
            {
                
            }
            else {
                current++;
            }
            
            node.push_back(new nodetype(inf));
            return current;
        }

        void freeNode(int p)
        {
            for (int i = p; i <= current; i++)
            {
                node.erase(node.begin() + i);
            }
            if (current ==0)
                current--;

        }

        T SearchByEmpNumber(int value) {
            for (int i = 0; i <= current; i++)
            {
                if (*(node[i]->data) == value)
                {
                    return *(node[i]->data);
                }
            }
            return *new TemporaryEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        }

        void SearchByEmpNumberToDelete(int value) {
            for (int i = 0; i <= current; i++)
            {
                if (*(node[i]->data) == value)
                {
                    freeNode(i);
                }
            }
        }

        T SearchByEmpTitle(string title) {
            for (int i = 0; i <= current; i++)
            {
                if (*(node[i]->data) == title)
                {
                    return *(node[i]->data);
                }
            }
            cout << "no employee with this title" << endl;
            return *new TemporaryEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        }

        void ListAllByMonth(int month) {
            for (int i = 0; i <= current; i++)
            {
                if (node[i]->data->getBirthDate().getMonth() == month)
                {
                    cout << *(node[i]->data) << endl;
                }
            }
        }

        void ListAll() {
            for (int i = 0; i <= current; i++)
            {

                cout << *(node[i]->data) << endl;
                
            }
        }

        void ListAllByDate(string date) {
            for (int i = 0; i <= current; i++)
            {
                if (node[i]->data->getAppointmentDate() >= date)
                {
                    cout << *(node[i]->data) << endl;
                }
            }
        }

        void ListAllByBornDate(string date) {
            for (int i = 0; i <= current; i++)
            {
                if (node[i]->data->getBirthDate() <= date)
                {
                    cout << *(node[i]->data) << endl;
                }
            }
        }

        void ListAllByYear(int year) {
            for (int i = 0; i <= current; i++)
            {
                if (node[i]->data->getAppointmentDate().getYear() == year)
                {
                    cout << *(node[i]->data) << endl;
                }
            }
        }




};

PermanentEmployee IsListIncludeEmp(DoubleDynamicLinkedList<PermanentEmployee> &perEmployees,int empNumb) {
    try
    {
        PermanentEmployee emp = perEmployees.SearchByEmpNumber(empNumb);
        return emp;
    }
    catch (const std::exception&)
    {
        return *new PermanentEmployee("s", "s", "s", -1, -1, - 1, - 1 ,- 1, - 1, - 1, - 1 ,- 1, - 1);
    }
    
}

TemporaryEmployee IsListIncludeEmp(CircularArrayLinkedList<TemporaryEmployee> &tempEmployees, int empNumb) {
    try
    {
        TemporaryEmployee emp = tempEmployees.SearchByEmpNumber(empNumb);
        return emp;
    }
    catch (const std::exception&)
    {
        return *new TemporaryEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
    }
    
}

PermanentEmployee IsListIncludeEmp(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, string title) {
    try
    {
        PermanentEmployee emp = perEmployees.SearchByEmpTitle(title);
        return emp;
    }
    catch (const std::exception&)
    {
        return *new PermanentEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
    }

}

TemporaryEmployee IsListIncludeEmp(CircularArrayLinkedList<TemporaryEmployee>& tempEmployees, string title) {
    try
    {
        TemporaryEmployee emp = tempEmployees.SearchByEmpTitle(title);
        return emp;
    }
    catch (const std::exception&)
    {
        return *new TemporaryEmployee("s", "s", "s", -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
    }

}



 void Choices() {
     cout << "____ Employee Recording System ____\n";
     cout << "Please select for the following menu Operation:\n";
     cout << "1) Appointment of a new employee\n";
     cout << "2) Appointment of a transferred employee\n";
     cout << "3) Updating the title and salary coefficient of an employee\n";
     cout << "4) Deletion of an employee\n";
     cout << "5) Listing the information of an employee\n";
     cout << "6) Listing employees ordered by employee number\n";
     cout << "7) Listing employees ordered by appointment date\n";
     cout << "8) Listing employees appointed after a certain date\n";
     cout << "9) Listing employees assigned in a given year\n";
    cout << "10) Listing employees born before a certain date\n";
    cout << "11) Listing employees born in a particular month\n";
    cout << "12) Listing the information of the last assigned employee with a given title\n";
}



 int AskForNumber() {
     int x;
     cin >> x;
     return x;
 }

 string AskForInput(string text) {
     string x;
     cout << text << endl;
     cout << "[";
     cin >> x;
     return x;
 }

 void _1and2(int _1or2, DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 1 and 2
     int empNumber= stoi(AskForInput("Please type the employee number"));
     int empType = stoi(AskForInput("Type the employee type"));
     string name = AskForInput("Type the name");
     string surName = AskForInput("Type surname");
     string title = AskForInput("Type title");
     float salaryCoef= stof(AskForInput("Type salary coefficient"));
     string birthDate= AskForInput("Type birth date");
     string appDate= AskForInput("Type appointment date");
     int serviceDays = 0;
     if (_1or2 == 1)
     {
         serviceDays = 0;
     }
     else {
         serviceDays= stoi(AskForInput("Type length of service days"));
     }
     if (!(IsListIncludeEmp(perEmployees, empNumber) == -1)&& !(IsListIncludeEmp(tempEmployees, empNumber) == -1)) // check if employee is permanent of temporary
         return;
     vector<int> BD = split(birthDate);
     vector<int> AD = split(appDate);
     if (empType == 0) {
         tempEmployees.addNode(new TemporaryEmployee(name, surName, title, empNumber, empType, salaryCoef, BD[0], BD[1], BD[2], AD[0], AD[1], AD[2], serviceDays));
     }
     else {
         perEmployees.insertAtBeginning(*new PermanentEmployee(name,surName,title,empNumber,empType,salaryCoef,BD[0],BD[1],BD[2],AD[0],AD[1],AD[2],serviceDays));
     }
 }


 void _3(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee> &tempEmployees) { // TASK 3
     int empNumber = stoi(AskForInput("Please type the employee number"));
     string title = AskForInput("Type title");
     float salaryCoef = stof(AskForInput("Type salary coefficient"));
     PermanentEmployee perEmp = IsListIncludeEmp(perEmployees, empNumber);
     TemporaryEmployee tempEmp = IsListIncludeEmp(tempEmployees, empNumber);
     bool isPer; // check if employee is permanent of temporary
     if (perEmp == -1)
     {
         if (tempEmp == -1)
         {
             return;
         }
         else {
             isPer = false;
         }
     }
     else {
         isPer = true;
     }
     if (isPer)
     {
         perEmp.setSalaryCoefficent(salaryCoef);
         perEmp.setTitle(title);
     }
     else {
         tempEmp.setSalaryCoefficent(salaryCoef);
         tempEmp.setTitle(title);
     }

     
 }

 void _4(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee> &tempEmployees) { // TASK 4
     int empNumber = stoi(AskForInput("Please type the employee number"));
     PermanentEmployee perEmp = IsListIncludeEmp(perEmployees, empNumber);
     TemporaryEmployee tempEmp = IsListIncludeEmp(tempEmployees, empNumber);
     bool isPer;  // check if employee is permanent of temporary
     if (perEmp == -1)
     {
         if (tempEmp == -1)
         {
             return;
         }
         else {
             isPer = false;
         }
     }
     else {
         isPer = true;
     }
     if (isPer)
     {
         perEmployees.SearchByEmpNumberToDelete(empNumber);
     }
     else {
         tempEmployees.SearchByEmpNumberToDelete(empNumber);
     }
 }

 void _5(DoubleDynamicLinkedList<PermanentEmployee> &perEmployees, CircularArrayLinkedList<TemporaryEmployee> &tempEmployees) { // TASK 5
     int empNumber = stoi(AskForInput("Please type the employee number"));
     PermanentEmployee perEmp = IsListIncludeEmp(perEmployees, empNumber);
     TemporaryEmployee tempEmp = IsListIncludeEmp(tempEmployees, empNumber);
     bool isPer; // check if employee is permanent of temporary
     if (perEmp == -1)
     {
         if (tempEmp == -1)
         {
             return;
         }
         else {
             isPer = false;
         }
     }
     else {
         isPer = true;
     }
     if (isPer)
     {
         cout << perEmp;
     }
     else {
         cout << tempEmp;
     }
 }

 void _6(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 6 
     perEmployees.ListAll();
     tempEmployees.ListAll();
 }

 void _7(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 7 
     perEmployees.ListAll();
     tempEmployees.ListAll();
 }

 void _8(DoubleDynamicLinkedList<PermanentEmployee> &perEmployees, CircularArrayLinkedList<TemporaryEmployee> &tempEmployees) { // TASK 8 
     string appDate = AskForInput("Type appointment date");
     perEmployees.ListAllByDate(appDate);
     tempEmployees.ListAllByDate(appDate);
 }

 void _9(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 9 
     int year = stoi(AskForInput("Please type the appointment year"));
     perEmployees.ListAllByYear(year);
     tempEmployees.ListAllByYear(year);
 }

 void _10(DoubleDynamicLinkedList<PermanentEmployee> &perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 10 
     string birthDate = AskForInput("Type birth date");
     perEmployees.ListAllByBornDate(birthDate);
     tempEmployees.ListAllByBornDate(birthDate);
 }

 void _11(DoubleDynamicLinkedList<PermanentEmployee> &perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 11
     int month = stoi(AskForInput("Please type the month"));
     perEmployees.ListAllByMonth(month);
     tempEmployees.ListAllByMonth(month);
 }

 void _12(DoubleDynamicLinkedList<PermanentEmployee>& perEmployees, CircularArrayLinkedList<TemporaryEmployee>& tempEmployees) { // TASK 12
     string empTitle = AskForInput("Please type the employee title");
     PermanentEmployee perEmp = IsListIncludeEmp(perEmployees, empTitle);
     TemporaryEmployee tempEmp = IsListIncludeEmp(tempEmployees, empTitle);
     bool isPer; // check if employee is permanent of temporary
     if (perEmp == -1)
     {
         if (tempEmp == -1)
         {
             return;
         }
         else {
             isPer = false;
         }
     }
     else {
         isPer = true;
     }
     if (isPer)
     {
         cout << perEmp;
     }
     else {
         cout << tempEmp;
     }
 }



int main()
{
    DoubleDynamicLinkedList<PermanentEmployee> perEmployees;  
    CircularArrayLinkedList<TemporaryEmployee> tempEmployees;


    Choices(); // starter screen
    while (true) {
        switch (AskForNumber())  // ask number for operation
        {
        case 1:
            _1and2(1,perEmployees, tempEmployees);
            break;
        case 2:
            _1and2(2, perEmployees, tempEmployees);
            break;
        case 3:
            _3(perEmployees, tempEmployees);
            break;
        case 4:
            _4(perEmployees, tempEmployees);
            break;
        case 5:
            _5(perEmployees, tempEmployees);
            break;
        case 6:
            _6(perEmployees, tempEmployees);
            break;
        case 7:
            _7(perEmployees,tempEmployees);
            break;
        case 8:
            _8(perEmployees, tempEmployees);
            break;
        case 9:
            _9(perEmployees, tempEmployees);
            break;
        case 10:
            _10(perEmployees, tempEmployees);
            break;
        case 11:
            _11(perEmployees, tempEmployees);
            break;
        case 12:
            _12(perEmployees, tempEmployees);
            break;

        }
    }
}



