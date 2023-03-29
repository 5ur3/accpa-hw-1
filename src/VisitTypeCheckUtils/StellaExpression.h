#ifndef STELLA_EXPRESSION_HEADER
#define STELLA_EXPRESSION_HEADER

#include "../Stella/Absyn.H"
#include "StellaType.h"
#include <map>

enum StellaExpressionType {
  STELLA_EXPRESSION_TYPE_CONST_INT = 0,
  STELLA_EXPRESSION_TYPE_CONST_BOOL = 1,
  STELLA_EXPRESSION_TYPE_VAR = 2,
  STELLA_EXPRESSION_TYPE_SUCC = 3,
  STELLA_EXPRESSION_TYPE_NAT_REC = 4,
  STELLA_EXPRESSION_TYPE_ABSTRACTION = 5,
  STELLA_EXPRESSION_TYPE_APPLICATION = 6,
  STELLA_EXPRESSION_TYPE_CONDITION = 7
};

// Representation of any stella expression
class StellaExpression {
public:
  StellaExpressionType type;

  // Context gets read only in StellaVarExpression to determine it's type.
  // In other StellaExpression implementations it is just passed down the tree.
  //
  // Functions and abstractions not only pass the context down the tree,
  // they also add its params to the context of encosed expression
  std::map<Stella::StellaIdent, StellaType> context;

  // These methods have to be overriden for every StellaExpression
  // implementation
  virtual StellaType getStellaType() = 0;
  virtual bool isTypingCorrect() = 0;

  // Some leaf StellaExpression implementation, such as
  // StellaConstIntExpression, have no inner expression, no ident and no
  // user-defined type declarations.
  //
  // For those expressions, default
  // implementations of methods below are written here.
  virtual void proxyIdent(Stella::StellaIdent ident){};
  virtual void proxyExpressionTypeToken(std::string typeToken){};
  virtual void proxyExpression(StellaExpression *expression){};
  virtual bool isParsed() { return true; };

  // Context setter methods are common among all StellaExpression
  // implementations
  void setContext(std::map<Stella::StellaIdent, StellaType> context) {
    this->context = context;
  };
  void addContext(Stella::StellaIdent ident, StellaType type) {
    if (!this->context.count(ident)) {
      this->context.insert({ident, type});
    } else {
      this->context[ident] = type;
    }
  };
};

// All StellaExpression declarations are written below
class StellaConstIntExpression : public StellaExpression {
public:
  StellaConstIntExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
};

class StellaConstBoolExpression : public StellaExpression {
public:
  StellaConstBoolExpression();
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

class StellaSuccExpression : public StellaExpression {
public:
  StellaExpression *expression = NULL;
  StellaSuccExpression();
  StellaType getStellaType();

  bool isTypingCorrect();
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  void proxyIdent(Stella::StellaIdent ident);
  bool isParsed();
};

class StellaNatRecExpression : public StellaExpression {
public:
  StellaExpression *n = NULL;
  StellaExpression *z = NULL;
  StellaExpression *s = NULL;

  StellaNatRecExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  void proxyIdent(Stella::StellaIdent ident);
  bool isParsed();
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

class StellaConditionExpression : public StellaExpression {
public:
  StellaExpression *condition = NULL;
  StellaExpression *expression1 = NULL;
  StellaExpression *expression2 = NULL;

  StellaConditionExpression();
  StellaType getStellaType();
  bool isTypingCorrect();
  void proxyIdent(Stella::StellaIdent ident);
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  bool isParsed();
};

#endif
