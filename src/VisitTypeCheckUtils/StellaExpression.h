#ifndef STELLA_EXPRESSION_HEADER
#define STELLA_EXPRESSION_HEADER

#include "../Stella/Absyn.H"
#include "StellaType.h"

enum StellaExpressionType {
  STELLA_EXPRESIION_TYPE_CONST_INT = 0,
  STELLA_EXPRESSION_TYPE_ABSTRACTION = 1
};

class StellaExpression {
public:
  StellaExpressionType type;
  virtual StellaType getStellaType() = 0;
  virtual bool isTypingCorrect() = 0;
  virtual void proxyExpressionTypeToken(std::string typeToken){};
  virtual void proxyExpression(StellaExpression *expression){};
  virtual void proxyIdent(Stella::StellaIdent ident){};
};

class StellaConstIntExpression : public StellaExpression {
public:
  StellaConstIntExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
};


class StellaAbstractionExpression : public StellaExpression {
public:
  Stella::StellaIdent paramIdent = "";
  StellaType paramType;
  StellaExpression *expression = NULL;
  StellaAbstractionExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  void proxyIdent(Stella::StellaIdent ident);
};

#endif
