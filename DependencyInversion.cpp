#include <bits/stdc++.h>
using namespace std;

class Keyboard{
    public:
    virtual void getSpecifications()=0;
    virtual ~Keyboard()=default;


};

class Mouse{
    public:
    virtual void getSpecifications()=0;
    virtual ~Mouse()=default;
};

class WiredKeyboard: public Keyboard{

    string connectionType,company, modelVersion, color;

    public:
    WiredKeyboard(string connectionType,string company, string modelVersion,string color):connectionType(connectionType),
    company(company),modelVersion(modelVersion),color(color){}

    void getSpecifications() override{

        cout<<"Wired keyboard"<<endl;
        cout<<"Company:"<<company<<endl;
        cout<<"ModelVersion:"<<modelVersion<<endl;
        cout<<"Color:"<<color<<endl;
    }
    
};

class BluetoothKeyboard:public Keyboard{

    string connectionType,company, modelVersion, color;
    public:
     BluetoothKeyboard(string connectionType,string company, string modelVersion,string color):connectionType(connectionType),
    company(company),modelVersion(modelVersion),color(color){}

    
    void getSpecifications() override{

        cout<<"Wired keyboard"<<endl;
        cout<<"Company:"<<company<<endl;
        cout<<"ModelVersion:"<<modelVersion<<endl;
        cout<<"Color:"<<color<<endl;
    }
};

class WiredMouse: public Mouse{
    string connectionType,company, modelVersion, color;

    public:
    WiredMouse(string connectionType, string company,string modelVersion,string color):
    connectionType(connectionType),company(company),modelVersion(modelVersion),color(color){}

    void getSpecifications(){

        cout<<"WiredMouse"<<endl;
         cout<<"Company:"<<company<<endl;
        cout<<"ModelVersion:"<<modelVersion<<endl;
        cout<<"Color:"<<color<<endl;
    }
};

class BluetoothMouse: public Mouse{

    string connectionType,company, modelVersion, color;

    public:
     BluetoothMouse(string connectionType, string company,string modelVersion,string color):
    connectionType(connectionType),company(company),modelVersion(modelVersion),color(color){}

     void getSpecifications(){

        cout<<"BluetoothMouse"<<endl;
         cout<<"Company:"<<company<<endl;
        cout<<"ModelVersion:"<<modelVersion<<endl;
        cout<<"Color:"<<color<<endl;
    }

};

class Macbook{

    Keyboard* keyboard;
    Mouse* mouse;

    public:
    Macbook(Keyboard* keyboard,Mouse* mouse): keyboard( keyboard),mouse(mouse){}

    Mouse* getMouse(){
        return mouse;
    }
    Keyboard* getKeyboard(){
        return keyboard;
    }

};

int main(){

       WiredKeyboard wiredKeyboard("USB","Dell","F1","Grey");
       WiredMouse wiredMouse("USB","Dell","F1","Grey");

    BluetoothKeyboard bluetoothKeyboard("Bluetooth", "Logitech", "G102", "Black");
    BluetoothMouse bluetoothMouse("Bluetooth", "Logitech", "G102", "Black");

     cout << "\n--- MacBook with Wired Parts ---" << endl;

     Macbook wiredMac(&wiredKeyboard,&wiredMouse);
     wiredMac.getKeyboard()->getSpecifications();
     wiredMac.getMouse()->getSpecifications();

     cout<<"---Mac with bluetooth---"<<endl;

     Macbook bluetoothMac(&bluetoothKeyboard, &bluetoothMouse);
     bluetoothMac.getKeyboard()->getSpecifications();
     bluetoothMac.getMouse()->getSpecifications();
};


