// src/logic/NcatExe.h

#pragma once
#include "../../core/InterfaceListener.h"

class NcatExe : public IListener {
public:
  std::string name() const override { return "ncat_exe"; }
  std::string command(const Options &o) const override {
    return "ncat.exe -lvnp " + std::to_string(o.port);
  }
};
