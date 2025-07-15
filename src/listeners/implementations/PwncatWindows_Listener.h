#pragma once
#include "../../core/InterfaceListener.h"

class PwncatWindows : public IListener {
public:
  std::string name() const override { return "pwncat_windows"; }
  std::string command(const Options &o) const override {
    return "python3 -m pwncat -m windows -lp " + std::to_string(o.port);
  }
};
