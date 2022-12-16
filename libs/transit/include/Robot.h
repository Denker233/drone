#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class Robot : public IEntity {
 public:
  /**
   * @brief Construct a new Robot object
   *
   * @param obj the input jsonobject
   */
  Robot(JsonObject& obj);
  /**
   * @brief Destroy the Robot object
   *
   */
  ~Robot() override = default;
  /**
   * @brief Get the Position of the robot
   *
   * @return Vector3 the Position of the robot
   */
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Get the Direction of the robot
   *
   * @return Vector3 the Direction of the robot
   */
  Vector3 GetDirection() const { return direction; }
  /**
   * @brief Get the Destination of the robot
   *
   * @return Vector3 the Destination of the robot
   */
  Vector3 GetDestination() const { return destination; }
  /**
   * @brief Get the Availability of the robot
   *
   * @return true available
   * @return false not available
   */
  bool GetAvailability() const { return available; }
  /**
   * @brief Get the Details of the robot
   *
   * @return JsonObject the Details of the robot
   */
  JsonObject GetDetails() const override;
  /**
   * @brief Get the Type of the robot
   *
   * @return std::string the Type of the robot
   */
  std::string GetType() { return type; }
  /**
   * @brief Get the Speed of the robot
   *
   * @return float the Speed of the robot
   */
  float GetSpeed() const { return speed; }
  /**
   * @brief Get the Strategy Name of the robot
   *
   * @return std::string Strategy Name of the robot
   */
  std::string GetStrategyName() { return strategyName; }
  /**
   * @brief Set the Availability of the robot
   *
   * @param choice true for available false for not available
   */
  void SetAvailability(bool choice);
  /**
   * @brief Set the Position of the robot
   *
   * @param pos_ the Position of the robot
   */
  void SetPosition(Vector3 pos_) { position = pos_; }
  /**
   * @brief Set the Direction of the robot
   *
   * @param dir_ the Direction of the robot
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }
  /**
   * @brief Set the Destination of the robot
   *
   * @param des_ the Destination of the robot
   */
  void SetDestination(Vector3 des_) { destination = des_; }
  /**
   * @brief Set the Strategy Name of the robot
   *
   * @param strategyName_ the the Strategy Name
   */
  void SetStrategyName(std::string strategyName_) {
    strategyName = strategyName_;
  }
  /**
   * @brief let the robot rotate certain angle
   *
   * @param angle
   */
  void Rotate(double angle);

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  std::string type;
  bool available;
  std::string strategyName;
};  // end class

#endif  // ROBOT_H
