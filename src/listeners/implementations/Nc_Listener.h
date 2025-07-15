// src/logic/NcListener.h

#pragma once
#include "../../core/InterfaceListener.h"

class NcListener : public IListener {
public:
  std::string name() const override { return "nc"; }
  std::string command(const Options &o) const override {
    // -l listen, -v verbose, -n numeric-only, -p port
    return "nc -nlvp " + std::to_string(o.port);
  }
};
