#pragma once
#include "../../core/InterfaceListener.h"

class WindowsConPty : public IListener {
public:
  std::string name() const override { return "windows_conpty"; }
  std::string command(const Options &o) const override {
    return "stty raw -echo; (stty size; cat) | nc -lvnp " +
           std::to_string(o.port);
  }
};
