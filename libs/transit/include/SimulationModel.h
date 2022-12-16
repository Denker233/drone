#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "CompositeFactory.h"
#include "IController.h"
#include "IEntity.h"
#include "graph.h"
using namespace routing;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
class SimulationModel {
 public:
  SimulationModel(IController& controller);
  /**
   * @brief Set the Graph object
   *
   * @param graph the Graph object will be set
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }
  /**
   * @brief Creates an simulation entity
   *
   * @param entity entity to created
   */
  void CreateEntity(JsonObject& entity);
  /**
   * @brief   Schedules a trip for an object in the scene
   *
   * @param details the detail about the trip
   */
  void ScheduleTrip(JsonObject& details);
  /**
   * @brief Updates the simulation
   *
   * @param dt delta time (change time)
   */
  void Update(double dt);
  /**
   * @brief Adds a new entity type
   *
   * @param factory factory to add
   */
  void AddFactory(IEntityFactory* factory);

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> stations;
  std::vector<IEntity*> scheduler;
  const IGraph* graph;
  CompositeFactory* compFactory;
};

#endif
