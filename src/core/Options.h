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

enum class PayloadType {
  REVERSE,
  BIND,
  MSFVENOM,
  HOAXSHELL
};

enum class Platform {
  LINUX,
  WINDOWS,
  MAC
};

enum class Encoding {
  NONE,
  URL,
  DOUBLE_URL,
  BASE64
};

struct Options {
  std::string host;
  int port;

  // Payload configuration
  PayloadType payloadType = PayloadType::REVERSE;
  Platform platform = Platform::LINUX;
  Encoding encoding = Encoding::NONE;

  // Listener configuration
  std::string listenerType;

  // Shell interpreter
  std::string interpreter;

  // Additional flags
  std::map<std::string, bool> flags;
};
