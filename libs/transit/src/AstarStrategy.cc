#include "AstarStrategy.h"

#include "graph.h"
#include "math/vector3.h"
#include "routing/astar.h"
#include "routing_api.h"
using namespace routing;

AstarStrategy::AstarStrategy(Vector3 position, Vector3 destination,
                             const IGraph* graph) {
  this->graph = graph;

  std::vector<float> positionV;
  positionV.push_back(position.x);
  positionV.push_back(position.y);
  positionV.push_back(position.z);

  std::vector<float> destinationV;
  destinationV.push_back(destination.x);
  destinationV.push_back(destination.y);
  destinationV.push_back(destination.z);

  std::vector<float> start =
      graph->NearestNode(positionV, EuclideanDistance())->GetPosition();
  std::vector<float> end =
      graph->NearestNode(destinationV, EuclideanDistance())->GetPosition();

  path = graph->GetPath(start, end, AStar::Default());
  currentIndex = 0;
  maxIndex = path.size() - 1;
}

AstarStrategy::AstarStrategy(Vector3 position, Vector3 mid, Vector3 destination,
                             const IGraph* graph) {
  this->graph = graph;

  std::vector<float> positionV;
  positionV.push_back(position.x);
  positionV.push_back(position.y);
  positionV.push_back(position.z);

  std::vector<float> midV;
  midV3 = mid;
  printf("constructure\n");
  midV3.Print();
  midV.push_back(mid.x);
  midV.push_back(mid.y);
  midV.push_back(mid.z);

  std::vector<float> destinationV;
  destinationV.push_back(destination.x);
  destinationV.push_back(destination.y);
  destinationV.push_back(destination.z);

  std::vector<float> start =
      graph->NearestNode(positionV, EuclideanDistance())->GetPosition();
  std::vector<float> midpoint =
      graph->NearestNode(midV, EuclideanDistance())->GetPosition();
  std::vector<float> end =
      graph->NearestNode(destinationV, EuclideanDistance())->GetPosition();

  path_station = graph->GetPath(start, midpoint, AStar::Default());
  path_2 = graph->GetPath(midpoint, end, AStar::Default());
  path = path_station;
  path.insert(path.end(), path_2.begin(), path_2.end());

  currentIndex = 0;
  maxIndex = path.size() - 1;
}

bool AstarStrategy::IsCompleted() { return currentIndex == maxIndex; }

void AstarStrategy::Move(IEntity* entity, double dt) {
  std::string type = entity->GetType();
  Vector3 currentPos = entity->GetPosition();
  if (((currentPos - midV3).Magnitude() < 80.0) && midV3.Magnitude() != 0) {
    printf("station arrive\n");
    std::cout << type << std::endl;
    entity->SetBattery(1000);
  }
  Vector3 oldPos = entity->GetPosition();
  Vector3 destination =
      Vector3(path[currentIndex].at(0), path[currentIndex].at(1),
              path[currentIndex].at(2));
  Vector3 direction = (destination - currentPos).Unit();
  float speed = entity->GetSpeed();
  currentPos = currentPos + direction * speed * dt;
  if (type.compare("drone") == 0) {
    entity->SetBattery(entity->GetBattery() -
                       currentPos.Distance(oldPos));  // update battery
    if (entity->GetBattery() < 0) {
      entity->SetBattery(0);
    }
  }

  entity->SetPosition(currentPos);

  entity->SetDirection(direction);

  if ((destination - currentPos).Magnitude() < 2.0) {
    currentIndex++;
  }
}
AstarStrategy* AstarStrategy::decision(
    IEntity* entity,
    std::vector<IStrategy*>
        s2) {  // loop through every station and pick shortest strategy
  printf("decision\n");
  AstarStrategy* MinStrategy = this;
  int i = 0;
  for (auto EachStrategy : s2) {
    if (i == 0) {
      MinStrategy = reinterpret_cast<AstarStrategy*>(EachStrategy);
    }
    if (EachStrategy->TimeSwap(entity) < MinStrategy->TimeSwap(entity)) {
      printf("better solution\n");
      MinStrategy = reinterpret_cast<AstarStrategy*>(EachStrategy);
    }
  }
  if (MinStrategy->TimeSwap(entity) >= this->TimeDirect(entity)) {
    std::cout << "Minstrategy time:" << MinStrategy->TimeSwap(entity)
              << "and direct time: " << this->TimeDirect(entity) << std::endl;
    std::cout << entity->GetBattery() << std::endl;
    printf("no swap\n");
    return this;
  }
  printf("swap\n");

  std::cout << "Minstrategy time:" << MinStrategy->TimeSwap(entity)
            << "and direct time: " << this->TimeDirect(entity) << std::endl;
  printf("MinStrategy's chosen station\n");
  return MinStrategy;
}

