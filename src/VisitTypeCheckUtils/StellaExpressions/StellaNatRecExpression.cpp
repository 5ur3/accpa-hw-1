#include "../StellaExpression.h"
#include <iostream>

StellaNatRecExpression::StellaNatRecExpression() {
  this->type = STELLA_EXPRESSION_TYPE_NAT_REC;
}
StellaType StellaNatRecExpression::getStellaType() {
  return z->getStellaType();
}
bool StellaNatRecExpression::isTypingCorrect() {
  if (!this->isParsed()) {
    return false;
  }

  bool isCorrect = true;
  if (!n->isTypingCorrect() || !z->isTypingCorrect() || !s->isTypingCorrect()) {
    isCorrect = false;
  } else if (n->getStellaType() != StellaType("nat")) {
    std::cout << "Type error: Nat::rec \"n\" is not Nat" << std::endl;
    isCorrect = false;
  } else if (!s->getStellaType().isFunction() ||
             !s->getStellaType().getReturnType().isFunction() ||
             s->getStellaType().getParamType() != StellaType("nat") ||
             s->getStellaType().getReturnType().getParamType() !=
                 s->getStellaType().getReturnType().getReturnType()) {
    std::cout << "Type error: Nat::rec \"s\" is not a function with signature "
                 "fn(Nat) "
                 "-> (fn(T) -> T)"
              << std::endl;
    isCorrect = false;
  } else if (z->getStellaType() !=
             s->getStellaType().getReturnType().getParamType()) {
    std::cout
        << "Type error: Nat::rec \"z\" type if mismatched (expected \"" +
               s->getStellaType().getReturnType().getParamType().type_string +
               "\", got \"" + z->getStellaType().type_string + "\")"
        << std::endl;
    isCorrect = false;
  }

  if (!isCorrect) {
    std::cout << "\tin Nat::rec" << std::endl;
  }

  return isCorrect;
}
void StellaNatRecExpression::proxyExpressionTypeToken(std::string typeToken) {
  if (!this->n->isParsed()) {
    return this->n->proxyExpressionTypeToken(typeToken);
  }
  if (!this->z->isParsed()) {
    return this->z->proxyExpressionTypeToken(typeToken);
  }
  this->s->proxyExpressionTypeToken(typeToken);
}
void StellaNatRecExpression::proxyExpression(StellaExpression *expression) {
  if (this->n == NULL) {
    this->n = expression;
    this->n->setContext(this->context);
  } else if (!this->n->isParsed()) {
    this->n->proxyExpression(expression);
  } else if (this->z == NULL) {
    this->z = expression;
    this->z->setContext(this->context);
  } else if (!this->z->isParsed()) {
    this->z->proxyExpression(expression);
  } else if (this->s == NULL) {
    this->s = expression;
    this->s->setContext(this->context);
  } else {
    this->s->proxyExpression(expression);
  }
}
void StellaNatRecExpression::proxyIdent(Stella::StellaIdent ident) {
  if (!this->n->isParsed()) {
    return this->n->proxyIdent(ident);
  }
  if (!this->z->isParsed()) {
    return this->z->proxyIdent(ident);
  }
  this->s->proxyIdent(ident);
}
bool StellaNatRecExpression::isParsed() {
  return this->n != NULL && this->z != NULL && this->s != NULL &&
         this->n->isParsed() && this->z->isParsed() && this->s->isParsed();
}
