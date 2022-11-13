#define _USE_MATH_DEFINES
#include "Helicopter.h"
#include "BeelineStrategy.h"


#include <cmath>
#include <limits>

Helicopter::Helicopter(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Helicopter::~Helicopter() {
  // Delete dynamically allocated variables
}

// void Helicopter::Move(){
//     int random_integer_x;
//     int random_integer_y;
//     int random_integer_z;
//     while(random_integer_x=rand()>=1500&&random_integer_x<-1400){
//       random_integer_x=rand();
//     }
//     while(random_integer_y=rand()<240){
//       random_integer_y=rand();
//     }

//     while(random_integer_z=rand()>=800&&random_integer_z < -800){
//       random_integer_z=rand();
//     }
//     this->SetDestination(Vector3(random_integer_x,random_integer_y,random_integer_z));
//     toTargetPosStrategy = new BeelineStrategy(this->GetPosition(), this->GetDestination());
// }
// void Helicopter::GetNearestEntity(std::vector<IEntity*> scheduler) {
//   float minDis = std::numeric_limits<float>::max();
//   for (auto entity : scheduler) {
//     if (entity->GetAvailability()) {
//       float disToEntity = this->position.Distance(entity->GetPosition());
//       if (disToEntity <= minDis) {
//         minDis = disToEntity;
//         nearestEntity = entity;
//       }
//     }
//   }

//   if(nearestEntity){
//     nearestEntity->SetAvailability(false);  // set availability to the nearest entity
//     available = false;
//     pickedUp = false;

//     destination = nearestEntity->GetPosition();

//     toTargetPosStrategy = new BeelineStrategy(this->GetPosition(), destination);
//     // std::string targetStrategyName = nearestEntity->GetStrategyName();
//     // if(targetStrategyName.compare("astar") == 0){
//     //     toTargetDestStrategy = new AstarStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
//     //     toTargetDestStrategy = new SpinDecorator(toTargetDestStrategy);
//     // } else if (targetStrategyName.compare("dfs") == 0){
//     //     toTargetDestStrategy = new DfsStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
//     //     toTargetDestStrategy = new JumpDecorator(toTargetDestStrategy);
//     // } else if (targetStrategyName.compare("dijkstra") == 0){
//     //     toTargetDestStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
//     //     toTargetDestStrategy = new SpinDecorator(toTargetDestStrategy);
//     //     toTargetDestStrategy = new JumpDecorator(toTargetDestStrategy);
//     // } 
//   }
// }

void Helicopter::Update(double dt, std::vector<IEntity*> scheduler) {
  // if (available) {
  //   GetNearestEntity(scheduler);
  // }
  //bool strtegycreated


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
    toTargetPosStrategy = new BeelineStrategy(this->GetPosition(), this->GetDestination());
    toTargetPosStrategy->Move(this, dt);
  }
  if(toTargetPosStrategy->IsCompleted()){
      delete toTargetPosStrategy;
      toTargetPosStrategy = NULL;
    }
    
//     // Moving the robot
//     // nearestEntity->SetPosition(this->GetPosition());
//     // nearestEntity->SetDirection(this->GetDirection());
//     // if(toTargetDestStrategy->IsCompleted()){
//     //     delete toTargetDestStrategy;
//     //     toTargetDestStrategy = NULL;
//     //     available = true;
//     //     nearestEntity = NULL;
//     // }

}

// void Helicopter::Rotate(double angle) {
//   Vector3 dirTmp = direction;
//   direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
//   direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
// }

// void Helicopter::Jump(double height) {
//   if(goUp){
//     position.y += height;
//     jumpHeight += height;
//     if(jumpHeight > 5){
//       goUp = false;
//     }
//   } else {
//     position.y -= height;
//     jumpHeight -= height;
//     if(jumpHeight < 0){
//       goUp = true;
//     }
//   }
// }
