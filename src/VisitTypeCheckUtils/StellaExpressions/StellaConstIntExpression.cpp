#include "../StellaExpression.h"

StellaConstIntExpression::StellaConstIntExpression() {
  this->type = STELLA_EXPRESSION_TYPE_CONST_INT;
}
StellaType StellaConstIntExpression::getStellaType() {
  return StellaType("nat");
}
bool StellaConstIntExpression::isTypingCorrect() { return true; }
