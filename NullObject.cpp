#include <bits/stdc++.h>
using namespace std;

class Vehicle{
    public:
    virtual void start()=0;
    virtual void stop()=0;
    virtual ~Vehicle()=default;
};

class Car:public Vehicle{

    string model;
    string color;
    int seatingCapacity;
    int fuelTankCapacity;
    bool isAvailableForTestDrive;

    public:

    Car(string model,string color,int seatingCapacity,int fuelTankCapacity,bool isAvailableForTestDrive){
         this->model= model;
         this->color=color;
          this->seatingCapacity= seatingCapacity;
          this->fuelTankCapacity=fuelTankCapacity;
          this->isAvailableForTestDrive=isAvailableForTestDrive;
    }

    void start() override{
        cout<<"Car:"<<model<<"Started"<<endl;

    }
    void stop() override{
        cout<<"Car:"<<model<<"Stopped"<<endl;
    }

    string getModel() const {return model;}
    string getColor() const {return color;}
    int getSeatingCapacity() const {return seatingCapacity;}
    int getFuelTanlCapacity() const {return fuelTankCapacity;}
    bool getIsAvailableForTestDrive() const { return isAvailableForTestDrive;}


};

class Bike:public Vehicle{

    string model;
    string color;
    int fuelTankCapacity;

    public:

    Bike(string model , string color,int fuelTankCapacity):model(model),color(color),fuelTankCapacity(fuelTankCapacity){}

    void start() override{
        cout<<"Bike "<<model<<" started"<<endl;
    }
    void stop() override{

        cout<<"Bike "<<model<<" Stopped"<<endl;
    }

    string getModel()  const{
        return model;
    }
    string getColor() const{
        return color;
    }
    int getFuelTankCapacity() const{
        return fuelTankCapacity;
    }
};

class NullVehicle : public Vehicle{
  string model;
  string  color;
  int seatingCapacity;
  int fuelTankCapacity;
  bool isAvailableForTestDrive;

  public:

  NullVehicle():model("Default"),color("Default"),seatingCapacity(0),fuelTankCapacity(0),isAvailableForTestDrive(false){}

  
    void start() override {
        cout << "\n[-] Null Vehicle: start() - do nothing";
    }

    void stop() override {
        cout << "\n[-] Null Vehicle: stop() - do nothing";
    }

    int getSeatingCapacity() const { return seatingCapacity; }
    int getFuelTankCapacity() const { return fuelTankCapacity; }
    bool getIsAvailableForTestDrive() const { return isAvailableForTestDrive; }

};

class VehicleFactory{

    public:

    static Vehicle* getVehicle(const string & type){

        if(type=="Car"){
            return new Car("Toyota","Red",6,20,true);
        }
        else if(type=="Bike"){
          return new Bike("Yamaha","Black",30);
        }
        else{
            return new NullVehicle();
        }
    }
};

class SolutionDemo{

    public:
    static void printVehicleDetails(Vehicle* vehicle){

        if(Car* car=dynamic_cast<Car*>(vehicle)){

              cout<<"Vehicle details:"<<car->getModel()<<endl;
              cout<<", color:"<<car->getSeatingCapacity()<<endl;
              cout<<", Seating Capacity="<<car->getFuelTanlCapacity()<<endl;
            
        }
        else if(Bike *bike=dynamic_cast<Bike*>(vehicle)){
             cout << "\n[+] Vehicle Details: Bike [Model=" << bike->getModel()
                 << ", Color=" << bike->getColor()
                 << ", Fuel Tank Capacity=" << bike->getFuelTankCapacity() << "]";
        } else {
            cout << "\n[-] Null Vehicle: No details available.";       
        }
    }
       static void testDrive(Vehicle* vehicle){
        vehicle->start();
        vehicle->stop();
       }
};

int main(){

     cout << "\n##### Null Object Pattern: Solution Demo #####\n";
    
     Vehicle* car=VehicleFactory::getVehicle("Car");
     SolutionDemo::printVehicleDetails(car);
     SolutionDemo::testDrive(car);

       Vehicle* bike=VehicleFactory::getVehicle("bike");
       SolutionDemo::printVehicleDetails(bike);
       SolutionDemo::testDrive(bike);

        // NullVehicle (Invalid type handled gracefully)
    Vehicle* nullVehicle = VehicleFactory::getVehicle("null");
    SolutionDemo::printVehicleDetails(nullVehicle);
    SolutionDemo::testDrive(nullVehicle);

       delete car;
       delete bike;
       delete nullVehicle;

       return 0;
}
