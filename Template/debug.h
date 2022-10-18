#include <bits/stdc++.h>
using namespace std;

namespace DEBUG {
template <typename T>
inline void _debug(const char* format, T t) {
  cerr << format << '=' << t << endl;
}

template <class First, class... Rest>
inline void _debug(const char* format, First first, Rest... rest) {
  while (*format != ',') cerr << *format++;
  cerr << '=' << first << ",";
  _debug(format + 1, rest...);
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& V) {
  os << "[ ";
  for (const auto& vv : V) os << vv << ", ";
  os << "]";
  return os;
}

#define debug(...) _debug(#__VA_ARGS__, __VA_ARGS__)
}  // namespace DEBUG

//using namespace DEBUG;
