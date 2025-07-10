// src/logic/InterfaceListener.h

#pragma once

#include "Options.h"
#include <string>

class IListener {
public:
  virtual ~IListener() = default;

  // Unique name, e.g. "nc", "socat_tty", "ncat_tls", etc.
  virtual std::string name() const = 0;

  // Returns the exact command to run locally to catch the shell
  virtual std::string command(const Options &opts) const = 0;
};
