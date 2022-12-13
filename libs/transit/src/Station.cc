#define _USE_MATH_DEFINES
#include "Station.h"

//#include <cmath>
//#include <limits>

//#include "AstarStrategy.h"

Station::Station(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
  std::string station_type=obj["type"];
  type = station_type;

  available = true;
}

Station::~Station() {
  // Delete dynamically allocated variables
}
