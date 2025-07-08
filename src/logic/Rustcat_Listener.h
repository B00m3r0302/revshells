#pragma once
#include "InterfaceListener.h"

class Rustcat : public IListener {
public:
  std::string name() const override { return "rustcat"; }
  std::string command(const Options &o) const override {
    return "rcat listen " + std::to_string(o.port);
  }
};
