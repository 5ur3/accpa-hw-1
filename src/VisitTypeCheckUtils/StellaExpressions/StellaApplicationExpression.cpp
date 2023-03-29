#include "../StellaExpression.h"
#include <iostream>

StellaApplicationExpression::StellaApplicationExpression() {
  this->type = STELLA_EXPRESSION_TYPE_APPLICATION;
}

StellaType StellaApplicationExpression::getStellaType() {
  return expression1->getStellaType().getReturnType();
}

bool StellaApplicationExpression::isTypingCorrect() {
  if (!this->isParsed()) {
    return false;
  }

  bool isCorrect = true;
  if (!this->expression1->isTypingCorrect() ||
      !this->expression2->isTypingCorrect()) {
    isCorrect = false;
  } else if (!expression1->getStellaType().isFunction()) {
    std::cout << "Type error: applying non function" << std::endl;
    isCorrect = false;
  } else if (expression1->getStellaType().getParamType() !=
             expression2->getStellaType()) {
    std::cout << "Type error: applying type \""
              << expression2->getStellaType().type_string << "\""
              << " to a function expecting \""
              << expression1->getStellaType().getParamType().type_string << "\""
              << std::endl;
    isCorrect = false;
  }

  if (!isCorrect) {
    std::cout << "\tin application" << std::endl;
  }

  return isCorrect;
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