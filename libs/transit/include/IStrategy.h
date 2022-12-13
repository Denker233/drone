#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

#include <vector>
#include "math/vector3.h"
#include "graph.h"
#include "IEntity.h"

using namespace routing;

class IStrategy {
    public:
        virtual void Move(IEntity* entity, double dt) = 0;
        virtual bool IsCompleted() = 0;
        virtual float TimeSwap(IEntity* entity){};
        IStrategy* decision(IEntity* entity, std::vector< IStrategy*> s2){}
//             IStrategy* MinStrategy = this;
//             int i=0;
//             for(auto EachStrategy:s2){
//             if(i==0){
//                 MinStrategy =  EachStrategy;
//             }
//             if(EachStrategy->TimeSwap(entity,&midV3)<MinStrategy->TimeSwap(entity,&midV3)){
//                 MinStrategy =  EachStrategy;
//             }
//             }
//             if(MinStrategy->TimeSwap(entity,&midV3)>=this->TimeDirect(entity)){
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
//         }
//         float Distance(IEntity* entity){
//             Vector3 currentPos = entity->GetPosition();
//             float TotalDistance=0;
//             for(int i =0; i< maxIndex;i++){
//                 TotalDistance += Vector3(path[i].at(0), path[i].at(1), path[i].at(2)).Distance(Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)));
//             }
//             return TotalDistance;
//         }
//         float TimeDirect(IEntity* entity){
//             Vector3 currentPos = entity->GetPosition();
//             if(entity->GetBattery()>entity->GetDestination().Distance(entity->GetDestination())){
//                 return currentPos.Distance(entity->GetDestination())/entity->GetSpeed();
//             }
//             else{
//                 return entity->GetBattery()/entity->GetSpeed()+(currentPos.Distance(entity->GetDestination())-entity->GetBattery())/(entity->GetSpeed()/2);
//             }
//         }
//         float TimeSwap(IEntity* entity,Vector3* SwapStation){
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


    protected:
        // IGraph object to be used in the simulation.
        const IGraph* graph;
}; //close class 

#endif // ISTRATEGY_H_