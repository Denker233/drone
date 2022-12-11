#include "DfsStrategy.h"
#include "routing/depth_first_search.h"
#include "routing_api.h"
#include "graph.h"
using namespace routing;

DfsStrategy::DfsStrategy(Vector3 position, Vector3 destination, const IGraph* graph) {
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
    
    path = graph->GetPath(start, end, DepthFirstSearch::Default());
    currentIndex = 0;
    maxIndex = path.size()-1;
}

bool DfsStrategy::IsCompleted(){
    return currentIndex == maxIndex;
}

void DfsStrategy::Move(IEntity* entity, double dt){
    std::string type = entity["type"];
    Vector3 currentPos = entity->GetPosition();
    Vector3 oldPos = entity->GetPosition();
    Vector3 destination = Vector3(path[currentIndex].at(0), path[currentIndex].at(1), path[currentIndex].at(2));
    Vector3 direction = (destination - currentPos).Unit();
    float speed = entity->GetSpeed(); 
    currentPos = currentPos + direction * speed * dt;
    if(type.compare("drone")==0){
        entity->SetBattery(entity->GetBattery()-PointDistance(position,oldPos); //update battery
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

DfsStrategy::decision(IEntity* entity, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
            IStrategy MinStrategy = new ;
            int i=0;
            for(EachStrategy:s2){
            if(i==0){
                MinStrategy=EachStrategy;
            }
            if(EachStrategy->TimeSwap(entity,midV3)<MinStrategy->TimeSwap(entity,midV3)){
                MinStrategy=EachStrategy;
            }
            }
            if(MinStrategy->TimeSwap(entity,midV3)>=this->TimeDirect(entity)){
            return this;
            }
            return MinStrategy;
}

float DfsStrategy::Distance(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            float TotalDistance=0;
            for(int i =0; i< maxIndex;i++){
                TotalDistance += PointDistance(Vector3(path[i].at(0), path[i].at(1), path[i].at(2)),Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)))
            }
            return TotalDistance;
        }

float DfsStrategy::TimeDirect(IEntity* entity){
            if(entity->GetBattery()>this->Distance(entity)){
                return this->Distance(entity)/entity->GetSpeed();
            }
            else{
                return entity->GetBattery()/entity->GetSpeed()+(this->Distance(entity)-entity->GetBattery())/(entity->GetSpeed()/2);
            }
        }
float DfsStrategy::TimeSwap(IEntity* entity,Vector3* SwapStation){
            Vector3 currentPos = entity->GetPosition();
            float DistanceToSwap = PointsDistance(currentPos,SwapStation);
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

