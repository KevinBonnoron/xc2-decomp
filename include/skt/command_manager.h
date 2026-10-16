#pragma once

namespace skt {

struct PortRegistInfo;

enum SERVER_OPTION : int;

class CommandManager {
public:
  static bool sendCommand(const char *server, const char *command);
  static bool sendCommandHtcs(const char *server, const char *command);
  static bool openServer(const PortRegistInfo &info, SERVER_OPTION option);
  static bool closeServer(const char *server);
  static bool isConnectedHtcs(const char *server);
  static bool setServerOption(const char *server, SERVER_OPTION option);
};

} // namespace skt
