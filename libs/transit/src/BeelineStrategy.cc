#include "BeelineStrategy.h"

BeelineStrategy::BeelineStrategy(Vector3 position, Vector3 destination) {
    this->position = position;
    this->destination = destination;
}

bool BeelineStrategy::IsCompleted(){
    return (destination - position).Magnitude()<1.0;
}

void BeelineStrategy::Move(IEntity* entity, double dt){
    std::string type = entity->GetType();
    position = entity->GetPosition();
    Vector3 oldPos = entity->GetPosition();
    Vector3 dir = (destination - position).Unit();
    float speed = entity->GetSpeed(); 
    position = position + dir * speed * dt;
    if(type.compare("drone")==0){
        entity->SetBattery(entity->GetBattery()-position.Distance(oldPos)); //update battery
        if(entity->GetBattery()<0){
            entity->SetBattery(0);
        }
    }
    entity->SetPosition(position);
    entity->SetDirection(dir);
}