float AstarStrategy::RealDistance(
    std::vector<std::vector<float>> path) {  // no need can delete later
  int size = path.size() - 1;
  float TotalDistance = 0;
  for (int i = 0; i < size - 1; i++) {
    TotalDistance += Vector3(path[i].at(0), path[i].at(1), path[i].at(2))
                         .Distance(Vector3(path[i + 1].at(0), path[i + 1].at(1),
                                           path[i + 1].at(2)));
  }
  return TotalDistance;
}

float AstarStrategy::TimeDirect(IEntity* entity) {
  printf("time direct\n");
  Vector3 currentPos = entity->GetPosition();
  if (entity->GetBattery() > this->RealDistance(path)) {
    printf("direct branch1\n");
    return this->RealDistance(path) / entity->GetHighSpeed();
  } else if (entity->GetBattery()) {
    printf("direct branch2\n");
    return entity->GetBattery() / entity->GetHighSpeed() +
           (this->RealDistance(path) - entity->GetBattery()) /
               (entity->GetLowSpeed());
  } else {
    printf("direct branch3\n");
    std::cout << "path_sta" << this->RealDistance(path_station) << std::endl;
    std::cout << "path_sta_des" << this->RealDistance(path_2) << std::endl;
    std::cout << "path_over_all" << this->RealDistance(path) << std::endl;
    return this->RealDistance(path) / entity->GetLowSpeed();
  }
}
float AstarStrategy::TimeSwap(IEntity* entity) {
  Vector3 currentPos = entity->GetPosition();
  float DistanceToSwap = this->RealDistance(path_station);
  float DistanceSwapToDes = this->RealDistance(path_2);
  float TotalDistance = this->RealDistance(path);
  float time;
  if (entity->GetBattery() > TotalDistance ||
      (entity->GetBattery() > DistanceToSwap && 1000 >= DistanceSwapToDes)) {
    printf("swap branch1\n");
    time = TotalDistance / entity->GetHighSpeed();
    std::cout << time << std::endl;
    return time;
  } else if (entity->GetBattery() >= DistanceToSwap &&
             1000 < DistanceSwapToDes) {
    printf("swap branch2\n");
    time = DistanceToSwap / entity->GetHighSpeed() +
           1000 / entity->GetHighSpeed() +
           (1000 - DistanceSwapToDes) / (entity->GetLowSpeed());
    std::cout << time << std::endl;
    return time;
  } else if (entity->GetBattery() < DistanceToSwap &&
             1000 >= DistanceSwapToDes) {
    printf("swap branch3\n");
    time = entity->GetBattery() / entity->GetHighSpeed() +
           (DistanceToSwap - entity->GetBattery()) / entity->GetLowSpeed() +
           DistanceSwapToDes / entity->GetHighSpeed();
    std::cout << time << std::endl;
    return time;
  } else {
    time = entity->GetBattery() / entity->GetHighSpeed() +
           (DistanceToSwap - entity->GetBattery()) / entity->GetLowSpeed() +
           1000 / entity->GetHighSpeed() +
           (1000 - DistanceSwapToDes) / (entity->GetLowSpeed());
    std::cout << time << std::endl;
    return time;
  }
}
