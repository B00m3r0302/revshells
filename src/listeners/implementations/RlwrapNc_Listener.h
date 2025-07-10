#pragma once
#include "InterfaceListener.h"

class RlwrapNc : public IListener {
public:
  std::string name() const override { return "rlwrap_nc"; }
  std::string command(const Options &o) const override {
    return "rlwrap -cAr nc -nlvp " + std::to_string(o.port);
  }
};
