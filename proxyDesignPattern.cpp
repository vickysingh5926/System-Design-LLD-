#include <bits/stdc++.h>
using namespace std;

enum class UserRole{
    ADMIN,
    HR,
    MANAGER,
    EMPLOYEE

};

enum class AccessType{
    CREATE,
    DELETE_,
    UPDATE,
    VIEW_ALL_DETAILS,
    VIEW_BASIC_INFO
};
class EmployeeDao {
public:
    virtual void getEmployeeInfo() = 0;
    virtual void createEmployee() = 0;
    virtual void deleteEmployee() = 0;
    virtual void updateSalary(double newSalary) = 0;
    virtual void displayEmployeeDetails() = 0;
    virtual ~EmployeeDao() = default;
};

class EmployeeDaoImpl: public EmployeeDao{

    private:
    int id;
    string name;
    string department;
    double salary;

    public:

    UserRole role;

    EmployeeDaoImpl(int id,string name, string department, double salary,UserRole role)
    :id(id),name(name), department(department), salary(salary), role(role){}

    void getEmployeeInfo() override{
        cout<<"Employee Basic Info -> Name: "<<name<<", Department: "<<department<<endl;
    }

    void createEmployee() override{
        cout<<"Employee created:"<<name<<endl;
    }
    void deleteEmployee() override{
        cout<<"Employee deleted:"<<name<<endl;
    }

    void updateSalary(double newSalary)override{
        this->salary=newSalary;
        cout<<"Salary updated to Rs. :"<<newSalary<<endl;
    }

    void displayEmployeeDetails() override{

        cout<<"Employee detail -> Id: "<<id<<",Name:"<<name<<", Department :"<<department<<", Salary :"<<salary<<",Role:"<<getRoleName(role)<<endl;
    }

    static string getRoleName(UserRole role){
        switch(role){

            case UserRole::ADMIN:return "ADMIN";
            case UserRole::EMPLOYEE:return "EMPLOYEE";
            case UserRole::HR:return "HR";
            case UserRole::MANAGER:return "MANAGER";
        }
        return "UNKNOWN";
    }
};

class EmployeeDaoProxy: public EmployeeDao{

    public:
    EmployeeDaoImpl* realEmployee;
    bool hasAccessForRole(AccessType accessType, UserRole role){

        switch(accessType){

            case AccessType::CREATE:
            case AccessType::DELETE_:
                 return role==UserRole::ADMIN;

            case AccessType::UPDATE:
                return role==UserRole::ADMIN || role==UserRole::HR;

            case AccessType::VIEW_ALL_DETAILS:
                 return role==UserRole::ADMIN || role==UserRole::HR || role==UserRole::MANAGER;

            case AccessType::VIEW_BASIC_INFO:
                 return role==UserRole::ADMIN|| role==UserRole::HR || role==UserRole::MANAGER || role==UserRole::EMPLOYEE;

            default:return false;
        }
    }

    public:
     EmployeeDaoProxy(int id,string name, string department, double salary, UserRole role){
        realEmployee=new EmployeeDaoImpl(id,name,department,salary,role);
     }
     ~EmployeeDaoProxy(){
        delete realEmployee;
     }
     
     void getEmployeeInfo() override{
        if(hasAccessForRole(AccessType::VIEW_BASIC_INFO,realEmployee->role))
        realEmployee->getEmployeeInfo();
     }
     void createEmployee() override{
         
        if(hasAccessForRole(AccessType::CREATE,realEmployee->role))
          realEmployee->createEmployee();
          else
          throw runtime_error("Access Denied: Cannot create employee");

     }
     void deleteEmployee() override{

        if(hasAccessForRole(AccessType::DELETE_,realEmployee->role))
        realEmployee->deleteEmployee();
        else
        throw runtime_error("Access denied for delete");
     }
     
    void updateSalary(double newSalary) override {
        if (hasAccessForRole(AccessType::UPDATE, realEmployee->role))
            realEmployee->updateSalary(newSalary);
        else
            throw runtime_error("Access Denied: Cannot update salary");
    }

    void displayEmployeeDetails() override {
        if (hasAccessForRole(AccessType::VIEW_ALL_DETAILS, realEmployee->role))
            realEmployee->displayEmployeeDetails();
        else
            throw runtime_error("Access Denied: Cannot view full details");
    }


};

int  main(){

     cout << "===== Proxy Design Pattern (C++) =====" << endl;

    try{

        cout<<"----ADMIN USER----"<<endl;
        EmployeeDao* admin=new EmployeeDaoProxy(1,"John","HR",3000.0,UserRole::ADMIN);
        admin->getEmployeeInfo();
        admin->displayEmployeeDetails();
        admin->createEmployee();
        admin->updateSalary(4000.0);
        admin->deleteEmployee();

        delete admin;

        cout<<"----HR User----"<<endl;
        EmployeeDao* hr=new EmployeeDaoProxy(2,"Jane","HR",2500.0,UserRole::HR);
        hr->getEmployeeInfo();
        hr->displayEmployeeDetails();
        hr->updateSalary(3000.0);
        delete hr;

         cout << "\n--- MANAGER USER ---" << endl;
        EmployeeDao* manager = new EmployeeDaoProxy(3, "Bob", "IT", 20000.0, UserRole::MANAGER);
        manager->getEmployeeInfo();
        manager->displayEmployeeDetails();
        delete manager;

        cout << "\n--- EMPLOYEE USER ---" << endl;
        EmployeeDao* employee = new EmployeeDaoProxy(4, "Alice", "Sales", 15000.0, UserRole::EMPLOYEE);
        employee->getEmployeeInfo();
        // employee->displayEmployeeDetails(); // Throws exception
        delete employee;
    }catch (exception& e) {
        cerr << e.what() << endl;
    }
  return 0;
}
