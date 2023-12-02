#include "alpp/device.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

void foo(const char* file, const std::uint_fast32_t line) {
  std::cout << "In " << file << ", line " << line << '\n';
}

int main(int argc, const char* argv[]) {
  std::vector<alpp::Device> devices = alpp::Device::get_devices();
  for (std::size_t i = 0; i < devices.size(); i++) {
    std::cout << i + 1 << ". " << devices[i].name() << '\n';
  }
  std::cout << "Your choice: ";
  std::size_t choice{0};
  std::cin >> choice;
  choice--;
  std::cout << "Using device '" << devices[choice].name() << "'\n";
  return 0;
}
