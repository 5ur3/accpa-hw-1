#include "StellaType.h"
#include <deque>
#include <string>
#include <vector>

// helper method. Splits string into vector of strings by a whitespace
std::vector<std::string> split_string(std::string str) {
  std::vector<std::string> vec;
  std::string acc = "";
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ' ') {
      vec.push_back(acc);
      acc = "";
    } else {
      acc += str[i];
    }
  }
  if (acc != "") {
    vec.push_back(acc);
  }

  return vec;
}

// Forward-declaration of one of state machine controlling methods from VisitTypeCheck.cpp
void onTypeParsingEnd();

// Documentation of the class methods is in StellaType.h
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
  if (token == "bool") {
    return true;
  }
  if (token == "fun") {
    return isCompletedRecursive(remainingTokens) &&
           isCompletedRecursive(remainingTokens);
  }
  return false;
}

bool StellaType::isCompleted() {
  std::vector<std::string> type_vector = split_string(this->type_string);

  std::deque<std::string> tokens;
  tokens.insert(tokens.begin(), type_vector.begin(), type_vector.end());
  return isCompletedRecursive(tokens);
}

StellaType::StellaType(){};
StellaType::StellaType(std::string type_string) {
  this->type_string = type_string;
};
StellaType::StellaType(StellaType functionParamType,
                       StellaType functionReturnType) {
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

bool StellaType::isFunction() {
  std::vector<std::string> type_vector = split_string(this->type_string);
  return this->isCompleted() && type_vector[0] == "fun";
}

StellaType StellaType::getParamType() {
  std::vector<std::string> type_vector = split_string(this->type_string);
  if (!this->isCompleted() || type_vector[0] != "fun") {
    return StellaType();
  }

  StellaType paramType;
  for (int i = 1; !paramType.isCompleted(); i++) {
    paramType.parse(type_vector[i]);
  }
  return paramType;
}

StellaType StellaType::getReturnType() {
  std::vector<std::string> type_vector = split_string(this->type_string);
  if (!this->isCompleted() || type_vector[0] != "fun") {
    return StellaType();
  }

  int i;
  StellaType paramType;
  for (i = 1; !paramType.isCompleted(); i++) {
    paramType.parse(type_vector[i]);
  }
  StellaType returnType;
  for (int j = i; j < type_vector.size(); j++) {
    returnType.parse(type_vector[j]);
  }
  return returnType;
}

bool StellaType::operator==(const StellaType &stellaType) const {
  return (this->type_string == stellaType.type_string);
}

bool StellaType::operator!=(const StellaType &stellaType) const {
  return (this->type_string != stellaType.type_string);
}
