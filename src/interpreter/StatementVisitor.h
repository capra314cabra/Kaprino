#pragma once

#include "../parser/KaprinoParserBaseVisitor.h"

class StatementVisitor : public KaprinoParserBaseVisitor {
   public:
    virtual antlrcpp::Any visitProgram(KaprinoParser::ProgramContext *ctx) override;

    virtual antlrcpp::Any visitPrintStatement(KaprinoParser::PrintStatementContext *ctx) override;

    virtual antlrcpp::Any visitNumberExpr(KaprinoParser::NumberExprContext *ctx) override;
};