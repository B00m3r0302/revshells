// src/logic/NcatTLS.h

#pragma once
#include "../../core/InterfaceListener.h"

class NcatTLS : public IListener {
public:
  std::string name() const override { return "ncat_tls"; }
  std::string command(const Options &o) const override {
    return "ncat --ssl --lvnp " + std::to_string(o.port);
  }
};
