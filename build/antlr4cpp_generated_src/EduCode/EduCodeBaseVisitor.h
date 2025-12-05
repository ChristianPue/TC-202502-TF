
// Generated from /mnt/c/TC-202502/TC-202502-TF/src/EduCode.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "EduCodeVisitor.h"


/**
 * This class provides an empty implementation of EduCodeVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  EduCodeBaseVisitor : public EduCodeVisitor {
public:

  virtual std::any visitProgram(EduCodeParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(EduCodeParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(EduCodeParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclaration(EduCodeParser::VarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(EduCodeParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(EduCodeParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignExpr(EduCodeParser::AssignExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrintStatement(EduCodeParser::PrintStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReadStatement(EduCodeParser::ReadStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(EduCodeParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSwitchStatement(EduCodeParser::SwitchStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaseClause(EduCodeParser::CaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(EduCodeParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDoWhileStatement(EduCodeParser::DoWhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(EduCodeParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayDeclaration(EduCodeParser::ArrayDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAssignment(EduCodeParser::ArrayAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAccess(EduCodeParser::ArrayAccessContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForEachStatement(EduCodeParser::ForEachStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(EduCodeParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntExpr(EduCodeParser::IntExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddSubExpr(EduCodeParser::AddSubExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReadExpr(EduCodeParser::ReadExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(EduCodeParser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulDivModExpr(EduCodeParser::MulDivModExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparisonExpr(EduCodeParser::ComparisonExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpr(EduCodeParser::ParenExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringExpr(EduCodeParser::StringExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLengthExpr(EduCodeParser::LengthExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatExpr(EduCodeParser::FloatExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayAccessExpr(EduCodeParser::ArrayAccessExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotExpr(EduCodeParser::NotExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolExpr(EduCodeParser::BoolExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdExpr(EduCodeParser::IdExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(EduCodeParser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

