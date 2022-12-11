#include "math/vector3.h"
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
    std::string type = entity["type"];
    Vector3 currentPos = entity->GetPosition();
    Vector3 oldPos = entity->GetPosition();
    Vector3 destination = Vector3(path[currentIndex].at(0), path[currentIndex].at(1), path[currentIndex].at(2));
    Vector3 direction = (destination - currentPos).Unit();
    float speed = entity->GetSpeed(); 
    currentPos = currentPos + direction * speed * dt;
    if(type.compare("drone")==0){
        entity->SetBattery(entity->GetBattery()-currentPos.Distance(oldPos)); //update battery
        if(entity->GetBattery()<0){
            entity->SetBattery(0);
        }
    }
    entity->SetPosition(currentPos);
    entity->SetDirection(direction);
    
    if((destination - currentPos).Magnitude()<1.0){
        currentIndex++;
    }
}
AstarStrategy AstarStrategy::decision(IEntity* entity, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
            AstarStrategy MinStrategy =this;
            int i=0;
            for(auto EachStrategy:s2){
            if(i==0){
                MinStrategy=EachStrategy;
            }
            if(EachStrategy->TimeSwap(entity,&midV3)<MinStrategy->TimeSwap(entity,&midV3)){
                MinStrategy=EachStrategy;
            }
            }
            if(MinStrategy->TimeSwap(entity,&midV3)>=this->TimeDirect(entity)){
            return *this;
            }
            return *MinStrategy;
}

float AstarStrategy::Distance(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            float TotalDistance=0;
            for(int i =0; i< maxIndex;i++){
                TotalDistance += Vector3(path[i].at(0), path[i].at(1), path[i].at(2))->PointDistance(Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)));
            }
            return TotalDistance;
        }

float AstarStrategy::TimeDirect(IEntity* entity){
            if(entity->GetBattery()>this->Distance(entity)){
                return this->Distance(entity)/entity->GetSpeed();
            }
            else{
                return entity->GetBattery()/entity->GetSpeed()+(this->Distance(entity)-entity->GetBattery())/(entity->GetSpeed()/2);
            }
        }
float AstarStrategy::TimeSwap(IEntity* entity,Vector3* SwapStation){
            Vector3 currentPos = entity->GetPosition();
            float DistanceToSwap = currentPos.Distance(*SwapStation);
            if(entity->GetBattery()>DistanceToSwap){
                return this->Distance(entity)/entity->GetSpeed();
            }
            else if (entity->GetBattery()){
                return entity->GetBattery()/entity->GetSpeed()+(DistanceToSwap-entity->GetBattery())/(entity->GetSpeed()/2)+(this->Distance(entity)-DistanceToSwap)/(entity->GetSpeed());
            }
            else{
                return DistanceToSwap/entity->GetSpeed()+(this->Distance(entity)-DistanceToSwap)/(entity->GetSpeed()*2);
            }
}        

