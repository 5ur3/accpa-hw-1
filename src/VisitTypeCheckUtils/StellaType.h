#ifndef STELLA_TYPE_HEADER
#define STELLA_TYPE_HEADER

#include <deque>
#include <string>
#include <vector>

// Representation of a stella type. Supports "==" and "!=" operators
class StellaType {
private:
  bool isCompletedRecursive(std::deque<std::string> &remainingTokens);

public:
  // The actual type information is stored in a whitespace-separated string.
  // type_string of "fun fun nat nat bool" is equivalent to
  // "stella type of "fn(fn(Nat) -> Nat) -> Bool"
  std::string type_string = "";

  // Types from stella source have to be built token-by-token.
  // Pass here type token (one of "fun", "nat" or "bool"), and this will add it
  // to the type string
  void parse(std::string typeToken);

  // Since types are often constructed token-by-token, this method is used to
  // check if the type is complete.
  // For example, it returns true for type "fun fun nat nat bool",
  // and false for type "fun fun nat nat"
  bool isCompleted();

  // Default constructor, for token-by-token construction
  StellaType();
  // Sort of a constant type constructor. Used as StellaType("nat") or
  // StellaType("bool")
  StellaType(std::string type_string);
  // Function constructor
  StellaType(StellaType functionParamType, StellaType functionReturnType);

  bool operator==(const StellaType &stellaType) const;
  bool operator!=(const StellaType &stellaType) const;

  // This method is used to check whether the type is a function
  bool isFunction();

  // If the type is a function, you can get param and return types
  StellaType getParamType();
  StellaType getReturnType();
};

#endif