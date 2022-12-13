#define _USE_MATH_DEFINES
#include "Drone.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "SpinDecorator.h"
#include "JumpDecorator.h"
#include "BoosterDecorator.h"
#include "SimulationModel.cc"
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

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
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
    Vector3 p1 = Vector3(200,300,5);
    Vector3 p2 = Vector3(700,300,5);
    nearestEntity->SetAvailability(false);  // set availability to the nearest entity
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();
    std::cout << "test - drone.cc line 54" << std::endl;
    nearestEntity->GetPosition().Print();

    // for(auto each:stations){
    //   Stras.push_back(new BeelineStrategy(nearestEntity->GetPosition(),each->GetPosition(), nearestEntity->GetDestination(), graph));
    // }
    toTargetPosStrategy = new BeelineStrategy(this->GetPosition(), destination);
    // toTargetPosStrategy = new BoosterDecorator(toTargetPosStrategy->decision(this,Stras));
    std::string targetStrategyName = nearestEntity->GetStrategyName();
    if(targetStrategyName.compare("astar") == 0){
        std::cout << "test - drone.cc line 64" << std::endl;
        nearestEntity->GetPosition().Print();
        printf("astar\n");
        Stras.push_back(new AstarStrategy(nearestEntity->GetPosition(),p1, nearestEntity->GetDestination(), graph));
        Stras.push_back(new AstarStrategy(nearestEntity->GetPosition(),p2, nearestEntity->GetDestination(), graph));
        std::cout << "test - drone.cc line 70" << std::endl;
        nearestEntity->GetPosition().Print();
        toTargetDestStrategy = new AstarStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        std::cout << "test - drone.cc line 73" << std::endl;
        nearestEntity->GetPosition().Print();
        toTargetDestStrategy = new BoosterDecorator(((AstarStrategy*) toTargetDestStrategy) -> decision(this,Stras));
        std::cout << "test - drone.cc line 74" << std::endl;
        nearestEntity->GetPosition().Print();
    } else if (targetStrategyName.compare("dfs") == 0){
      printf("dfs\n");
        Stras.push_back(new DfsStrategy(nearestEntity->GetPosition(),p1, nearestEntity->GetDestination(), graph));
        Stras.push_back(new DfsStrategy(nearestEntity->GetPosition(),p2, nearestEntity->GetDestination(), graph));
        toTargetDestStrategy = new DfsStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        toTargetDestStrategy = new BoosterDecorator(((DfsStrategy*) toTargetDestStrategy) -> decision(this,Stras));
    } else if (targetStrategyName.compare("dijkstra") == 0){
        printf("dij\n");
        Stras.push_back(new DijkstraStrategy(nearestEntity->GetPosition(),p1, nearestEntity->GetDestination(), graph));
        Stras.push_back(new DijkstraStrategy(nearestEntity->GetPosition(),p2, nearestEntity->GetDestination(), graph));
        toTargetDestStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
        toTargetDestStrategy = new BoosterDecorator(((DijkstraStrategy*) toTargetDestStrategy) -> decision(this,Stras));
    } 
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  if (available) {
    GetNearestEntity(scheduler);
  }

  if(toTargetPosStrategy){
    //printf("beeline,\n");
    toTargetPosStrategy->Move(this, dt);
    if(toTargetPosStrategy->IsCompleted()){
      delete toTargetPosStrategy;
      printf("inside complete\n");
      toTargetPosStrategy = NULL;
    }
  } else if (toTargetDestStrategy) {
    toTargetDestStrategy->Move(this, dt);
    
    // Moving the robot
    nearestEntity->SetPosition(this->GetPosition());
    nearestEntity->SetDirection(this->GetDirection());
    if(toTargetDestStrategy->IsCompleted()){
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
    speed = highSpeed;
  } else {
    speed = lowSpeed;
  }
}