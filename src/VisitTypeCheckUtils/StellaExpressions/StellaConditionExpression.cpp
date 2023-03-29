#include "../StellaExpression.h"

StellaConditionExpression::StellaConditionExpression() {
  this->type = STELLA_EXPRESSION_TYPE_CONDITION;
}
StellaType StellaConditionExpression::getStellaType() {
  if (!this->isParsed() || !this->isTypingCorrect()) {
    return StellaType();
  }

  return expression1->getStellaType();
}
bool StellaConditionExpression::isTypingCorrect() {
  if (!this->isParsed()) {
    return false;
  }
  if (!this->condition->isTypingCorrect() ||
      !this->expression1->isTypingCorrect() ||
      !this->expression2->isTypingCorrect()) {
    return false;
  }

  return condition->getStellaType() == StellaType("bool") &&
         expression1->getStellaType() == expression2->getStellaType();
}
void StellaConditionExpression::proxyIdent(Stella::StellaIdent ident) {
  if (!this->condition->isParsed()) {
    return this->condition->proxyIdent(ident);
  }
  if (!this->expression1->isParsed()) {
    return this->expression1->proxyIdent(ident);
  }
  this->expression2->proxyIdent(ident);
}
void StellaConditionExpression::proxyExpressionTypeToken(
    std::string typeToken) {
  if (!this->condition->isParsed()) {
    return this->condition->proxyExpressionTypeToken(typeToken);
  }
  if (!this->expression1->isParsed()) {
    return this->expression1->proxyExpressionTypeToken(typeToken);
  }
  this->expression2->proxyExpressionTypeToken(typeToken);
}
void StellaConditionExpression::proxyExpression(StellaExpression *expression) {
  if (this->condition == NULL) {
    this->condition = expression;
    this->condition->setContext(this->context);
  } else if (!this->condition->isParsed()) {
    this->condition->proxyExpression(expression);
  } else if (this->expression1 == NULL) {
    this->expression1 = expression;
    this->expression1->setContext(this->context);
  } else if (!this->expression1->isParsed()) {
    this->expression1->proxyExpression(expression);
  } else if (this->expression2 == NULL) {
    this->expression2 = expression;
    this->expression2->setContext(this->context);
  } else {
    this->expression2->proxyExpression(expression);
  }
}
bool StellaConditionExpression::isParsed() {
  return this->condition != NULL && this->expression1 != NULL &&
         this->expression2 != NULL && this->condition->isParsed() &&
         this->expression1->isParsed() && this->expression2->isParsed();
}
