#ifndef HIGHSPEEDCAR_H_
#define HIGHSPEEDCAR_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a HighSpeedCar in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class HighSpeedCar : public IEntity {
 public:
  /**
   * @brief Construct a new high speed Car object. This high speed Car has all
   * the functions that the entity has. This class will do
   * nothing except moving from its position toward the
   * destination (chosen randomly) in higher speed than common car.
   *
   * @param obj New json object to create a high speed car right at the
   * start of the scene with the information
   */
  HighSpeedCar(JsonObject& obj);
  // Destructor
  /**
   * @brief Destroy the high speed Car object
   *
   */
  ~HighSpeedCar();

  /**
   * @brief Get speed of the high speed car.
   * @return The speed of the high speed car.
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Get current position of the high speed car.
   * @return Current position of the high speed car
   **/
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Get direction of the high speed car.
   * @return The direction of the high speed car.
   **/
  Vector3 GetDirection() const { return direction; }
  /**
   * @brief Get destination of the high speed car.
   * @return The destination of the high speed car.
   **/
  Vector3 GetDestination() const { return destination; }
  /**
   * @brief Get details of the high speed car.
   * @return The jsonObject with the deatis of this high speed car.
   **/
  JsonObject GetDetails() const { return details; }
  /**
   * @brief Figure if the high speed car is available.
   * @return True of false for availability of the high speed car.
   **/
  bool GetAvailability() const { return available; }
  /**
   * @brief Find the nearest entity of the high speed car.
   * @param  scheduler The list of entities that you
   * need to find the nearest one.
   **/
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  // Updates the high speed car's position
  /**
   * @brief  Updates the high speed car's position. The high speed car moving
   * from its position toward the destination (chosen randomly)
   * ub this function. Must use Astar strategy to move around.
   * @param dt Movement distance per unit time
   * @param scheduler The list of entities
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);
  /**
   * @brief Set the position of high speed car.
   * @param pos_ the position in vector
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  // Sets the high speed car's direction
  /**
   * @brief Set the direction of high speed car.
   * @param dir the direction in vector
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }
  /**
   * @brief Set the destination of high speed car.
   * @param des_ the destination in vector
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  // Rotates a drone
  // void Rotate(double angle);

  // void Jump(double height);

  // void Move();

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  HighSpeedCar(const HighSpeedCar& HighSpeedCar) = delete;
  HighSpeedCar& operator=(const HighSpeedCar& HighSpeedCar) = delete;

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
};

#endif  // HIGHSPEEDCAR_H_
