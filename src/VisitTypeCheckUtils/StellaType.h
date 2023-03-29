#ifndef STELLA_TYPE_HEADER
#define STELLA_TYPE_HEADER

#include <deque>
#include <string>
#include <vector>

class StellaType {
public:
  std::string type_string = "";

  StellaType();
  StellaType(std::string type_string);
  StellaType(StellaType functionParamType, StellaType functionReturnType);

  bool isCompletedRecursive(std::deque<std::string> &remainingTokens);
  bool isCompleted();
  void parse(std::string typeToken);
  bool operator==(const StellaType &stellaType) const;
  bool operator!=(const StellaType &stellaType) const;
  bool isFunction();
  StellaType getParamType();
  StellaType getReturnType();
};

#endif