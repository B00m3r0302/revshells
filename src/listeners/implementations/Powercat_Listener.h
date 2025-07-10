#pragma once
#include "InterfaceListener.h"

class Powercat : public IListener {
public:
  std::string name() const override { return "powercat"; }
  std::string command(const Options &o) const override {
    return "powercat -l -p " + std::to_string(o.port);
  }
};
