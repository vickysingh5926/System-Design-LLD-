#include <bits/stdc++.h>
using namespace std;

class ChefTasks{
    public:
    virtual void prepareFood()=0;
    virtual void decideMenu()=0;
    virtual ~ChefTasks()=default;

};
class WaiterTasks{

    public:
    virtual void serveFoodAndDrinks()=0;
    virtual void takeOrder()=0;
    virtual ~WaiterTasks()=default;
};

class Maintenance{
    public:
    virtual void cleanTheKitchen()=0;
    virtual void reStockGroceries()=0;
    virtual ~Maintenance()=default;
};

class Chef : public  ChefTasks{
    public:
    void prepareFood() override{
        cout<<"Preparing food..."<<endl;
    }
    void decideMenu() override{
        cout<<"Deciding menu..."<<endl;
    }
};

class Waiter : WaiterTasks{

    public:
    void serveFoodAndDrinks() override {
         cout<<"Serving...."<<endl;
    }
    void takeOrder() override{
        cout<<"Taking order"<<endl;
    }
};

int  main(){

     Chef chef;
     Waiter waiter;
     chef.prepareFood();
     chef.decideMenu();

     waiter.serveFoodAndDrinks();
     waiter.takeOrder();
}

