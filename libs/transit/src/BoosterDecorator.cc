#include "BoosterDecorator.h"

bool BoosterDecorator::IsCompleted() {
  return strategy->IsCompleted();
}

void BoosterDecorator::Move(IEntity* entity, double dt) {
  if (!strategy->IsCompleted()) {
    time = time + dt;
    entity->Booster();
    strategy->Move(entity, dt);
  }
}

//modify completetd to check battery distance
//booster: speed up 


