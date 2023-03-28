#include "StellaFunction.h"

StellaFunction::StellaFunction() {}
StellaFunction::StellaFunction(Stella::StellaIdent ident) {
  this->ident = ident;
}
void StellaFunction::setParamName(Stella::StellaIdent paramName) {
  this->paramName = paramName;
}
void StellaFunction::assembleParamType(std::string paramType) {
  this->paramType.parse(paramType);
}
void StellaFunction::assembleReturnType(std::string returnType) {
  this->returnType.parse(returnType);
}
void StellaFunction::setExpression(StellaExpression *expression) {
  this->expression = expression;
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
void StellaFunction::addContext() {}
bool StellaFunction::isTypingCorrect() {
  return this->returnType == this->expression->getStellaType() &&
         this->expression->isTypingCorrect();
}