#include "../StellaExpression.h"
#include <iostream>

StellaAbstractionExpression::StellaAbstractionExpression() {
  this->type = STELLA_EXPRESSION_TYPE_ABSTRACTION;
}
StellaType StellaAbstractionExpression::getStellaType() {
  return StellaType(this->paramType, this->expression->getStellaType());
}
bool StellaAbstractionExpression::isTypingCorrect() {
  bool isCorrect = this->expression->isTypingCorrect();

  if (!isCorrect) {
    std::cout << "\tin abstraction" << std::endl;
  }

  return isCorrect;
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
    this->expression->setContext(this->context);
    this->expression->addContext(this->paramIdent, this->paramType);
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
bool StellaAbstractionExpression::isParsed() {
  return this->paramIdent != "" && this->paramType.isCompleted() &&
         this->expression != NULL && this->expression->isParsed();
}
