#ifndef Dijkstra_STRATEGY_H_
#define Dijkstra_STRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "IEntity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class DijkstraStrategy : public IStrategy {
public:
    DijkstraStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
    DijkstraStrategy(Vector3 position, Vector3 mid, Vector3 destination, const IGraph* graph);
    ~DijkstraStrategy();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();
    DijkstraStrategy* decision(IEntity* entity, std::vector< IStrategy*> s2);
    float RealDistance();
    float TimeDirect(IEntity* entity);
    float TimeSwap(IEntity* entity);

private:
    std::vector<std::vector<float>> path;
    std::vector<std::vector<float>> path_station;
    std::vector<std::vector<float>> path_2;
    int currentIndex;
    int maxIndex;
    Vector3 midV3 = {0,0,0};
}; //end class
#endif // Dijkstra_STRATEGY_H_