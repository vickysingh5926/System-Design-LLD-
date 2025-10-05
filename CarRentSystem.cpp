#include <bits/stdc++.h>
using namespace std;

enum class ReservationType{
    HOURLY,
    DAILY
};
enum class ReservationStatus{
    SCHEDULED,
    INPROGRESS,
    COMPLETED,
    CANCELLED
};
enum class PaymentMode{
    CASH,
    ONLINE
};
enum class VehicleType{
    CAR,
    BIKE
};

class Location{
    public:

    string address;
    int pincode;
    string city;
    string state;
    string country;

    Location(int pincode,string city,string state,string country):
     pincode(pincode), city(city), state(state), country(country) {}

};

class User{
    public:
    int userId;
    string userName;
    string drivingLicence;

    User()=default;
    User(int id,string name,string licence):userId(id),userName(name),drivingLicence(licence){}
};

class Vehicle{
     protected:
     int vehicleId;
     VehicleType vehicleType;
    public:

    virtual ~Vehicle()=default;

    void setVehicleId(int id){vehicleId=id};
    int getVehicleId(){return vehicleId};

    void setVehicleType(VehicleType type){vehicleType=type;}
    VehicleType getVehicleType(){return vehicleType;}


};

class Car:public Vehicle{

    public:
    Car(){vehicleType=VehicleType::CAR;}
};

class Reservation{

    public:

    int reservationId;
    User* user;
    Vehicle* vehicle;
    time_t bookingDate;
    time_t dateBookedFrom;
    time_t dateBookedTo;
    Location* pickUpLocation;
    Location* dropLocation;
    ReservationType reservationType;
    ReservationStatus reservationStatus;

    Reservation(): user(nullptr),vehicle(nullptr),pickUpLocation(nullptr),dropLocation(nullptr){}

    int createReserve(User* user, Vehicle* vehicle){

        reservationId=1000+rand()%9000;
        this->user=user;
        this->vehicle=vehicle;
        reservationType=ReservationType::DAILY;
        reservationStatus=ReservationStatus::SCHEDULED;
        return reservationId;
    }
};

class Bill{

    public:
    Reservation* reservation;
    double totalBillAmount;
    bool isBillPaid;

    Bill(Reservation* reservation)
    :reservation(reservation),totalBillAmount(computeBillAmount),isBillPaid(false){}

    private:
    double computeBillAmount(){
        return 100.0;
    }
};

class Payment{
    public:
    void payBill(Bill* bill){

        bill->isBillPaid=true;
        cout<<"Payment completed for reservation ID:"<<bill->reservation->reservationId<<endl;
    }
};

class VehicleInventoryManagement{
    vector<Vehicle*>Vehicles;

    public:
    VehicleInventoryManagement()=default;
    VehicleInventoryManagement(vector<Vehicle*>vehicles):vehicles(vehicles){}

    vector<Vehicle*>getVehicles(){
        return vehicles;
    }
    void setVehicles(vector<Vehicle*>v){
        vehicle=v;
    }

};

class Store{

    public:

    int storeId;
    VehicleInventoryManagement inventoryManagement;
    Location* storeLocation;
    vector<Reservation*>reservations;

    vector<Vehicle*>getVehicles(VehicleType vehicleType){
        return inventoryManagement.getVehicles();
    }

    void setVehicles(vector<Vehicle*>vehicles){
        inventoryManagement=VehicleInventoryManagement(vehicles);
    }

    Reservation* createReservation(Vehicle* vehicle, User* user){
        Reservation *reservation=new Reservation();
        reservation->createReserve(user,vehicle);
        reservations.push_back(reservation);
        return reservation;
    }

    bool completeReservations(int reservationID){

        for(auto& res: reservations){

            if(res->reservationId==reservationID){

                res->reservationStatus=ReservationStatus::COMPLETED;
                   cout << "Reservation " << reservationID << " marked as completed.\n";
                   return true;
            }
        }
        return false;
    }
};

class VehicleRentalSystem{

    public:
    vector<Store*>storeList;
    vector<User*>userList;

    VehicleRentalSystem(vector<Store*>stores,vector<User*>users):
    storeList(stores),userList(users){}

    store* getStore(Location* location){
        return storeList[0];
    }

    

};

int main(){

    srand(time(0));

    vector<User*>users;
    users.push_back(new User(1,"Vicky","djdfk"));

    vector<Vehicle*>vehicles;
    Vehicle* v1=new Car();
    v1->setVehicleId(1);
    vehicles.push_back(v1);

     Vehicle* v2 = new Car();
    v2->setVehicleID(2);
    vehicles.push_back(v2);

    vector<Store*>stores;
    Store* store1=new Store();
    store1->storeId=1;
    store1->setVehicles(vehicles);
    stores.push_back(store1);

    VehicleRentalSystem rentalSystem(stores,users);
    User* user=users[0];

    Location* location=new Location(403012, "Bangalore", "Karnataka", "India");
    Store* store=rentalSystem.getStore(location);

    vector<Vehicle*>storeVehicles=store->getVehicles(VehicleType::CAR);

    Reservation* reservation=store->createReservation(storeVehicles[0],user);

    Bill* bill=new Bill(reservation);

    Payment* payment=new Payment();
    payment->payBill(bill);

    store->completeReservations(reservation->reservationId);

    return 0;

}

