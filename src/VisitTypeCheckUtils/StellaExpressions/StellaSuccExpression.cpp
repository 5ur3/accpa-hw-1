#include "../StellaExpression.h"

StellaSuccExpression::StellaSuccExpression() {
    this->type = STELLA_EXPRESSION_TYPE_SUCC;
}
StellaType StellaSuccExpression::getStellaType() {
  return StellaType("nat");
}
bool StellaSuccExpression::isTypingCorrect() {
  return this->isParsed() && this->expression->getStellaType() == StellaType("nat");
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
