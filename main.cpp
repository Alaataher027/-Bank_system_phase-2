#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Validation {
public:
    static bool setName(string name) {
        bool flag = true;

        if (name.length() <= 20 && name.length() >= 5)
        {
            for (int i = 0; i < name.length(); i++) {
                if (!isalpha(name[i])) {
                    return false;
                }
            }
        }
        return flag;
    }
    static bool setPassword(string password)
    {
        if (password.length() <= 20 && password.length() >= 8)
            return true;
        else
            return false;
    }
    static bool setBalance(int balance)
    {
        if (balance < 1500)
            return false;
        else
            return true;
    }
    static bool setSalary(int salary)
    {
        if (salary >= 5000)
        {
            return true;
        }
        else
            return false;
    }
};
class Person: public Validation
{
protected:
    string Name, Password;
    int Id;
public:
    Person() {
        Name = " ";
        Password = " ";
        Id = 0;
    }
    Person(int id, string name, string password) {
        setName(name);
        setPassword(password);
        setId(id);
    }
    void setName(string name)
    {
        if (Validation::setName(name))
            Name = name;
        else if (name.length() < 5)
            cout << "Name must be greater than 5\n";
        else if (name.length() > 20)
            cout << " name must be smaller than 20 \n";
        else
            cout << "you have entered unvaild name\n";
    }
    void setPassword(string password)
    {
        if (Validation::setPassword(password)) {
            Password = password;
        }
        else if (password.length() < 8)
            cout << "password must be greater than 8\n";
        else
            cout << " password must be smaller than 20 \n";
    }
    void setId(int id)
    {
        Id = id;
    }
    int getId()
    {
        return Id;
    }
    string getName()
    {
        return Name;
    }
    string getPassword()
    {
        return Password;
    }
    virtual void Display()
    {
        cout << "Id : " << getId() << '\n';
        cout << "Name : " << getName() << '\n';
        cout << "Password : " << getPassword() << '\n';
        cout << "=================================\n";
    }
};



class Client : public Person
{
protected:
    double Balance;
public:
    Client() :Person() {
        setBalance(1500);
    }
    Client(int id, string name, string password, double balance) : Person(id, name, password) {
        setBalance(balance);
    }
    void setBalance(int balance)
    {
        if (Validation::setBalance(balance))
            Balance += balance;
        else {
            cout << "you must enter balance more than 1500\n";
            //exit(0);
        }
    }
    double getBalance()
    {
        return Balance;
    }
    void deposit(double amount)
    {

        Balance += amount;
    }
    void withdraw(double amount)
    {

        if (Balance - amount >= 1500)
            Balance -= amount;
        else {
            cout << "you can't withdraw amount less than 1500\n";
            //exit(0);
        }
    }
    void transferTo(double amount, Client& recipient)
    {
        if (Balance > amount)
        {
            Balance = Balance - amount;
            recipient.Balance += amount;
        }
        else
        {
            cout << "Sorry Transfer failed " << '\n';
        }
    }
    void checkBalance()
    {
        if (Balance > 1500) {
            cout << " you can withdraw and transferto\n";
        }
        else
            cout << " you can't withdraw and transferto\n";
    }

    void display()
    {
        Person::Display();
        cout << "Balance : " << getBalance() << '\n';
    }

};

class Employee : public Person
{
protected:
    double Salary;
public:
    Employee() {
        Salary = 5000;
    }
    Employee(int id, string name, string password, double salary) : Person(id, name, password) {
        Salary = salary;
    }
    void setSalary(int salary)
    {
        if (Validation::setSalary)
        {
            Salary = salary;
        }
        else
            cout << "Min salary is 5000 !\n";
        //exit(0);
    }
    int getSalary()
    {
        return Salary;
    }
    void display()
    {
        Person::Display();
        cout << "Balance : " << getSalary() << '\n';

    }
    void addClient(Client& client);
    vector<Client> allClients;
    Client* searchClient(int id);
    void listClient();
    void editClient(int id, string name, string password, double balance);
};

class Admin : public Person {
protected:
    double Salary;
public:
    Admin() {
        Salary = 5000;
    }
    Admin(int id, string name, string password, double salary) : Person(id, name, password) {
        Salary = salary;
    }
    void setSalary(int salary)
    {
        if (Validation::setSalary)
        {
            Salary = salary;
        }
        else
            cout << "Min salary is 5000 !\n";
        //exit(0);
    }
    int getSalary()
    {
        return Salary;
    }
    void display()
    {
        Person::Display();
        cout << "Salary : " << getSalary() << '\n';
    }

};
class DataSourceInterface
{
public:

    virtual void addClient(Client) = 0;
    virtual void addEmployee(Employee) = 0;
    virtual void addAdmin(Admin) = 0;
    virtual void getAllClients() = 0;
	virtual void getAllEmployees() = 0;
	virtual void getAllAdmins() = 0;
    virtual void removeAllClients() = 0;
    virtual void removeAllEmployees() = 0;
    virtual void removeAllAdmins() = 0;

};
class FileManager : public DataSourceInterface
{
public:
    void addClient(Client client)
    {
        ofstream ClientsFile ("Clients.txt", ios::app);
        cout<<"Enter the client info:\n";
        cout<<"Press ctrl+z to exit\n";

        ClientsFile.close();
    }
    void addEmployee(Employee)
    {
        ofstream EmployeeFile ("Employee.txt");
        //EmployeeFile<<e;
        EmployeeFile.close();
    }
    void addAdmin(Admin)
    {
        ofstream AdminFile ("Admin.txt");
        //AdminFile<<Admin;
        AdminFile.close();
    }
    void removeAllClients()
    {
         ofstream ClientsFile ("Clients.txt", ios::app);
         ClientsFile.open("Clients.txt", ios::out | ios::trunc);
         ClientsFile.close();
    }
    void removeAllEmployees()
    {
         ofstream EmployeeFile ("Employee.txt");
         EmployeeFile.open("Employee.txt", ios::out | ios::trunc);
         EmployeeFile.close();
    }
    void removeAllAdmins()
    {
         ofstream AdminFile ("Admin.txt");
         AdminFile.open("Admin.txt", ios::out | ios::trunc);
         AdminFile.close();
    }

};
int main()
{
    ofstream ClientsFile ("Clients.txt");
    ClientsFile<<"7|yaya|789*io|4500";
    ClientsFile.close();

    ofstream EmployeeFile ("Employee.txt");
    EmployeeFile<<"8|hazem|87*ws|5000";
    EmployeeFile.close();

    ofstream AdminFile ("Admin.txt");
    AdminFile<<"9|reem|78*pdwbf|6570";
    AdminFile.close();

    
    Admin a;
    a.setName("taghreed");
    a.setPassword("ju8@77edj");
    a.setSalary(6554);
    a.setId(7845712);
    a.display();

    cout << "\n";

    Employee e;
    e.setName("mohamed");
    e.setPassword("hgfd**87");
    e.setSalary(4000);
    e.setId(458712574);
    e.display();

    cout << "\n";

    Client c;
    c.setName("ahmed");
    c.setBalance(4770);
    c.setPassword("024*55sdg");
    c.setId(19587451);
    c.display();
    c.deposit(300);
    c.withdraw(1600);
    c.checkBalance();

     //FileManager fc;
    //fc.addClient(c);

}
