#include "StellaFunction.h"
#include <iostream>

StellaFunction::StellaFunction(
    Stella::StellaIdent ident,
    std::map<Stella::StellaIdent, StellaType> context) {
  this->ident = ident;
  this->context = context;
}
void StellaFunction::setParamIdent(Stella::StellaIdent paramIdent) {
  this->paramIdent = paramIdent;
}
void StellaFunction::assembleParamType(std::string paramType) {
  this->paramType.parse(paramType);
}
void StellaFunction::assembleReturnType(std::string returnType) {
  this->returnType.parse(returnType);
}
void StellaFunction::setExpression(StellaExpression *expression) {
  this->expression = expression;
  this->expression->setContext(this->context);
  this->expression->addContext(this->paramIdent, this->paramType);
}
void StellaFunction::proxyExpressionTypeToken(std::string typeToken) {
  this->expression->proxyExpressionTypeToken(typeToken);
}
void StellaFunction::proxyExpression(StellaExpression *expression) {
  this->expression->proxyExpression(expression);
}
void StellaFunction::proxyIdent(Stella::StellaIdent ident) {
  this->expression->proxyIdent(ident);
}
bool StellaFunction::isTypingCorrect() {
  bool isCorrect = true;
  if (!this->expression->isTypingCorrect()) {
    isCorrect = false;
  } else if (this->returnType != this->expression->getStellaType()) {
    std::cout << "Type error: function return and function expression types "
                 "are mismatched"
              << std::endl;
    isCorrect = false;
  }

  if (!isCorrect) {
    std::cout << "\tin function \"" << this->ident << "\"" << std::endl;
  }
  return isCorrect;
}