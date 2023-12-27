#ifndef ALPP_ALPP_UTIL_H_
#define ALPP_ALPP_UTIL_H_

#include <cstdint>

#define AL_CHECK_ERROR() alpp::al_check_error(__FILE__, __LINE__)

namespace alpp {

void al_check_error(const char* file, std::uint_fast32_t line);

} // namespace alpp

#endif // ALPP_ALPP_UTIL_H_
