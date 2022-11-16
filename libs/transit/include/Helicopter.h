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
  /**
   * @brief Construct a new helicopter object. This helicopter has all
   * the functions that the entity has. This class will do
   * nothing except moving from its position toward the
   * destination (chosen randomly).
   *
   * @param obj New json object to create a helicopter right at the
   * start of the scene with the information
   */
  Helicopter(JsonObject& obj);
  // Destructor
  /**
   * @brief Destroy the helicopter object
   *
   */
  ~Helicopter();

  /**
   * @brief Get speed of the helicopter.
   * @return The speed of the helicopter.
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Get current position of the helicopter.
   * @return Current position of the helicopter.
   **/
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Get direction of the helicopter.
   * @return The direction of the helicopter.
   **/
  Vector3 GetDirection() const { return direction; }
  /**
   * @brief Get destination of the helicopter.
   * @return The destination of the helicopter.
   **/
  Vector3 GetDestination() const { return destination; }
  /**
   * @brief Get details of the helicopter.
   * @return The jsonObject with the deatis of this helicopter.
   **/
  JsonObject GetDetails() const { return details; }
  /**
   * @brief Figure if the helicopter is available.
   * @return True of false for availability of the helicopter.
   **/
  bool GetAvailability() const { return available; }
  /**
   * @brief Find the nearest entity of the helicopter.
   * @param  scheduler The list of entities that you
   * need to find the nearest one.
   **/
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  // Updates the helicopter's position
  /**
   * @brief  Updates the helicopter's position. The helicopter moving
   * from its position toward the destination (chosen randomly)
   * ub this function. Must use Astar strategy to move around.
   * @param dt Movement distance per unit time
   * @param scheduler The list of entities
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);
  /**
   * @brief Set the position of helicopter.
   * @param pos_ the position in vector
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  // Sets the helicopter's direction
  /**
   * @brief Set the direction of helicopter.
   * @param dir the direction in vector
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }
  /**
   * @brief Set the destination of helicopter.
   * @param des_ the destination in vector
   **/
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
