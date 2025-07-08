// src/logic/InterfacePayload.h

/**
 * Using #pragma once to tell the compiler that its already processed the file
 * and to skip it on subsequent #includes This prevents: Multiple-definition
 * errors: This is when a header is #included (directly or indirectly) more than
 * once Redundant parsing: parsing of the same header, which can slightly speed
 * up compile times
 */

#pragma once

#include "Options.h"
#include <string>

/**
 * InterfacePayload is our *interface* for any payload type.
 * - `name()` gives a unique identifier used in UIs or CLI flags.
 * - `generate()` returns a one-liner command for the *target*.
 * - `listener()` returns the one-liner command for the *attacker* to run.
 *
 *   Why interface?
 * - **Open/Closed Principle**: new payloads can be added without editing old
 * code.
 * - **Dependency Inversion**: UI and CLI layers depend on this interface not on
 * concrete implementations.
 * - **Testability**: each payload can be unit tested in isolation.
 */

class IPayload {
public:
  virtual ~IPayload() = default;
  /// e.g. "bash", "python", "powershell", etc.
  virtual std::string name() const = 0;
  /// Command to drop on the victim machine
  virtual std::string generate(const Options &opts) const = 0;
  /// Command to run locally to catch the shell
  virtual std::string listener(const Options &opts) const = 0;
};
