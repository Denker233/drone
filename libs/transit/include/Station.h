#ifndef LIBS_TRANSIT_INCLUDE_STATION_H_
#define LIBS_TRANSIT_INCLUDE_STATION_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

// Represents a Booster swapping station in a physical system.
// Stations move using euler integration based on a specified
// velocity and direction.
class Station : public IEntity {
 public:
  /**
   * @brief Construct a new Station Stations are created with a name
   *
   * @param obj the input json object
   */
  Station(JsonObject& obj);
  /**
   * @brief Destroy the Station object
   *
   */
  ~Station();
  /**
   * @brief Get the Position of the staion
   *
   * @return Vector3 position
   */
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Get the Destination of the station
   *
   * @return Vector3 the Destination of the station
   */
  Vector3 GetDestination() const { return destination; }
  /**
   * @brief Get the Direction of the station
   *
   * @return Vector3 the Direction of the station
   */
  Vector3 GetDirection() const { return direction; }
  /**
   * @brief Get the Details of the station
   *
   * @return JsonObject the Details of the station
   */
  JsonObject GetDetails() const { return details; }
  /**
   * @brief   Updates the Station's position
   *
   * @param dt delta time (change time)
   * @param scheduler the scheduler to update
   */
  void Update(double dt, std::vector<IEntity*> scheduler){}
  /**
   * @brief Get the Type of the station
   *
   * @return std::string the Type of the station
   */
  std::string GetType() { return type; }

  // Removing the copy constructor and assignment operator
  // so that Stations cannot be coppied.
  Station(const Station& Station) = delete;
  Station& operator=(const Station& Station) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 destination;
  Vector3 direction;
  float speed;
  float battery;
  bool available;
  bool pickedUp;
  std::string type;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif  // LIBS_TRANSIT_INCLUDE_STATION_H_
