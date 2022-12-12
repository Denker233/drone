#ifndef BOOSTER_DECORATOR_H_
#define BOOSTER_DECORATOR_H_

#include <vector>

#include "IStrategy.h"

class BoosterDecorator : public IStrategy {
 public:
  BoosterDecorator(IStrategy* strategy_) {
    strategy = strategy_;
    time = 0;
  };
   
  bool IsCompleted(){};
  void Move(IEntity* entity, double dt);
  float TimeSwap(IEntity* entity,Vector3* SwapStation){};

 protected: 
  IStrategy *strategy;
  float time;
};  // close class

#endif  // BOOSTER_DECORATOR_H_