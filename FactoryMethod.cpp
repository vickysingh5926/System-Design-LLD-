#include <bits/stdc++.h>
using namespace std;

class Shape{
    public:
    virtual void computeArea()=0;
    virtual void draw()=0;
    virtual ~Shape()=default;
};

class Circle:public Shape{
     public:
     void computeArea() override{
        cout<<"Area of circle"<<endl;
     }
     void draw() override{
        cout<<"Drawing circle"<<endl;
     }
}; 
class Rectangle : public Shape {
public:
    void computeArea() override {
        cout << "Inside Rectangle::computeArea() method." << endl;
    }
    void draw() override {
        cout << "Inside Rectangle::draw() method." << endl;
    }
};

class Square : public Shape {
public:
    void computeArea() override {
        cout << "Inside Square::computeArea() method." << endl;
    }
    void draw() override {
        cout << "Inside Square::draw() method." << endl;
    }
};

enum class ShapeType{
    CIRCLE,
    RECTANGLE,
    SQUARE
};

class SimpleShapeFactory{

    public:
    static Shape* createShapeInstance(ShapeType shapeType){

        switch (shapeType)
        {
        case ShapeType::CIRCLE:return new Circle();
      
        case ShapeType::RECTANGLE:return new Rectangle();
      
        case ShapeType::SQUARE:return new Square();
       
            
        
        default:throw invalid_argument("ShapeType not exist");
        }
    }
};


void simpleFactoryDemo(){

    cout << "======= Simple Factory Design Pattern ======" << endl;
    ShapeType shapeType=ShapeType::RECTANGLE;

    Shape* shape=SimpleShapeFactory::createShapeInstance(shapeType);

    shape->draw();
    shape->computeArea();

    delete shape;
}

class ShapeFactory{
    public:
    virtual Shape* createShape()=0;
    virtual ~ShapeFactory()=default;
};

class CircleCreator : public ShapeFactory{
    public:
    Shape* createShape() override{
        return new Circle();
    }

};
class RectangleCreator: public ShapeFactory{
    public:
    Shape* createShape() override{
        return new Rectangle();
    }
};
class SquareCreator:public ShapeFactory{

    public:
    Shape* createShape() override{

        return new Square();
    }
};

Shape* getShapeInstance(ShapeType shapeType){

    ShapeFactory* factory=nullptr;
    Shape* shape=nullptr;

    switch(shapeType){
           case ShapeType::CIRCLE:
                factory=new CircleCreator();
                break;
           case ShapeType::RECTANGLE:
                factory=new RectangleCreator();
                break;
           case ShapeType::SQUARE:
                factory=new SquareCreator();
                break;
           default:
                throw invalid_argument("Shape not exist");
    }

    shape =factory->createShape();
    delete factory;
    return shape;
}

void factoryMethodDemo(){

       cout << "======= Factory Method Design Pattern ======" << endl;
       ShapeType shapeType=ShapeType::RECTANGLE;

       Shape* shape=getShapeInstance(shapeType);

       shape->computeArea();
       shape->draw();
       delete shape;

}

int main(){

    simpleFactoryDemo();
    cout<<endl;
    factoryMethodDemo();
    return 0;
}
