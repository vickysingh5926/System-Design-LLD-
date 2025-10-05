#include <bits/stdc++.h>
using namespace std;

enum class Direction{
    UP,
    DOWN
};
enum class ElevatorState{
    MOVING,
    IDLE
};

class ElevatorDoor{
    public:
    void openDoor(){
        cout<<"Opening the door..."<<endl;
    }
    void closeDoor(){
        cout<<"Closing the door..."<<endl;
    }
};

class ElevatorDisplay{
    int floor;
    Direction direction;
    public:
    void setDisplay(int f,Direction dir){
        floor=f;
        direction=dir;
    }

    void showDisplay(){
        cout<<floor<<endl;
        cout<<(direction==Direction::UP?"UP":"DOWN")<<endl;
    }

};

class InternalButtons{
    InternalDispatcher dispatcher;
    int availableButtons[10]={1,2,3,4,5,6,7,8,9,10};
    int buttonSelected;

    public:
    void pressButton(int destination , ElevatorCar elevatorCar){
        dispatcher.submitInternalRequest(destination,elevatorCar);
    }
};


class ElevatorCar{
    public:
    
    int id;
    ElevatorDisplay display;
    InternalButtons internalButtons;
    ElevatorState elevatorState;
    int currentFloor;
    Direction elevatorDirection;
    ElevatorDoor elevatorDoor;

    ElevatorCar(){
        elevatorState=ElevatorState::IDLE;
        currentFloor=0;
        elevatorDirection=Direction::UP;
    }

    void showDisplay(){
        display.showDisplay();
    }

    void pressButton(int destination){
        internalButtons.pressButton(destination,*this);
    }
    void setDisplay(){
        display.setDisplay(currentFloor,elevatorDirection);
    }

    bool moveElevator(Direction dir,int destinationFloor){
        int startFloor =currentFloor;

        if(dir==Direction::UP){
            for(int i=startFloor;i<=destinationFloor;i++){
                currentFloor=i;
                setDisplay();
                showDisplay();
                if(i==destinationFloor)return true;
            }
        }

        if (dir == Direction::DOWN) {
            for (int i = startFloor; i >= destinationFloor; i--) {
                currentFloor = i;
                setDisplay();
                showDisplay();
                if (i == destinationFloor) return true;
            }
        }

        return false;
    }

};

class ElevatorController{
    public:

    priority_queue<int,vector<int>,greater<int>>upMinPQ;
    priority_queue<int>downMaxPQ;
    ElevatorCar elevatorCar;

    ElevatorController (ElevatorCar e){
        elevatorCar=e;
    }
    void submitExternalRequest(int floor , Direction direction){

        if(direction==Direction::DOWN)downMaxPQ.push(floor);
        else
        upMinPQ.push(floor);
    }

    void submitInternalRequest(int floor){
        //future logic
    }
   
     void controlElevator(){
        while(true){
            if(elevatorCar.elevatorDirection==Direction::UP){
                //control logic
            }
        }
     }


};
class ElevatorCreator{

    public:
    static vector<ElevatorController>elevatorControllerList;

    static void initialize(){
        ElevatorCar elevatorCar1;
        elevatorCar1.id=1;
        ElevatorController controller1(elevatorCar1);

        ElevatorCar elevatorCar2;
        elevatorCar2.id=2;
        ElevatorController controller2(elevatorCar2);

        elevatorControllerList.push_back(controller1);
        elevatorControllerList.push_back(controller2);
        
        
    }
};

vector<ElevatorController>ElevatorCreator::elevatorControllerList;

class InternalDispatcher{
    public:

    vector<ElevatorController>&elevatorControllerList=ElevatorCreator::elevatorControllerList;

    void submitInternalRequest(int floor,ElevatorCar elevatorCar){
        // future internal handling
    }
};

class ExternalDispatcher{
     vector<ElevatorController>&elevatorControllerList=ElevatorCreator::elevatorControllerList;

     public:
     void submitExternalRequest(int floor,Direction direction){

        for(auto &controller: elevatorControllerList){
            int elevatorID=controller.elevatorCar.id;
            if(elevatorID%2==1 && floor%2==0)
              controller.submitExternalRequest(floor,direction);
              else if(elevatorID%2==0 && floor%2==0)
               controller.submitExternalRequest(floor,direction);
        }
     }
};

class Floor{
    public:

    int floorNumber;
    ExternalDispatcher externalDispatcher;

    Floor(int num){
         floorNumber=num;
    }

    void pressButton(Direction direction){
        externalDispatcher.submitExternalRequest(floorNumber,direction);
    }
};

class Building{
    vector<Floor>floorList;
    public:
    Building(vector<Floor>floors){
        floorList=floors;
    }

    void addFloors(Floor f){
        floorList.push_back(f);
    }
    void removeFloors(Floor f){
       
    }
    vector<Floor>getAllFloors(){
        return floorList;
    }
};

int main(){

    ElevatorCreator::initialize();

    vector<Floor>floorList;
    for(int i=1;i<=5;i++){
        floorList.emplace_back(i);
    }

    Building building(floorList);

    cout<<"Building initialized:"<<floorList.size()<<endl;
    return 0;
}
