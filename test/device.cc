#include "alpp/device.h"

#include <cstddef>
#include <cstdio>
#include <vector>

int main(int argc, const char* argv[]) {
  std::vector<alpp::Device> d0 = alpp::Device::get_devices();
  std::printf("========== devices ==========\n");
  for (std::size_t i = 0; i < d0.size(); i++) {
    std::printf("%02d. %s\n", i + 1, d0[i].name().data());
  }
  std::vector<alpp::Device> d1 = alpp::Device::get_devices();
  std::printf("========== devices ==========\n");
  for (std::size_t i = 0; i < d1.size(); i++) {
    std::printf("%02d. %s\n", i + 1, d1[i].name().data());
  }
  std::printf("%s\n", (d0 == d1 ? "fine" : "fuck"));
  return 0;
}
