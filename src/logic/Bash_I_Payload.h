// src/logic/BashPayload.h

#pragma once

#include "InterfacePayload.h"
#include "Options.h"
#include <string>
/**
 * BashIPayload implements IPayload for generic Bourne-style shells.
 * It uses the specified interpreter (bash, sh, zsh, etc.) to execute
 * a TCP reverse shell back to the attacker.
 */
class BashIPayload : public IPayload {
public:
  // Returns a unique identifier for this payload type.
  std::string name() const override;

  // Generates the reverse-shell one-liner for the target.
  std::string generate(const Options &o) const override;

  // Generates the listener command (defaulting to 'nc') for the attacker.
  std::string listener(const Options &o) const override;
};
