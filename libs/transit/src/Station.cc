#define _USE_MATH_DEFINES
#include "Station.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"

Station::Station(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  available = true;
}

Station::~Station() {
  // Delete dynamically allocated variables
}
