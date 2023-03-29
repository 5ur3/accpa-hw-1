#ifndef STELLA_FUNCTION_HEADER
#define STELLA_FUNCTION_HEADER

#include "StellaExpression.h"
#include "StellaType.h"
#include <map>

// Representation of a defined stella function
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
  void assembleParamType(std::string paramTypeToken);
  void assembleReturnType(std::string returnTypeToken);
  void setExpression(StellaExpression *expression);
  bool isTypingCorrect();

  // Methods below are used to pass things down the tree.
  // For example, if stella source function's expression is "return succ(0);",
  // expression for "succ" will become "StellaFunction.expression",
  // and expression for "0" will be proxied to "succ" expression via
  // "proxyExpression" method below and can be accessed as
  // "StellaFunction.expression.expression"
  void proxyExpressionTypeToken(std::string typeToken);
  void proxyExpression(StellaExpression *expression);
  void proxyIdent(Stella::StellaIdent ident);
};

#endif
