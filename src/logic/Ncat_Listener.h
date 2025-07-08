// src/logic/Ncat.h

#pragma once
#include "InterfaceListener.h"

class NcatListener : public IListener {
public:
  std::string name() const override { return "ncat"; }
  std::string command(const Options &o) const override {
    // Ncat NcatListener
    return "ncat -nlvp " + std::to_string(o.port);
  }
};
