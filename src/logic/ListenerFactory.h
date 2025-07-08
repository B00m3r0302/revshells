#pragma once
#include "Hoaxshell_Listener.h"
#include "InterfaceListener.h"
#include "Msfconsole_Listener.h"
#include "NcBusyBox_Listener.h"
#include "NcFreeBsd_Listener.h"
#include "Nc_Listener.h"
#include "NcatExe_Listener.h"
#include "NcatTLS_Listener.h"
#include "Ncat_Listener.h"
#include "Openssl_Listener.h"
#include "Powercat_Listener.h"
#include "PwncatWindows_Listener.h"
#include "Pwncat_Listener.h"
#include "RlwrapNc_Listener.h"
#include "Rustcat_Listener.h"
#include "SocatTTY_Listener.h"
#include "Socat_Listener.h"
#include "WindowsConPty_Listener.h"
#include <memory>
#include <unordered_map>
#include <vector>

class ListenerFactory {
  std::unordered_map<std::string, std::unique_prt<IListener>> registry_;

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
