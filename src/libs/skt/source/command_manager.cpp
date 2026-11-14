#include "skt/command_manager.h"

#include <string.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace skt {

CommandManager::~CommandManager() {
  if (unknown3148) {
    finalize();
  }
}

void CommandManager::destroy() {
  CommandManager *manager = get();
  if (manager != nullptr) {
    mm::mtl::IAllocator *allocator = manager->m_allocator;
    if (allocator != nullptr) {
      manager->~CommandManager();
      allocator->deallocate(manager);
    } else {
      mm::MMStdBase::mmPrint("[skt] allocator not found!!\n");
    }
  }
}

void CommandManager::finalize() {
  unknown3148 = false;
  mm::threading::CS lock(unknown3120);
  for (PortInfo *port = unknown08.begin(); port != unknown08.end(); ++port) {
    port->destroy();
  }
  unknown08.clear();
}

mm::mtl::IAllocator *CommandManager::getAllocator() {
  CommandManager *manager = get();
  if (manager != nullptr) {
    return manager->m_allocator;
  }
  return nullptr;
}

bool CommandManager::sendCommand(const char *server, const char *command) {
  CommandManager *manager = get();
  if (manager == nullptr) {
    return false;
  }

  PortInfo *port = manager->findPortInfoExcludeHtcs(server);
  if (port == nullptr) {
    mm::MMStdBase::mmPrint("[skt] not exit %s\n", server);
    return false;
  }

  if (port->unknown15c == SERVER_OPTION_UNKNOWN_1) {
    return false;
  }

  if (port->unknown48 != nullptr) {
    port->unknown48->unknown20(command);
    return true;
  }
  return false;
}

bool CommandManager::sendCommandHtcs(const char *server, const char *command) {
  CommandManager *manager = get();
  if (manager == nullptr) {
    return false;
  }

  PortInfo *port = manager->findHtcsPortInfo(server);
  if (port == nullptr) {
    mm::MMStdBase::mmPrint("[skt] not exit %s\n", server);
    return false;
  }

  if (port->unknown48 != nullptr) {
    port->unknown48->unknown20(command);
    return true;
  }
  return false;
}

void CommandManager::closeServer(const char *server) {
  CommandManager *manager = get();
  if (manager != nullptr) {
    manager->removePort(server, NETWORK_MODE_UNKNOWN_1);
  }
}

bool CommandManager::openClient(const PortRegistInfo &info) { return false; }

void CommandManager::closeClient(const char *server) {
  CommandManager *manager = get();
  if (manager != nullptr) {
    manager->removePort(server, NETWORK_MODE_UNKNOWN_2);
  }
}

bool CommandManager::isConnectedHtcs(const char *server) {
  CommandManager *manager = get();
  if (manager == nullptr) {
    return false;
  }
  return manager->findHtcsPortInfo(server) != nullptr;
}

bool CommandManager::setServerOption(const char *server, SERVER_OPTION option) { return false; }

bool CommandManager::updateHtcsPortInfo(size_t unknown) { return false; }

CommandManager::PortInfo *CommandManager::findPortInfo(u16 port, const char *name) {
  mm::threading::CS lock(unknown3120);
  for (PortInfo *info = unknown08.begin(); info != unknown08.end(); ++info) {
    if (strcmp(info->unknown0c.c_str(), name) == 0) {
      return info;
    }
  }
  return nullptr;
}

CommandManager::PortInfo *CommandManager::findPortInfoFromID(u32 id) {
  mm::threading::CS lock(unknown3120);
  for (PortInfo *info = unknown08.begin(); info != unknown08.end(); ++info) {
    if (info->unknown04 == id) {
      return info;
    }
  }
  return nullptr;
}

CommandManager::PortInfo *CommandManager::findHtcsPortInfo(const char *name) {
  mm::threading::CS lock(unknown3120);
  for (PortInfo *info = unknown08.begin(); info != unknown08.end(); ++info) {
    if (strcmp(info->unknown0c.c_str(), name) == 0 && info->unknown158 == NETWORK_MODE_UNKNOWN_3) {
      return info;
    }
  }
  return nullptr;
}

CommandManager::PortInfo *CommandManager::findPortInfoExcludeHtcs(const char *name) {
  mm::threading::CS lock(unknown3120);
  for (PortInfo *info = unknown08.begin(); info != unknown08.end(); ++info) {
    if (strcmp(info->unknown0c.c_str(), name) == 0 && info->unknown158 != NETWORK_MODE_UNKNOWN_3) {
      return info;
    }
  }
  return nullptr;
}

u16 CommandManager::getTargetPortNo(const char *name) {
  u16 result = 0;
  if (name != nullptr && *name != '\0') {
    mm::threading::CS lock(unknown3120);
    for (const unknown002 *port = unknown2c10.begin(); port != unknown2c10.end(); ++port) {
      if (strcmp(port->unknown04.c_str(), name) == 0) {
        result = port->unknown00;
        break;
      }
    }
  }
  return result;
}

u32 CommandManager::thServerExecute(void *argument) {
  CommandManager *manager = get();
  if (manager != nullptr && manager->unknown3148) {
    u32 id = static_cast<u32>(reinterpret_cast<size_t>(argument));
    PortInfo *port = manager->findPortInfoFromID(id);
    if (port == nullptr) {
      mm::MMStdBase::mmPrint("port not found!! portID:%d\n", id);
    } else if (port->unknown48 != nullptr) {
      port->unknown48->unknown30(manager);
    }
  }
  return 0;
}

u32 CommandManager::thClientExecute(void *argument) {
  CommandManager *manager = get();
  if (manager != nullptr && manager->unknown3148) {
    u32 id = static_cast<u32>(reinterpret_cast<size_t>(argument));
    PortInfo *port = manager->findPortInfoFromID(id);
    if (port == nullptr) {
      mm::MMStdBase::mmPrint("port not found!! portID:%d\n", id);
    } else if (port->unknown48 != nullptr) {
      port->unknown48->unknown30(manager);
    }
  }
  return 0;
}

void CommandManager::notifyDisconnect(u32 id) {
  CommandManager *manager = get();
  if (manager != nullptr && manager->unknown3148) {
    PortInfo *port = manager->findPortInfoFromID(id);
    if (port != nullptr) {
      mm::threading::CS lock(manager->unknown3120);
      if (port->unknown38 != nullptr) {
        port->unknown38->OnDisconnect(port->unknown0c.c_str());
      }
    }
  }
}

} // namespace skt

template mm::mtl::PtrSingleton<skt::CommandManager>::~PtrSingleton();
