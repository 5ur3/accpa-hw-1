#include "StellaType.h"
#include <deque>
#include <string>
#include <vector>

void onTypeParsingEnd();

bool StellaType::isCompletedRecursive(
    std::deque<std::string> &remainingTokens) {
  if (remainingTokens.empty()) {
    return false;
  }

  std::string token = remainingTokens.front();
  remainingTokens.pop_front();

  if (token == "nat") {
    return true;
  }
  if (token == "fun") {
    return isCompletedRecursive(remainingTokens) &&
           isCompletedRecursive(remainingTokens);
  }
  return false;
}

bool StellaType::isCompleted() {
  std::vector<std::string> type_vector;
  std::string acc = "";
  for (int i = 0; i < this->type_string.size(); i++) {
    if (this->type_string[i] == ' ') {
      type_vector.push_back(acc);
      acc = "";
    } else {
      acc += this->type_string[i];
    }
  }
  type_vector.push_back(acc);

  std::deque<std::string> tokens;
  tokens.insert(tokens.begin(), type_vector.begin(), type_vector.end());
  return isCompletedRecursive(tokens);
}

StellaType::StellaType(){};
StellaType::StellaType(std::string type_string) { this->type_string = type_string; };
StellaType::StellaType(StellaType functionParamType, StellaType functionReturnType) {
  this->type_string = "fun " + functionParamType.type_string + " " +
                      functionReturnType.type_string;
};

void StellaType::parse(std::string typeToken) {
  if (type_string == "") {
    type_string = typeToken;
  } else {
    type_string += " ";
    type_string += typeToken;
  }

  if (isCompleted()) {
    onTypeParsingEnd();
  }
}

bool StellaType::operator==(const StellaType &stellaType) const {
  return (this->type_string == stellaType.type_string);
}
