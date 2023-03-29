#include "../StellaExpression.h"
#include "../StellaType.h"
#include <iostream>

StellaVarExpression::StellaVarExpression(Stella::StellaIdent ident) {
  this->type = STELLA_EXPRESSION_TYPE_VAR;
  this->ident = ident;
}
StellaType StellaVarExpression::getStellaType() {
  if (!this->context.count(this->ident)) {
    return StellaType();
  }
  return this->context[this->ident];
}
bool StellaVarExpression::isTypingCorrect() {
  bool isCorrect = this->context.count(this->ident);

  if (!isCorrect) {
    std::cout << "Error: ident \"" + this->ident + "\" is not declared"
              << std::endl;
  }

  return isCorrect;
}
