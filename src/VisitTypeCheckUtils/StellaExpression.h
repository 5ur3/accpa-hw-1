#ifndef STELLA_EXPRESSION_HEADER
#define STELLA_EXPRESSION_HEADER

#include "../Stella/Absyn.H"
#include "StellaType.h"
#include <map>

enum StellaExpressionType {
  STELLA_EXPRESIION_TYPE_CONST_INT = 0,
  STELLA_EXPRESIION_TYPE_VAR = 1,
  STELLA_EXPRESSION_TYPE_ABSTRACTION = 2,
  STELLA_EXPRESSION_TYPE_APPLICATION = 3
};

class StellaExpression {
public:
  StellaExpressionType type;
  std::map<Stella::StellaIdent, StellaType> context;

  virtual StellaType getStellaType() = 0;
  virtual bool isTypingCorrect() = 0;
  virtual void proxyIdent(Stella::StellaIdent ident){};
  virtual void proxyExpressionTypeToken(std::string typeToken){};
  virtual void proxyExpression(StellaExpression *expression){};
  virtual bool isParsed() { return true; };
  void setContext(std::map<Stella::StellaIdent, StellaType> context) {
    this->context = context;
  };
  void addContext(Stella::StellaIdent ident, StellaType type) {
    this->context.insert({ident, type});
  };
};

class StellaConstIntExpression : public StellaExpression {
public:
  StellaConstIntExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
};

class StellaVarExpression : public StellaExpression {
public:
  Stella::StellaIdent ident;
  StellaVarExpression(Stella::StellaIdent ident);
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
  bool isParsed();
};

class StellaApplicationExpression : public StellaExpression {
public:
  StellaExpression *expression1 = NULL;
  StellaExpression *expression2 = NULL;

  StellaApplicationExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
  void proxyIdent(Stella::StellaIdent ident);
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  bool isParsed();
};

#endif
