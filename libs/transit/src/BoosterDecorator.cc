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

AstarStrategy BoosterDecorator::decision(IEntity* entity,AstarStrategy* direct, std::vector< AstarStrategy*> s2){ //loop through every station and pick shortest strategy
    AstarStrategy MaxAstar;
    int i=0;
    for(EachAstar:s2){
      if(i==0){
        MaxAstar=EachAstar;
      }
      if(EachAstar->TimeSwap(entity,midV3)>MaxAstar->TimeSwap(entity,midV3)){
        MaxAstar=EachAstar;
      }
    }
    if(MaxAsar->TimeSwap(entity,midV3)>=direct->TimeDirect(entity)){
      return MaxAstar;
    }
    return direct;
}

