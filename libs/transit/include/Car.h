#ifndef CAR_H_
#define CAR_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a car in a physical system.

class Car : public IEntity {
 public:
  /**
   * @brief Construct a new Car object. This Car has all
   * the functions that the entity has. This class will do
   * nothing except moving from its position toward the
   * destination (chosen randomly).
   *
   * @param obj New json object to create a car right at the
   * start of the scene with the information
   */
  Car(JsonObject& obj);
  // Destructor
  /**
   * @brief Destroy the Car object
   *
   */
  ~Car();
  /**
   * @brief Get speed of the car.
   * @return The speed of the car.
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Get current position of the car.
   * @return Current position of the car.
   **/
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Get direction of the car.
   * @return The direction of the car.
   **/
  Vector3 GetDirection() const { return direction; }
  /**
   * @brief Get destination of the car.
   * @return The destination of the car.
   **/
  Vector3 GetDestination() const { return destination; }
  /**
   * @brief Get details of the car.
   * @return The jsonObject with the deatis of this car.
   **/
  JsonObject GetDetails() const { return details; }
  /**
   * @brief Figure if the car is available.
   * @return True of false for availability of the car.
   **/
  bool GetAvailability() const { return available; }
  /**
   * @brief Find the nearest entity of the car.
   * @param  scheduler The list of entities that you
   * need to find the nearest one.
   **/
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  // Updates the car's position
  /**
   * @brief  Updates the car's position. The car moving
   * from its position toward the destination (chosen randomly)
   * ub this function. Must use Astar strategy to move around.
   * @param dt Movement distance per unit time
   * @param scheduler The list of entities
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);
  /**
   * @brief Set the position of car.
   * @param pos_ the position in vector
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  // Sets the car's direction
  /**
   * @brief Set the direction of car.
   * @param dir the direction in vector
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }
  /**
   * @brief Set the destination of car.
   * @param des_ the destination in vector
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  // Removing the copy constructor and assignment operator
  // so that cars cannot be coppied.
  Car(const Car& car) = delete;
  Car& operator=(const Car& car) = delete;

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

#endif  // CAR_H_
