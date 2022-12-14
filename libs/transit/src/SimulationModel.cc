#include "SimulationModel.h"
#include "DroneFactory.h"
#include "RobotFactory.h"
#include "HelicopterFactory.h"
#include "CarFactory.h"
#include "HighSpeedCarFactory.h"
#include "StationFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new CarFactory());
  AddFactory(new HighSpeedCarFactory());
  AddFactory(new StationFactory());
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);
  
  // Call AddEntity to add it to the view
  if(type.compare("swapstation")==0){
    controller.AddEntity(*myNewEntity);
    stations.push_back(myNewEntity);
  }
  else{
    controller.AddEntity(*myNewEntity);
    entities.push_back(myNewEntity);
  }
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 && entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetStrategyName(strategyName);
      std::cout <<"Front Endpoint"<<end[0]<<end[1]<<end[2] << std::endl;
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    std::string type = entities[i]->GetType();
    
    
    if(type.compare("drone")==0){
      // printf("inside update simu\n");
      // entities[i]->GetDestination().Print();
      entities[i]->Update_Drone(dt, scheduler, stations);
      controller.UpdateEntity(*entities[i]);
    }
    else{
      // if(type.compare("robot")==0){
      //   printf("robot position\n");
      //   entities[i]->GetPosition().Print();
      // }
      entities[i]->Update(dt, scheduler);
      controller.UpdateEntity(*entities[i]);
    }
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
