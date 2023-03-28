#include "../StellaExpression.h"

StellaConstIntExpression::StellaConstIntExpression() {
  this->type = STELLA_EXPRESIION_TYPE_CONST_INT;
}
StellaType StellaConstIntExpression::getStellaType() {
  return StellaType("nat");
}
bool StellaConstIntExpression::isTypingCorrect() { return true; }
