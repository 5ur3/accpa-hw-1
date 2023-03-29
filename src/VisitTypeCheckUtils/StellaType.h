#ifndef STELLA_TYPE_HEADER
#define STELLA_TYPE_HEADER

#include <string>
#include <deque>
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
  StellaType getParamType();
  StellaType getReturnType();
};

#endif