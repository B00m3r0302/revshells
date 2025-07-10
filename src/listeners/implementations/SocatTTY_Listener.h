#pragma once
#include "InterfaceListener.h"

class SocatTTY : public IListener {
public:
  std::string name() const override { return "socat_tty"; }
  std::string command(const Options &o) const override {
    return "socat -d -d file:`tty`,raw,echo=0 TCP-LISTEN:" +
           std::to_string(o.port);
  }
};
