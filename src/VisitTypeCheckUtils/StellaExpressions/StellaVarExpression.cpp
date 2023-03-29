#include "../StellaExpression.h"
#include "../StellaType.h"
#include <iostream>

StellaVarExpression::StellaVarExpression(Stella::StellaIdent ident) {
  this->type = STELLA_EXPRESIION_TYPE_VAR;
  this->ident = ident;
}
StellaType StellaVarExpression::getStellaType() {
  if (!this->context.count(this->ident)) {
    return StellaType();
  }
  return this->context[this->ident];
}
bool StellaVarExpression::isTypingCorrect() {
  return this->context.count(this->ident);
}
