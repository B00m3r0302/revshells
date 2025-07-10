#pragma once
#include "../core/InterfaceListener.h"
#include "implementations/Hoaxshell_Listener.h"
#include "implementations/Msfconsole_Listener.h"
#include "implementations/NcBusyBox_Listener.h"
#include "implementations/NcFreeBsd_Listener.h"
#include "implementations/Nc_Listener.h"
#include "implementations/NcatExe_Listener.h"
#include "implementations/NcatTLS_Listener.h"
#include "implementations/Ncat_Listener.h"
#include "implementations/Openssl_Listener.h"
#include "implementations/Powercat_Listener.h"
#include "implementations/PwncatWindows_Listener.h"
#include "implementations/Pwncat_Listener.h"
#include "implementations/RlwrapNc_Listener.h"
#include "implementations/Rustcat_Listener.h"
#include "implementations/SocatTTY_Listener.h"
#include "implementations/Socat_Listener.h"
#include "implementations/WindowsConPty_Listener.h"
#include <memory>
#include <unordered_map>
#include <vector>

class ListenerFactory {
  std::unordered_map<std::string, std::unique_ptr<IListener>> registry_;

public:
  ListenerFactory() {
    registry_["hoaxshell"] = std::make_unique<NcListener>();
    registry_["msfconsole"] = std::make_unique<Msfconsole>();
    registry_["nc_busybox"] = std::make_unique<NcBusyBox>();
    registry_["nc_freebsd"] = std::make_unique<NcFreeBsd>();
    registry_["nc"] = std::make_unique<NcListener>();
    registry_["ncat_exe"] = std::make_unique<NcatExe>();
    registry_["ncat_tls"] = std::make_unique<NcatTLS>();
    registry_["ncat"] = std::make_unique<NcatListener>();
    registry_["openssl"] = std::make_unique<Openssl>();
    registry_["powercat"] = std::make_unique<Powercat>();
    registry_["pwncat_windows"] = std::make_unique<PwncatWindows>();
    registry_["pwncat"] = std::make_unique<Pwncat>();
    registry_["rlwrap_nc"] = std::make_unique<RlwrapNc>();
    registry_["rustcat"] = std::make_unique<Rustcat>();
    registry_["socat"] = std::make_unique<SocatListener>();
    registry_["socat_tty"] = std::make_unique<SocatTTY>();
    registry_["windows_conpty"] = std::make_unique<WindowsConPty>();
  }

  std::vector<std::string> available() const {
    std::vector<std::string> names;
    names.reserve(registry_.size());
    for (auto &kv : registry_)
      names.push_back(kv.first);
    return names;
  }

  IListener *get(const std::string &name) const {
    auto it = registry_.find(name);
    return it == registry_.end() ? nullptr : it->second.get();
  }
};
