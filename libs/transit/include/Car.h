#ifndef CAR_H_
#define CAR_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a car in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class Car: public IEntity {
 public:
  // Drones are created with a name
  Car(JsonObject& obj);
  // Destructor
  ~Car();

  float GetSpeed() const { return speed; }

  // Gets the drone position
  Vector3 GetPosition() const { return position; }

  Vector3 GetDirection() const { return direction; }

  Vector3 GetDestination() const { return destination; }

  JsonObject GetDetails() const { return details; }

  bool GetAvailability() const { return available; }

  void GetNearestEntity(std::vector<IEntity*> scheduler);

  // Updates the drone's position
  void Update(double dt, std::vector<IEntity*> scheduler);

  void SetPosition(Vector3 pos_) { position = pos_; }

  // Sets the drone's direction
  void SetDirection(Vector3 dir_) { direction = dir_; }

  void SetDestination(Vector3 des_) { destination = des_; }

  // Rotates a drone
  void Rotate(double angle);

  void Jump(double height);

  void Move();

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  Car(const Car& car) = delete;
  Car& operator=(const Car& car) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true; // jump helper
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  std::string strategyName;
  IEntity* nearestEntity = NULL;
  IStrategy* Strategy1 = NULL;
};

#endif
