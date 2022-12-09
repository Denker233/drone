#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

#include <vector>
#include "graph.h"
#include "IEntity.h"

using namespace routing;

class IStrategy {
    public:
        virtual void Move(IEntity* entity, double dt) = 0;
        virtual bool IsCompleted() = 0;
        IStrategy IStrategy::decision(IEntity* entity, IStrategy* direct, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
            IStrategy MinStrategy;
            int i=0;
            for(EachStrategy:s2){
            if(i==0){
                MinStrategy=EachStrategy;
            }
            if(EachStrategy->TimeSwap(entity,midV3)<MinStrategy->TimeSwap(entity,midV3)){
                MinStrategy=EachStrategy;
            }
            }
            if(MinStrategy->TimeSwap(entity,midV3)>=direct->TimeDirect(entity)){
            return direct;
            }
            return MinStrategy;
        }
        
        float IStrategy::Distance(IEntity* entity){
            Vector3 currentPos = entity->GetPosition();
            float TotalDistance=0;
            for(int i =0; i< maxIndex;i++){
                TotalDistance += PointDistance(Vector3(path[i].at(0), path[i].at(1), path[i].at(2)),Vector3(path[i+1].at(0), path[i+1].at(1), path[i+1].at(2)))
            }
            return TotalDistance;
        }

        float IStrategy::TimeDirect(IEntity* entity){
            if(entity->battery>this->Distance){
                return this->Distance/entity->GetSpeed();
            }
            else{
                return entity->battery/entity->GetSpeed()+(this->Distance-entity->battery)/(entity->GetSpeed()/2);
            }
        }

        float IStrategy::TimeSwap(IEntity* entity,Vector3* SwapStation){
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
    protected:
        // IGraph object to be used in the simulation.
        const IGraph* graph;
}; //close class 

#endif // ISTRATEGY_H_