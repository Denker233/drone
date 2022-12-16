#ifndef LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_
#define LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_

#include "IEntity.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern
class IController {
 public:
  /**
   * @brief Destroy the IController object
   *
   */
  virtual ~IController() {}
  /**
   * @brief Adds an entity to the program
   *
   * @param entity the entity to add
   */
  virtual void AddEntity(const IEntity& entity) = 0;
  /**
   * @brief Adds an entity to the program
   *
   * @param entity entity to add
   */
  virtual void UpdateEntity(const IEntity& entity) = 0;
  /**
   * @brief Removes an entity from the program
   *
   * @param id the id of the entity to delete
   */
  virtual void RemoveEntity(int id) = 0;
  /**
   * @brief Adds a path to the program
   *
   * @param id id of path
   * @param path path to add
   */
  virtual void AddPath(int id,
                       const std::vector<std::vector<float> >& path) = 0;
  /**
   * @brief Removes a path from the program
   *
   * @param id id to remove
   */
  virtual void RemovePath(int id) = 0;
  /**
   * @brief Allows messages to be passed back to the view
   *
   * @param event enent occur
   * @param details detail event will be add
   */
  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif  // LIBS_TRANSIT_INCLUDE_ICONTROLLER_H_
