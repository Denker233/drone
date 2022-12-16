#include "BoosterDecorator.h"

bool BoosterDecorator::IsCompleted() { return strategy->IsCompleted(); }

void BoosterDecorator::Move(IEntity* entity, double dt) {
  if (!strategy->IsCompleted()) {
    // entity->Booster();
    strategy->Move(entity, dt);
  }
}
