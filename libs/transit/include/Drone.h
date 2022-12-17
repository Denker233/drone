#ifndef LIBS_TRANSIT_INCLUDE_DRONE_H_
#define LIBS_TRANSIT_INCLUDE_DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Construct a new Drone object Drones are created with a name
   *
   * @param obj the input json object
   */
  Drone(JsonObject& obj);
  /**
   * @brief Destroy the Drone object
   *
   */
  ~Drone();
  /**
   * @brief Get the Speed of the drone
   *
   * @return float speed of the drone
   */
  float GetSpeed() const { return speed; }
  float GetHighSpeed() const { return highSpeed;}
  float GetLowSpeed() const { return lowSpeed;}
  /**
   * @brief Get the Position of the drone
   *
   * @return Vector3 position
   */
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Get the Direction of the drone
   *
   * @return Vector3 direction
   */
  Vector3 GetDirection() const { return direction; }
  /**
   * @brief Get the Destination of the drone
   *
   * @return Vector3 destination
   */
  Vector3 GetDestination() const { return destination; }
  /**
   * @brief Get the Details of the drone
   *
   * @return JsonObject detail of the drone
   */
  JsonObject GetDetails() const { return details; }
  /**
   * @brief Get the Availability of the drone
   *
   * @return true is available
   * @return false is not available
   */
  bool GetAvailability() const { return available; }
  /**
   * @brief Get the Type of the drone
   *
   * @return std::string type
   */
  std::string GetType() { return type; }
  /**
   * @brief Get the Nearest Entity of the drone
   *
   * @param scheduler the scheduler the drone is in
   * @param stations the station entity
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler,
                        std::vector<IEntity*> stations);
  /**
   * @brief update the drone in the scheduler
   *
   * @param dt delta time (change time)
   * @param scheduler the scheduler the drone in
   * @param station the station entities
   */
  void Update_Drone(double dt, std::vector<IEntity*> scheduler,
                    std::vector<IEntity*> stations);
  /**
   * @brief Set the Position of the drone
   *
   * @param pos_ the new position
   */
  void SetPosition(Vector3 pos_) { position = pos_; }
  /**
   * @brief Set the Direction of the drone
   *
   * @param dir_ the direction of the drone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }
  /**
   * @brief Set the Destination of the drone
   *
   * @param des_ the destination of the drone
   */
  void SetDestination(Vector3 des_) { destination = des_; }
  /**
   * @brief Set the Battery of the drone
   *
   * @param ba the battery of the drone
   */
  void SetBattery(float ba) { battery = ba; }
  /**
   * @brief Get the Battery of the drone
   *
   * @return float battery
   */
  float GetBattery() { return battery; }
  /**
   * @brief rotate the drone
   *
   * @param angle angle to rotate
   */
  void Rotate(double angle);
  /**
   * @brief let the drone to jump
   *
   * @param height height to jump
   */
  void Jump(double height);

  void Booster();

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

 private:
  JsonObject details;
  std::vector<IStrategy*> Stras;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true;  // jump helper
  Vector3 destination;
  std::string type;
  float speed;
  float highSpeed = 100.0;
  float lowSpeed = 10.0;
  float battery = 0;
  bool available;
  bool pickedUp;
  std::string strategyName;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif // LIBS_TRANSIT_INCLUDE_DRONE_H_
