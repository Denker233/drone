#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"

using namespace routing;

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern
class IEntity {
 public:
  /**
   * @brief Construct a new IEntity object
   *
   */
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }
  /**
   * @brief Destroy the IEntity object
   *
   */
  virtual ~IEntity() {}
  /**
   * @brief Get the Id of the entity
   *
   * @return int the Id of the entity
   */
  virtual int GetId() const { return id; }
  /**
   * @brief Get the Position of the entity
   *
   * @return Vector3 the Position of the entity
   */
  virtual Vector3 GetPosition() const = 0;
  /**
   * @brief Get the Direction of the entity
   *
   * @return Vector3 the Direction of the entity
   */
  virtual Vector3 GetDirection() const = 0;
  /**
   * @brief Get the Destination of the entity
   *
   * @return Vector3 the Destination of the entity
   */
  virtual Vector3 GetDestination() const = 0;
  /**
   * @brief Get the Details of the entity
   *
   * @return JsonObject the Details of the entity
   */
  virtual JsonObject GetDetails() const = 0;
  /**
   * @brief Get the Type of the entity
   *
   * @return std::string the Type of the entity
   */
  virtual std::string GetType() = 0;
  /**
   * @brief Get the High Speed of the entity
   *
   * @return float the High Speed of the entity
   */
  virtual float GetHighSpeed() const {};
  /**
   * @brief Get the Low Speed of the entity
   *
   * @return float the Low Speed of the entity
   */
  virtual float GetLowSpeed() const {};
  /**
   * @brief Get the Speed of the entity
   *
   * @return float the Speed of the entity
   */
  virtual float GetSpeed() const {};
  /**
   * @brief Get the Battery of the entity
   *
   * @return float the Battery of the entity
   */
  virtual float GetBattery(){};
  /**
   * @brief Set the Battery of the entity
   *
   * @param newbat the Battery of the entity
   */
  virtual void SetBattery(float newbat) {}
  /**
   * @brief Get the Availability of the entity
   *
   * @return true available
   * @return false not available
   */
  virtual bool GetAvailability() const {}
  /**
   * @brief Get the Strategy Name of the entity
   *
   * @return std::string the Strategy Name of the entity
   */
  virtual std::string GetStrategyName() {}
  /**
   * @brief Set the Availability of the entity
   *
   * @param choice true available false not available
   */
  virtual void SetAvailability(bool choice) {}
  /**
   * @brief
   *
   * @param dt delta time 
   * @param scheduler scheduler to update
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) {}
  /**
   * @brief update the drone
   *
   * @param dt delta time 
   * @param scheduler scheduler to update
   * @param stations charge 
   */
  virtual void Update_Drone(double dt, std::vector<IEntity*> scheduler,
                            std::vector<IEntity*> stations) {}
  /**
   * @brief Set the Graph of the entity
   *
   * @param graph the Graph of the entity
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }
  /**
   * @brief Set the Position of the entity
   *
   * @param pos_ the Position of the entity
   */
  virtual void SetPosition(Vector3 pos_) {}
  /**
   * @brief Set the Direction of the entity
   *
   * @param dir_ the Direction of the entity
   */
  virtual void SetDirection(Vector3 dir_) {}
  /**
   * @brief Set the Destination of the entity
   *
   * @param des_ the Destination of the entity
   */
  virtual void SetDestination(Vector3 des_) {}
  /**
   * @brief Set the Strategy Name of the entity
   *
   * @param strategyName_ the Strategy Name of the entity
   */
  virtual void SetStrategyName(std::string strategyName_) {}
  /**
   * @brief let entity to ratate
   *
   * @param angle angle will rotated
   */
  virtual void Rotate(double angle) {}
  /**
   * @brief let the entity to jump
   *
   * @param height height to jump
   */
  virtual void Jump(double height) {}

 protected:
  int id;
  const IGraph* graph;
};

#endif
