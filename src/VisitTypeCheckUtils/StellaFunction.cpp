#include "StellaFunction.h"

StellaFunction::StellaFunction(Stella::StellaIdent ident, std::map<Stella::StellaIdent, StellaType> context) {
  this->ident = ident;
  this->context = context;
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
  this->expression->setContext(this->context);
  this->expression->addContext(this->paramName, this->paramType);
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
  return this->returnType == this->expression->getStellaType() &&
         this->expression->isTypingCorrect();
}