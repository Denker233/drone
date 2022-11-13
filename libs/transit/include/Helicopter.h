#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a Helicopter in a physical system.
// Helicopters move using euler integration based on a specified
// velocity and direction.
class Helicopter : public IEntity {
 public:
  // Helicopters are created with a name
  Helicopter(JsonObject& obj);
  // Destructor
  ~Helicopter();

  float GetSpeed() const { return speed; }

  // Gets the Helicopter position
  Vector3 GetPosition() const { return position; }

  Vector3 GetDirection() const { return direction; }

  Vector3 GetDestination() const { return destination; }

  JsonObject GetDetails() const { return details; }

  bool GetAvailability() const { return available; }

  void GetNearestEntity(std::vector<IEntity*> scheduler);

  // Updates the Helicopter's position
  void Update(double dt, std::vector<IEntity*> scheduler);

  void SetPosition(Vector3 pos_) { position = pos_; }

  // Sets the Helicopter's direction
  void SetDirection(Vector3 dir_) { direction = dir_; }

  void SetDestination(Vector3 des_) { destination = des_; }

  // void Move();

  // Rotates a Helicopter
//   void Rotate(double angle);

//   void Jump(double height);

  // Removing the copy constructor and assignment operator
  // so that Helicopters cannot be coppied.
  Helicopter(const Helicopter& Helicopter) = delete;
  Helicopter& operator=(const Helicopter& Helicopter) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true;  // jump helper
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  std::string strategyName;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif  // LIBS_TRANSIT_INCLUDE_HELICOPTER_H_
