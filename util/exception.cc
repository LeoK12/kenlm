#include "util/exception.hh"

#include <errno.h>
#include <string.h>

namespace util {

Exception::Exception() throw() {}
Exception::~Exception() throw() {}
Exception::Exception(const Exception &other) throw() : stream_(other.stream_.str()) {}
Exception &Exception::operator=(const Exception &other) throw() { stream_.str(other.stream_.str()); return *this; }
const char *Exception::what() const throw() { return stream_.str().c_str(); }

ErrnoException::ErrnoException() throw() : errno_(errno) {
  char buf[200];
  buf[0] = 0;
#if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && ! _GNU_SOURCE
  const char *add = buf;
  if (!strerror_r(errno, buf, 200)) {
#else
  const char *add = strerror_r(errno, buf, 200);
  if (add) {
#endif
    *this << add << ' ';
  }
}

ErrnoException::~ErrnoException() throw() {}

} // namespace util
