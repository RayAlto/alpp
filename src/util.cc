#include "alpp/util.h"

#include <cstdint>
#include <stdexcept>

#include "AL/al.h"

namespace alpp {

void al_check_error(const char* file, const std::uint_fast32_t line) {
  int al_error = alGetError();
  if (al_error == AL_NO_ERROR) {
    return;
  }
  std::string msg{"("};
  msg += file;
  msg += ':';
  msg += std::to_string(line);
  msg += ") [OpenAL] ";
  switch (al_error) {
    case AL_INVALID_NAME: msg += "A bad name (ID) was passed to an OpenAL function."; break;
    case AL_INVALID_ENUM: msg += "An invalid enum value was passed to an OpenAL function."; break;
    case AL_INVALID_VALUE: msg += "An invalid value was passed to an OpenAL function."; break;
    case AL_INVALID_OPERATION: msg += "The requested operation is not valid."; break;
    case AL_OUT_OF_MEMORY: msg += "The requested operation resulted in OpenAL running out of memory."; break;
    default: msg += "Unknown error."; break;
  }
  throw std::runtime_error(msg);
}

} // namespace alpp
