#include "BoosterDecorator.h"

// bool BoosterDecorator::IsCompleted() {
//   return this->CelebrationDecorator::IsCompleted();
// }

void BoosterDecorator::Move(IEntity* entity, double dt) {
  if (!strategy->IsCompleted()) {
    time = time + dt;
    entity->Booster(dt * 20);
    strategy->Move(entity, dt);
  }
}

//modify completetd to check battery distance
//booster: speed up 


