

#include <bits/stdc++.h>
using namespace std;

class Bike{

    public:
    virtual void accelerate()=0;
    virtual void applyBrakes()=0;
    virtual ~Bike(){}
};

class Engine{

    public:
    virtual void turnOnEngine()=0;
    virtual void turnOffEngine()=0;
    virtual ~Engine(){}
};

class MotorCyle:public Bike , public Engine{

   
    string company;
    bool isEngineOn;
    int speed;

    public:
    MotorCyle(string company ,int speed):company(company),isEngineOn(false),speed(speed){}

    void turnOnEngine() override{
        isEngineOn=true;
        cout<<"Engine is on..."<<endl;
    }
    void turnOffEngine() override{
         isEngineOn=false;
         cout<<"Engine is off..."<<endl;
    }
    void accelerate() override{
           speed+=10;
           cout<<"Motorcycle speed:"<<speed<<endl;
    }
    void applyBrakes() override{
        speed-=10;
        cout<<"Motorcycle speed drops to:"<<speed<<endl;
    }
};

class Bicycle  : public Bike{
       string brand;
       bool hasGears;
       int speed;

       public:
       Bicycle(string brand,bool hasGears, int speed):brand(brand),hasGears(hasGears),speed(speed){}

        void accelerate() override {
        speed += 10;
        cout << "Bicycle Speed: " << speed << endl;
    }

    void applyBrakes() override {
        speed -= 5;
        cout << "Bicycle Speed: " << speed << endl;
    }
};

int main() {
    
    MotorCyle motorcycle("HeroHonda",10);
    Bicycle bicycle("Hercules",1,10);


    motorcycle.turnOnEngine();
    motorcycle.accelerate();
    motorcycle.applyBrakes();
    motorcycle.turnOffEngine();

    bicycle.accelerate();
    bicycle.applyBrakes();
    return 0;
}
