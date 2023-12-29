#ifndef ALPP_ALPP_DEVICE_H_
#define ALPP_ALPP_DEVICE_H_

#include <string>
#include <string_view>
#include <vector>

namespace alpp {

class Device {
public:
  Device(const Device&) = default;
  Device(Device&&) noexcept = default;
  Device& operator=(const Device&) = default;
  Device& operator=(Device&&) noexcept = default;

  virtual ~Device();

  [[nodiscard]] std::string_view name() const;
  bool open();
  [[nodiscard]] bool is_opened() const;

  static const Device DEFAULT;
  static const std::vector<Device>& get_devices(bool refresh = true);

  friend bool operator==(const Device& l, const Device& r);
  friend bool operator!=(const Device& l, const Device& r);

protected:
  Device();
  explicit Device(const std::string& str);
  explicit Device(std::string&& str);

  void* alc_device_;

  std::string name_;
  std::string_view name_sanitized_;

  void sanitize_name_();

  /* NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables) */
  static std::vector<Device> devices_;
};

} // namespace alpp

#endif // ALPP_ALPP_DEVICE_H_
