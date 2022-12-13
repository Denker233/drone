#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 position, Vector3 destination) {
    this->position = position;
    this->destination = destination;
}

bool BeelineStrategy::IsCompleted(){
    return (destination - position).Magnitude()<1.0;
}

void BeelineStrategy::Move(IEntity* entity, double dt){
    std::string type = entity->GetType();
    position = entity->GetPosition();
    Vector3 oldPos = entity->GetPosition();
    Vector3 dir = (destination - position).Unit();
    float speed = entity->GetSpeed(); 
    position = position + dir * speed * dt;
    // if(type.compare("drone")==0){
    //     entity->SetBattery(entity->GetBattery()-position.Distance(oldPos)); //update battery
    //     if(entity->GetBattery()<0){
    //         entity->SetBattery(0);
    //     }
    // }
    entity->SetPosition(position);
    entity->SetDirection(dir);
}

// BeelineStrategyy* BeelineStrategy::decision(IEntity* entity, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
//             DijkstraStrategy* MinStrategy = this;
//             int i=0;
//             for(auto EachStrategy:s2){
//             if(i==0){
//                 MinStrategy = (DijkstraStrategy*) EachStrategy;
//             }
//             if(EachStrategy->TimeSwap(entity)<MinStrategy->TimeSwap(entity)){
//                 MinStrategy = (DijkstraStrategy*) EachStrategy;
//             }
//             }
//             if(MinStrategy->TimeSwap(entity)>=this->TimeDirect(entity)){
//                 for(auto EachStrategy:s2){
//                     delete(EachStrategy);
//                 }
//                 return this;
//             }
//             for(auto EachStrategy:s2){
//                 if(EachStrategy!=MinStrategy){
//                   delete(EachStrategy);
//                 }
//             }
//             return MinStrategy;
// }

// float BeelineStrategy::Distance(IEntity* entity){
//             Vector3 currentPos = entity->GetPosition();
//             float TotalDistance=0;
//             for(int i =0; i< maxIndex;i++){
//                 TotalDistance += Vector3(path[i].at(0), path[i].at(1), path[i].at(2)).Distance(Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)));
//             }
//             return TotalDistance;
//         }

// float BeelineStrategy::TimeDirect(IEntity* entity){
//             Vector3 currentPos = entity->GetPosition();
//             if(entity->GetBattery()>entity->GetDestination().Distance(entity->GetDestination())){
//                 return currentPos.Distance(entity->GetDestination())/entity->GetSpeed();
//             }
//             else{
//                 return entity->GetBattery()/entity->GetSpeed()+(currentPos.Distance(entity->GetDestination())-entity->GetBattery())/(entity->GetSpeed()/2);
//             }
//         }
// float BeelineStrategy::TimeSwap(IEntity* entity){
//             Vector3 currentPos = entity->GetPosition();
//             float DistanceToSwap = currentPos.Distance(*SwapStation);
//             if(entity->GetBattery()>DistanceToSwap){
//                 return currentPos.Distance(entity->GetDestination())/entity->GetSpeed();
//             }
//             else if (entity->GetBattery()){
//                 return entity->GetBattery()/entity->GetSpeed()+(DistanceToSwap-entity->GetBattery())/(entity->GetSpeed()/2)+(currentPos.Distance(entity->GetDestination())-DistanceToSwap)/(entity->GetSpeed());
//             }
//             else{
//                 return DistanceToSwap/entity->GetSpeed()+(currentPos.Distance(entity->GetDestination())-DistanceToSwap)/(entity->GetSpeed()*2);
//             }
// }        