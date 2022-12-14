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
    
    std::vector<std::vector<float>> path = graph->GetPath(start, midpoint, AStar::Default());
    std::vector<std::vector<float>> path_2 = graph->GetPath( midpoint, end, AStar::Default());
    path.insert(path.end(),path_2.begin(), path_2.end());

    currentIndex = 0;
    maxIndex = path.size()-1;
}

bool AstarStrategy::IsCompleted(){
    std::cout<<currentIndex<<" and "<<maxIndex<<"in is completed"<<std::endl;
    return currentIndex == maxIndex;
}

void AstarStrategy::Move(IEntity* entity, double dt){
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
    if(entity->GetType().compare("drone")==0){
    printf("astar move\n");
    std::cout<<currentIndex<<" and "<<maxIndex<<std::endl;
    }
    // entity->SetBattery(entity->GetBattery()-currentPos.Distance(oldPos)); //update battery
    // if(entity->GetBattery()<0){
    //     entity->SetBattery(0);
    // }
    entity->SetPosition(currentPos);
    if(entity->GetType().compare("drone")==0){
    printf("after set pos\n");
    std::cout<<currentIndex<<" and "<<maxIndex<<std::endl;
    }
    
    entity->SetDirection(direction);
    
    if(entity->GetType().compare("drone")==0){
    printf("after set dir\n");
    std::cout<<currentIndex<<" and "<<maxIndex<<std::endl;
    }
    if((destination - currentPos).Magnitude()<3.0){
        currentIndex++;
    }
    if(entity->GetType().compare("drone")==0){
    printf("astar move\n");
    std::cout<<currentIndex<<" and "<<maxIndex<<std::endl;
    printf("after update current\n");
    }
}
AstarStrategy* AstarStrategy::decision(IEntity* entity, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
            AstarStrategy* MinStrategy = this;
            int i=0;
            for(auto EachStrategy:s2){
            if(i==0){
                MinStrategy = (AstarStrategy*) EachStrategy;
            }
            if(EachStrategy->TimeSwap(entity)<MinStrategy->TimeSwap(entity)){
                MinStrategy = (AstarStrategy*) EachStrategy;
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

float AstarStrategy::RealDistance(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            float TotalDistance=0;
            for(int i =0; i< maxIndex;i++){
                TotalDistance += Vector3(path[i].at(0), path[i].at(1), path[i].at(2)).Distance(Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)));
            }
            return TotalDistance;
        }

float AstarStrategy::TimeDirect(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            if(entity->GetBattery()>entity->GetDestination().Distance(entity->GetDestination())){
                return currentPos.Distance(entity->GetDestination())/entity->GetHighSpeed();
            }
            else{
                return entity->GetBattery()/entity->GetSpeed()+(currentPos.Distance(entity->GetDestination())-entity->GetBattery())/(entity->GetLowSpeed());
            }
        }
float AstarStrategy::TimeSwap(IEntity* entity){
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

