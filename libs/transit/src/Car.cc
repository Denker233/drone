#define _USE_MATH_DEFINES
#include "Car.h"
#include "AstarStrategy.h"
#include "SpinDecorator.h"
#include "JumpDecorator.h"

#include <cmath>
#include <limits>

Car::Car(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Car::~Car() {
  // Delete dynamically allocated variables
}

void Car::Update(double dt, std::vector<IEntity*> scheduler){
  // float x = std::rand()%2901-1400;
  // float y = std::rand()+240;
  // float z = std::rand()%1601-800;
  // while(x>=1500 || x<=-1400){
  //   x = std::rand()%2901-1400;
  // }
  // while(y<=240) {
  //   y = std::rand()+240; 
  // }
  // while(z>=800 || z<=-800){
  //   z = std::rand()%1601-800;
  // }
  // this->SetDestination(Vector3(x,y,z));
  // Strategy1 = new AstarStrategy(this->GetPosition(), this->GetDestination());
  // //Strategy1->Move(this,10);
  
  // delete Strategy1;
  if(toTargetPosStrategy){
    toTargetPosStrategy->Move(this, dt);
  } else  {
    int random_integer_x;
    int random_integer_y;
    int random_integer_z;
    while(random_integer_x=rand()>=1500&&random_integer_x<-1400){
      random_integer_x=rand();
    }
    while(random_integer_y=rand()<240){
      random_integer_y=rand();
    }

    while(random_integer_z=rand()>=800&&random_integer_z < -800){
      random_integer_z=rand();
    }
    this->SetDestination(Vector3(random_integer_x,random_integer_y,random_integer_z));
    toTargetPosStrategy = new AstarStrategy(this->GetPosition(), this->GetDestination(),graph);
    toTargetPosStrategy->Move(this, dt);
  }
  if(toTargetPosStrategy->IsCompleted()){
      delete toTargetPosStrategy;
      toTargetPosStrategy = NULL;
    }
}


 
