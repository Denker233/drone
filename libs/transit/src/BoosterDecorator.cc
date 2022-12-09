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

AstarStrategy BoosterDecorator::decision(AstarStrategy* direct, std::vector< AstarStrategy*> s2){ //loop through every station and pick shortest strategy
    AstarStrategy MaxAstar = direct;
    for(EachAstar:s2){
      if(EachAstar->TimeSwap()>MaxAstar->TimeSwap()){
        MaxAstar=EachAstar;
      }
    }
    return MaxAstar;
}

