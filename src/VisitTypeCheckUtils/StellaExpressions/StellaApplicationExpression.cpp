#include "../StellaExpression.h"
#include "../StellaType.h"

StellaApplicationExpression::StellaApplicationExpression() {
  this->type = STELLA_EXPRESSION_TYPE_APPLICATION;
}

StellaType StellaApplicationExpression::getStellaType() {
  if (!this->isParsed()) {
    return StellaType();
  }

  if (expression1->type == STELLA_EXPRESSION_TYPE_ABSTRACTION ||
      expression1->type == STELLA_EXPRESIION_TYPE_VAR ||
      expression1->type == STELLA_EXPRESSION_TYPE_APPLICATION) {
    return expression1->getStellaType().getReturnType();
  }

  return StellaType();
}

bool StellaApplicationExpression::isTypingCorrect() {
  if (!this->isParsed()) {
    return false;
  }
  if (!this->expression1->isTypingCorrect() ||
      !this->expression2->isTypingCorrect()) {
    return false;
  }

  if (expression1->type == STELLA_EXPRESSION_TYPE_ABSTRACTION ||
      expression1->type == STELLA_EXPRESIION_TYPE_VAR ||
      expression1->type == STELLA_EXPRESSION_TYPE_APPLICATION) {
    return expression1->getStellaType().getParamType() ==
           expression2->getStellaType();
  }

  return false;
}

void StellaApplicationExpression::proxyIdent(Stella::StellaIdent ident) {
  if (!this->expression1->isParsed()) {
    return this->expression1->proxyIdent(ident);
  }
  this->expression2->proxyIdent(ident);
}

void StellaApplicationExpression::proxyExpressionTypeToken(
    std::string typeToken) {
  if (!this->expression1->isParsed()) {
    return this->expression1->proxyExpressionTypeToken(typeToken);
  }
  this->expression2->proxyExpressionTypeToken(typeToken);
}

void StellaApplicationExpression::proxyExpression(
    StellaExpression *expression) {
  if (this->expression1 == NULL) {
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

bool StellaApplicationExpression::isParsed() {
  return this->expression1 != NULL && this->expression2 != NULL &&
         this->expression1->isParsed() && this->expression2->isParsed();
}