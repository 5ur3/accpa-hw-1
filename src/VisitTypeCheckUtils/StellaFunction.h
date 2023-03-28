#ifndef STELLA_FUNCTION_HEADER
#define STELLA_FUNCTION_HEADER

#include "StellaType.h"
#include "StellaExpression.h"
#include "../Stella/Absyn.H"

class StellaFunction {
public:
  Stella::StellaIdent ident;
  Stella::StellaIdent paramName;
  StellaType paramType;
  StellaType returnType;
  StellaExpression *expression;

  StellaFunction();
  StellaFunction(Stella::StellaIdent ident);
  void setParamName(Stella::StellaIdent paramName);
  void assembleParamType(std::string paramType);
  void assembleReturnType(std::string returnType);
  void setExpression(StellaExpression *expression);
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  void proxyIdent(Stella::StellaIdent ident);
  void addContext();
  bool isTypingCorrect();
};

#endif