#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class Drone : public IEntity {
 public:
  // Drones are created with a name
  Drone(JsonObject& obj);
  // Destructor
  ~Drone();

  float GetSpeed() const { return speed; }

  // Gets the drone position
  Vector3 GetPosition() const { return position; }

  Vector3 GetDirection() const { return direction; }

  Vector3 GetDestination() const { return destination; }

  JsonObject GetDetails() const { return details; }

  bool GetAvailability() const { return available; }

  std::string GetType() { 
    // std::string s(type);
    return type;}

  void GetNearestEntity(std::vector<IEntity*> scheduler,std::vector<IEntity*> stations);

  // Updates the drone's position
  void Update_Drone(double dt, std::vector<IEntity*> scheduler,std::vector<IEntity*> stations);

  void SetPosition(Vector3 pos_) { position = pos_; }

  void SetSpeed(int i) { originSpeed = speed;
                         speed = speed*i; }

  void SetOriginSpeed() { speed = originSpeed; };

  // Sets the drone's direction
  void SetDirection(Vector3 dir_) { direction = dir_; }

  void SetDestination(Vector3 des_) { destination = des_; }

  void SetBattery(float ba) { battery=ba; }

  float GetBattery() {return battery;}

  // Rotates a drone
  void Rotate(double angle);

  void Jump(double height);

  //zhu
  void Booster();

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

 private:
  JsonObject details;
  std::vector< IStrategy*> Stras;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true; // jump helper
  Vector3 destination;
  // const char* type;
  std::string type;
  float speed;
  float originSpeed;
  float highSpeed = 60.0;
  float lowSpeed = 30.0;
  float battery = 0;
  bool available;
  bool pickedUp;
  std::string strategyName;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif
