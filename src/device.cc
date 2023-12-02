#include "alpp/device.h"

#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "AL/alc.h"

#include "alpp/util.h"

constexpr std::string_view OPENAL_SOFT_PREFIX = "OpenAL Soft on ";
constexpr std::size_t OPENAL_SOFT_PREFIX_LEN = OPENAL_SOFT_PREFIX.length();

namespace alpp {

struct Device::AL {
  ALCdevice* alc_device;
};

Device::Device() : al_(nullptr){};

Device::Device(const std::string& str) : al_(nullptr), name_(str) {
  sanitize_name_();
}

Device::Device(std::string&& str) : al_(nullptr), name_(std::move(str)) {
  sanitize_name_();
}

Device::~Device() {
  if (al_ == nullptr) {
    return;
  }

  delete al_;
}

std::string_view Device::name() const {
  return name_sanitized_;
}

bool Device::open() {
  if (al_ != nullptr) {
    return true;
  }
  al_ = new Device::AL;
  al_->alc_device = (this == &DEFAULT) ? alcOpenDevice(nullptr) : alcOpenDevice(name_.c_str());
  AL_CHECK_ERROR();
  return al_->alc_device != nullptr;
}

const Device Device::DEFAULT{};

const std::vector<Device>& Device::get_devices(bool refresh) {
  if (!refresh) {
    return devices_;
  }
  devices_.clear();
  const char* devs_str = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
  const char* dev_str_begin = devs_str;
  const char* dev_str_end = dev_str_begin;
  while (true) {
    if (*dev_str_begin == '\0') {
      // list end
      break;
    }
    if (*dev_str_end == '\0') {
      // item end
      devices_.emplace_back(Device{
        std::string{dev_str_begin, dev_str_end}
      });
      dev_str_begin = dev_str_end + 1;
    }
    dev_str_end += 1;
  }
  return devices_;
}

void Device::sanitize_name_() {
  std::string_view name_v{name_};
  name_sanitized_
    = (name_v.substr(0, OPENAL_SOFT_PREFIX_LEN) == OPENAL_SOFT_PREFIX) ? name_v.substr(OPENAL_SOFT_PREFIX_LEN) : name_v;
}

/* NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables) */
std::vector<Device> Device::devices_{};

} // namespace alpp
