#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Base Vehicle class
class Vehicle {
public:
    virtual int getNumberOfWheels() {
        return 2;  // default
    }
    virtual ~Vehicle() = default;
};

// Bicycle is a type of Vehicle
class Bicycle : public Vehicle {
    // inherits getNumberOfWheels() = 2
};

// EngineVehicle is also a Vehicle
class EngineVehicle : public Vehicle {
public:
    virtual bool hasEngine() {
        return true;
    }
};

// MotorCycle is an EngineVehicle
class MotorCycle : public EngineVehicle {
    // inherits getNumberOfWheels() = 2
};

// Car is also an EngineVehicle
class Car : public EngineVehicle {
public:
    int getNumberOfWheels() override {
        return 4;  // cars have 4 wheels
    }
};

int main() {
    // Polymorphic list of Vehicles
    vector<shared_ptr<Vehicle>> vehicleList;
    vehicleList.push_back(make_shared<MotorCycle>());
    vehicleList.push_back(make_shared<Car>());
    vehicleList.push_back(make_shared<Bicycle>());

    // Works for all Vehicles
    for (auto &vehicle : vehicleList) {
        cout << vehicle->getNumberOfWheels() << endl;
    }

    // Polymorphic list of EngineVehicles
    vector<shared_ptr<EngineVehicle>> vehicleList2;
    vehicleList2.push_back(make_shared<MotorCycle>());
    vehicleList2.push_back(make_shared<Car>());
    // vehicleList2.push_back(make_shared<Bicycle>()); // ❌ Compile error equivalent in Java

    for (auto &vehicle : vehicleList2) {
        cout << "Has engine? " << (vehicle->hasEngine() ? "Yes" : "No") << endl;
    }

    return 0;
}
