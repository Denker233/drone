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
        virtual float TimeSwap(IEntity* entity,Vector3* SwapStation){};
        IStrategy* decision(IEntity* entity, std::vector< IStrategy*> s2){};

    protected:
        // IGraph object to be used in the simulation.
        const IGraph* graph;
}; //close class 

#endif // ISTRATEGY_H_