#include "../StellaExpression.h"

StellaAbstractionExpression::StellaAbstractionExpression() {
  this->type = STELLA_EXPRESSION_TYPE_ABSTRACTION;
}
StellaType StellaAbstractionExpression::getStellaType() {
  return StellaType(this->paramType, this->expression->getStellaType());
}
bool StellaAbstractionExpression::isTypingCorrect() {
  return this->expression->isTypingCorrect();
}
void StellaAbstractionExpression::proxyExpressionTypeToken(
    std::string typeToken) {
  if (this->paramType.isCompleted()) {
    this->expression->proxyExpressionTypeToken(typeToken);
  } else {
    this->paramType.parse(typeToken);
  }
}
void StellaAbstractionExpression::proxyExpression(
    StellaExpression *expression) {
  if (this->expression == NULL) {
    this->expression = expression;
  } else {
    this->expression->proxyExpression(expression);
  }
}
void StellaAbstractionExpression::proxyIdent(Stella::StellaIdent ident) {
  if (this->paramIdent == "") {
    this->paramIdent = ident;
  } else {
    this->expression->proxyIdent(ident);
  }
}
