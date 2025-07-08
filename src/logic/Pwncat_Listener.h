#pragma once
#include "InterfaceListener.h"

class Pwncat : public IListener {
public:
  std::string name() const override { return "pwncat"; }
  std::string command(const Options &o) const override {
    return "python3 -m pwncat -lp " + std::to_string(o.port);
  }
};
