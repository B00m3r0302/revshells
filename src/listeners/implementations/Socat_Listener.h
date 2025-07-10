// src/logic/SocatListener.h

#pragma once
#include "InterfaceListener.h"

class SocatListener : public IListener {
public:
  std::string name() const override { return "socat"; }
  std::string command(const Options &o) const override {
    // TCP-listener on port pipe to stdio
    return "socat -d -d TCP-LISTEN:" + std::to_string(o.port) + " STDOUT";
  }
};
