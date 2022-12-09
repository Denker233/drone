#include "AstarStrategy.h"
#include "routing/astar.h"
#include "routing_api.h"
#include "graph.h"
using namespace routing;

AstarStrategy::AstarStrategy(Vector3 position, Vector3 destination, const IGraph* graph) {
    this->graph = graph;

    std::vector<float> positionV;
    positionV.push_back(position.x);
    positionV.push_back(position.y);
    positionV.push_back(position.z);
    
    std::vector<float> destinationV;
    destinationV.push_back(destination.x);
    destinationV.push_back(destination.y);
    destinationV.push_back(destination.z);

    std::vector<float> start = graph->NearestNode(positionV, EuclideanDistance())->GetPosition();
    std::vector<float> end = graph->NearestNode(destinationV, EuclideanDistance())->GetPosition();
    
    path = graph->GetPath(start, end, AStar::Default());
    currentIndex = 0;
    maxIndex = path.size()-1;
}

AstarStrategy::AstarStrategy(Vector3 position, Vector3 mid, Vector3 destination, const IGraph* graph) {
    this->graph = graph;

    std::vector<float> positionV;
    positionV.push_back(position.x);
    positionV.push_back(position.y);
    positionV.push_back(position.z);

    std::vector<float> midV;
    midV3=mid;
    midV.push_back(position.x);
    midV.push_back(position.y);
    midV.push_back(position.z);
    
    std::vector<float> destinationV;
    destinationV.push_back(destination.x);
    destinationV.push_back(destination.y);
    destinationV.push_back(destination.z);

    std::vector<float> start = graph->NearestNode(positionV, EuclideanDistance())->GetPosition();
    std::vector<float> midpoint = graph->NearestNode(midV, EuclideanDistance())->GetPosition();
    std::vector<float> end = graph->NearestNode(destinationV, EuclideanDistance())->GetPosition();
    
    std::vector<std::vector<float>> path_1 = graph->GetPath(start, midpoint, AStar::Default());
    std::vector<std::vector<float>> path_2 = graph->GetPath( midpoint, end, AStar::Default());
    path_1.insert(path_1.end(),path_2.begin(), path_2.end());

    currentIndex = 0;
    maxIndex = path.size()-1;
}

bool AstarStrategy::IsCompleted(){
    return currentIndex == maxIndex;
}

void AstarStrategy::Move(IEntity* entity, double dt){
    Vector3 currentPos = entity->GetPosition();
    Vector3 destination = Vector3(path[currentIndex].at(0), path[currentIndex].at(1), path[currentIndex].at(2));
    Vector3 direction = (destination - currentPos).Unit();
    float speed = entity->GetSpeed(); 
    currentPos = currentPos + direction * speed * dt;
    entity->SetPosition(currentPos);
    entity->SetDirection(direction);
    
    if((destination - currentPos).Magnitude()<1.0){
        currentIndex++;
    }
}

float AstarStrategy::Distance(IEntity* entity){
    Vector3 currentPos = entity->GetPosition();
    float TotalDistance=0;
    for(int i =0; i< maxIndex;i++){
        TotalDistance += PointDistance(Vector3(path[i].at(0), path[i].at(1), path[i].at(2)),Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)))
    }
    return TotalDistance;
}

float AstarStrategy::TimeDirect(IEntity* entity){
    if(entity->battery>this->Distance){
        return this->Distance/entity->GetSpeed();
    }
    else{
        return entity->battery/entity->GetSpeed()+(this->Distance-entity->battery)/(entity->GetSpeed()/2);
    }
}

float AstarStrategy::TimeSwap(IEntity* entity,Vector3* SwapStation){
    Vector3 currentPos = entity->GetPosition();
    float DistanceToSwap = PointsDistance(currentPos,SwapStation);
    if(entity->battery>DistanceToSwap){
        return this->Distance/entity->GetSpeed();
    }
    else if (battery){
        return entity->battery/entity->GetSpeed()+(DistanceToSwap-entity->battery)/(entity->GetSpeed()/2)+(this->Distance-DistanceToSwap)/(entity->GetSpeed());
    }
    else{
        return DistanceToSwap/entity->GetSpeed()+(this->Distance-DistanceToSwap)/(entity->GetSpeed()*2);
    }
}