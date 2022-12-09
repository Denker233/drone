#ifndef STATION_H_
#define STATION_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a Booster swapping station in a physical system.
// Stations move using euler integration based on a specified
// velocity and direction.
class Station : public IEntity {
 public:
  // Stations are created with a name
  Station(JsonObject& obj);
  // Destructor
  ~Station();

   
  Vector3 GetPosition() const { return position; }

  JsonObject GetDetails() const { return details; }

  //bool GetAvailability() const { return available; }

  // void GetNearestEntity(std::vector<IEntity*> scheduler);

  // Updates the Station's position
  // void Update(double dt, std::vector<IEntity*> scheduler);

  void SetPosition(Vector3 pos_) { position = pos_; }

  void SwapBooster(Drone *dr){ 
    dr->SetSpeed(2);
    dr->SetBattery(1000);
  }

  // Removing the copy constructor and assignment operator
  // so that Stations cannot be coppied.
  Station(const Station& Station) = delete;
  Station& operator=(const Station& Station) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 destination;
  float speed;
  float battery;
  bool available;
  bool pickedUp;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif
