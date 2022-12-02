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

AstarStrategy AstarStrategy::decision(AstarStrategy* s1,AstarStrategy* s2){
    
}