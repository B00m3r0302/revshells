// src/logic/NcFreeBsd.h

#pragma once
#include "../../core/InterfaceListener.h"

class NcFreeBsd : public IListener {
public:
  std::string name() const override { return "nc_freebsd"; }
  std::string command(const Options &o) const override {
    return "nc -lvn " + std::to_string(o.port);
  }
};
