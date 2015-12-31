#ifndef _UTIL_H
#define _UTIL_H

#include "types.h"

#include <string>

namespace util
{
  bool isInteger(const std::string &s);
  bool isNumber(const std::string &s);

  int    str2int(const std::string &s);
  double str2num(const std::string &s);

  std::string str2key(const std::string &s);

  std::string int2str(int n);
  std::string num2str(double n);

  StringList_t tokenize(std::string);
};

#endif // _UTIL_H
