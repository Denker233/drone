#include "math/vector3.h"
#include "DijkstraStrategy.h"
#include "routing/dijkstra.h"
#include "routing_api.h"
#include "graph.h"
using namespace routing;

DijkstraStrategy::DijkstraStrategy(Vector3 position, Vector3 destination, const IGraph* graph) {
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
    
    path = graph->GetPath(start, end, Dijkstra::Default());
    currentIndex = 0;
    maxIndex = path.size()-1;
}

DijkstraStrategy::DijkstraStrategy(Vector3 position, Vector3 mid, Vector3 destination, const IGraph* graph) {
    this->graph = graph;

    std::vector<float> positionV;
    positionV.push_back(position.x);
    positionV.push_back(position.y);
    positionV.push_back(position.z);

    std::vector<float> midV;
    midV3=mid;
    midV.push_back(mid.x);
    midV.push_back(mid.y);
    midV.push_back(mid.z);
    
    std::vector<float> destinationV;
    destinationV.push_back(destination.x);
    destinationV.push_back(destination.y);
    destinationV.push_back(destination.z);

    std::vector<float> start = graph->NearestNode(positionV, EuclideanDistance())->GetPosition();
    std::vector<float> midpoint = graph->NearestNode(midV, EuclideanDistance())->GetPosition();
    std::vector<float> end = graph->NearestNode(destinationV, EuclideanDistance())->GetPosition();
    
    std::vector<std::vector<float>> path_1 = graph->GetPath(start, midpoint, Dijkstra::Default());
    std::vector<std::vector<float>> path_2 = graph->GetPath( midpoint, end, Dijkstra::Default());
    path_1.insert(path_1.end(),path_2.begin(), path_2.end());
    path=path_1;

    currentIndex = 0;
    maxIndex = path.size()-1;
}

bool DijkstraStrategy::IsCompleted(){
    return currentIndex == maxIndex;
}

void DijkstraStrategy::Move(IEntity* entity, double dt){
    std::string type = entity->GetType();
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
    // entity->SetBattery(entity->GetBattery()-currentPos.Distance(oldPos)); //update battery
    // if(entity->GetBattery()<0){
    //     entity->SetBattery(0);
    // }
    entity->SetPosition(currentPos);
    entity->SetDirection(direction);
    
    if((destination - currentPos).Magnitude()<1.0){
        currentIndex++;
    }
}

DijkstraStrategy* DijkstraStrategy::decision(IEntity* entity, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
            DijkstraStrategy* MinStrategy = this;
            int i=0;
            for(auto EachStrategy:s2){
            if(i==0){
                MinStrategy = (DijkstraStrategy*) EachStrategy;
            }
            if(EachStrategy->TimeSwap(entity)<MinStrategy->TimeSwap(entity)){
                MinStrategy = (DijkstraStrategy*) EachStrategy;
            }
            }
            if(MinStrategy->TimeSwap(entity)>=this->TimeDirect(entity)){
                for(auto EachStrategy:s2){
                    delete(EachStrategy);
                }
                return this;
            }
            for(auto EachStrategy:s2){
                if(EachStrategy!=MinStrategy){
                  delete(EachStrategy);
                }
            }
            return MinStrategy;
}

float DijkstraStrategy::RealDistance(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            float TotalDistance=0;
            for(int i =0; i< maxIndex;i++){
                TotalDistance += Vector3(path[i].at(0), path[i].at(1), path[i].at(2)).Distance(Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)));
            }
            return TotalDistance;
        }

float DijkstraStrategy::TimeDirect(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            if(entity->GetBattery()>entity->GetDestination().Distance(entity->GetDestination())){
                return currentPos.Distance(entity->GetDestination())/entity->GetHighSpeed();
            }
            else{
                return entity->GetBattery()/entity->GetSpeed()+(currentPos.Distance(entity->GetDestination())-entity->GetBattery())/(entity->GetLowSpeed());
            }
        }
float DijkstraStrategy::TimeSwap(IEntity* entity){
          Vector3 currentPos = entity->GetPosition();
            float DistanceToSwap = this->RealDistance(entity);
            if(entity->GetBattery()>DistanceToSwap){
                return currentPos.Distance(entity->GetDestination())/entity->GetHighSpeed();
            }
            else if (entity->GetBattery()){
                return entity->GetBattery()/entity->GetHighSpeed()+(DistanceToSwap-entity->GetBattery())/(entity->GetLowSpeed());
            }
            else{
                return DistanceToSwap/entity->GetLowSpeed();
            }
}        
