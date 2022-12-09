#include "BoosterDecorator.h"

bool BoosterDecorator::IsCompleted() {
  return this->CelebrationDecorator::IsCompleted();
}

void BoosterDecorator::Move(IEntity* entity, double dt) {
  if (strategy->IsCompleted() && !IsCompleted()) {
    time = time + dt;
    entity->Booster(dt * 20);
  } else {
    strategy->Move(entity, dt);
  }
}

IStrategy BoosterDecorator::decision(IEntity* entity, IStrategy* direct, std::vector< IStrategy*> s2){ //loop through every station and pick shortest strategy
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

