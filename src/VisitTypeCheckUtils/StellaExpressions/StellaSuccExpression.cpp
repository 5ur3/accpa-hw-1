#include "../StellaExpression.h"
#include <iostream>

StellaSuccExpression::StellaSuccExpression() {
  this->type = STELLA_EXPRESSION_TYPE_SUCC;
}
StellaType StellaSuccExpression::getStellaType() { return StellaType("nat"); }
bool StellaSuccExpression::isTypingCorrect() {
  if (!this->isParsed()) {
    return false;
  }

  bool isCorrect = true;
  if (!this->expression->isTypingCorrect()) {
    isCorrect = false;
  } else if (this->expression->getStellaType() != StellaType("nat")) {
    std::cout << "Type error: succ expression type is not Nat" << std::endl;
    isCorrect = false;
  }

  if (!isCorrect) {
    std::cout << "\tin succ" << std::endl;
  }

  return isCorrect;
}
void StellaSuccExpression::proxyExpressionTypeToken(std::string typeToken) {
  this->expression->proxyExpressionTypeToken(typeToken);
}
void StellaSuccExpression::proxyExpression(StellaExpression *expression) {
  if (this->expression == NULL) {
    this->expression = expression;
    this->expression->setContext(this->context);
  } else {
    this->expression->proxyExpression(expression);
  }
}
void StellaSuccExpression::proxyIdent(Stella::StellaIdent ident) {
  this->expression->proxyIdent(ident);
}
bool StellaSuccExpression::isParsed() {
  return this->expression != NULL && this->expression->isParsed();
}
