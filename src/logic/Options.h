// src/logic/Options.h

#pragma once

#include <map>
#include <string>

/**
 * Options struct carries all parameters that any payload might need.
 * - host/port are common to every reverse shell.
 * - Can extend this with booleans or enums for base64-encoding, etc.
 * like stager stages, encryption flags, etc. without touching existing payloads
 */

struct Options {
  std::string host;
  int port;

  // New field: which listener tool to use
  // e.g. "nc", "socat", "ncat_tls", etc.
  std::string listenerType;

  // Which shell interpreter to invoke on the target.
  // e.g. "bash", "sh", "zsh", "bin/sh", etc.
  std::string interpreter;

  // e.g. {"base64", true}, {"stager", false}
  std::map<std::string, bool> flags;
};
