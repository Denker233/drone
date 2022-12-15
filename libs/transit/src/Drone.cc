#define _USE_MATH_DEFINES
#include "Drone.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "SpinDecorator.h"
#include "JumpDecorator.h"
#include "BoosterDecorator.h"
//#include "SimulationModel.cc"
#include <iostream>
#include "SimulationModel.h"
#include "math/vector3.h"

#include <cmath>
#include <limits>

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  std::string drone_type=obj["type"];
  type = drone_type;

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler,std::vector<IEntity*> stations) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if(nearestEntity){
    nearestEntity->SetAvailability(false);  // set availability to the nearest entity
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();


    toTargetPosStrategy = new BeelineStrategy(this->GetPosition(), destination);
    std::string targetStrategyName = nearestEntity->GetStrategyName();
    if(targetStrategyName.compare("astar") == 0){
        printf("astar\n");
        for(auto each:stations){
          printf("in the station loop\n");
          Stras.push_back(new AstarStrategy(nearestEntity->GetPosition(),each->GetPosition(), nearestEntity->GetDestination(), graph));
        }
        toTargetDestStrategy = new AstarStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        toTargetDestStrategy = new BoosterDecorator(((AstarStrategy*) toTargetDestStrategy) -> decision(this,Stras));
        toTargetDestStrategy = new SpinDecorator(toTargetDestStrategy);
    } else if (targetStrategyName.compare("dfs") == 0){
      printf("dfs\n");
        for(auto each:stations){
          Stras.push_back(new DfsStrategy(nearestEntity->GetPosition(),each->GetPosition(), nearestEntity->GetDestination(), graph));
        }
        toTargetDestStrategy = new DfsStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        toTargetDestStrategy = new BoosterDecorator(((DfsStrategy*) toTargetDestStrategy) -> decision(this,Stras));
        toTargetDestStrategy = new JumpDecorator(toTargetDestStrategy);
    } else if (targetStrategyName.compare("dijkstra") == 0){
        printf("dij\n");
        for(auto each:stations){
          Stras.push_back(new DijkstraStrategy(nearestEntity->GetPosition(),each->GetPosition(), nearestEntity->GetDestination(), graph));
        }
        toTargetDestStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        toTargetDestStrategy = new BoosterDecorator(((DijkstraStrategy*) toTargetDestStrategy) -> decision(this,Stras));
        toTargetDestStrategy = new SpinDecorator(toTargetDestStrategy);
        toTargetDestStrategy = new JumpDecorator(toTargetDestStrategy);
    } 
  }
}

void Drone::Update_Drone(double dt, std::vector<IEntity*> scheduler,std::vector<IEntity*> stations) {
  if (available) {
    GetNearestEntity(scheduler,stations);
  }
  // printf("update drone\n");
  // printf("%d\n",toTargetPosStrategy);

  if(toTargetPosStrategy){
    // printf("beeline,\n");
    // printf("before move\n");
    // this->GetDestination().Print();
    toTargetPosStrategy->Move(this, dt);
    // printf("after move\n");
    // this->GetDestination().Print();
    if(toTargetPosStrategy->IsCompleted()){
      // printf("end of beeline\n");
      delete toTargetPosStrategy;
      toTargetPosStrategy = NULL;
    }
  } else if (toTargetDestStrategy) {
    // printf("%d\n",toTargetDestStrategy);
    // printf("before move\n");
    // this->GetDestination().Print();
    // std::cout<<"before move IS completed "<<toTargetDestStrategy->IsCompleted()<<std::endl;
    toTargetDestStrategy->Move(this, dt);
    // printf("after move\n");
    // this->GetDestination().Print();
    // std::cout<<"after move IS completed "<<toTargetDestStrategy->IsCompleted()<<std::endl;

    // Moving the robot
    nearestEntity->SetPosition(this->GetPosition());
    nearestEntity->SetDirection(this->GetDirection());
    if(toTargetDestStrategy->IsCompleted()){
        printf("delete astar\n");
        delete toTargetDestStrategy;
        toTargetDestStrategy = NULL;
        available = true;
        nearestEntity = NULL;
    }
  }  
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if(goUp){
    position.y += height;
    jumpHeight += height;
    if(jumpHeight > 5){
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if(jumpHeight < 0){
      goUp = true;
    }
  }
}

void Drone::Booster() {
  if (battery > 0) {
    printf("high speed\n");
    speed = highSpeed;
  } else {
    speed = lowSpeed;
  }
}