#ifndef STELLA_FUNCTION_HEADER
#define STELLA_FUNCTION_HEADER

#include "../Stella/Absyn.H"
#include "StellaExpression.h"
#include "StellaType.h"
#include <map>

class StellaFunction {
public:
  Stella::StellaIdent ident;
  Stella::StellaIdent paramIdent;
  StellaType paramType;
  StellaType returnType;
  StellaExpression *expression;
  std::map<Stella::StellaIdent, StellaType> context;

  StellaFunction(Stella::StellaIdent ident,
                 std::map<Stella::StellaIdent, StellaType> context);
  void setParamIdent(Stella::StellaIdent paramName);
  void assembleParamType(std::string paramType);
  void assembleReturnType(std::string returnType);
  void setExpression(StellaExpression *expression);
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  void proxyIdent(Stella::StellaIdent ident);
  bool isTypingCorrect();
};

#endif