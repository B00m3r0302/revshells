// src/logic/NcBusyBox.h

#pragma once
#include "InterfaceListener.h"

class NcBusyBox : public IListener {
public:
  std::string name() const override { return "nc_busybox"; }
  std::string command(const Options &o) const override {
    return "busybox nc -lp " + std::to_string(o.port);
  }
};
