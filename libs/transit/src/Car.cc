#define _USE_MATH_DEFINES
#include "Car.h"
#include "BeelineStrategy.h"
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

void Car::Move(){
  
  float x = std::rand()%2901-1400;
  float y = std::rand()+240;
  float z = std::rand()%1601-800;
  while(x>=1500 || x<=-1400){
    x = std::rand()%2901-1400;
  }
  while(y<=240) {
    y = std::rand()+240; 
  }
  while(z>=800 || z<=-800){
    z = std::rand()%1601-800;
  }
  this->SetDestination(Vector3(x,y,z));
  Strategy1 = new BeelineStrategy(this->GetPosition(), this->GetDestination());
  //Strategy1->Move(this,10);
  
  delete Strategy1;
}


 
