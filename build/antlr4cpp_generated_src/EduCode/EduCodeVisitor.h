
// Generated from /mnt/c/TC-202502/TC-202502-TF/src/EduCode.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "EduCodeParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by EduCodeParser.
 */
class  EduCodeVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by EduCodeParser.
   */
    virtual std::any visitProgram(EduCodeParser::ProgramContext *context) = 0;

    virtual std::any visitStatement(EduCodeParser::StatementContext *context) = 0;

    virtual std::any visitBlock(EduCodeParser::BlockContext *context) = 0;

    virtual std::any visitVarDeclaration(EduCodeParser::VarDeclarationContext *context) = 0;

    virtual std::any visitAssignment(EduCodeParser::AssignmentContext *context) = 0;

    virtual std::any visitVarDef(EduCodeParser::VarDefContext *context) = 0;

    virtual std::any visitAssignExpr(EduCodeParser::AssignExprContext *context) = 0;

    virtual std::any visitPrintStatement(EduCodeParser::PrintStatementContext *context) = 0;

    virtual std::any visitReadStatement(EduCodeParser::ReadStatementContext *context) = 0;

    virtual std::any visitIfStatement(EduCodeParser::IfStatementContext *context) = 0;

    virtual std::any visitSwitchStatement(EduCodeParser::SwitchStatementContext *context) = 0;

    virtual std::any visitCaseClause(EduCodeParser::CaseClauseContext *context) = 0;

    virtual std::any visitWhileStatement(EduCodeParser::WhileStatementContext *context) = 0;

    virtual std::any visitDoWhileStatement(EduCodeParser::DoWhileStatementContext *context) = 0;

    virtual std::any visitForStatement(EduCodeParser::ForStatementContext *context) = 0;

    virtual std::any visitArrayDeclaration(EduCodeParser::ArrayDeclarationContext *context) = 0;

    virtual std::any visitArrayAssignment(EduCodeParser::ArrayAssignmentContext *context) = 0;

    virtual std::any visitArrayAccess(EduCodeParser::ArrayAccessContext *context) = 0;

    virtual std::any visitForEachStatement(EduCodeParser::ForEachStatementContext *context) = 0;

    virtual std::any visitExpressionList(EduCodeParser::ExpressionListContext *context) = 0;

    virtual std::any visitIntExpr(EduCodeParser::IntExprContext *context) = 0;

    virtual std::any visitAddSubExpr(EduCodeParser::AddSubExprContext *context) = 0;

    virtual std::any visitReadExpr(EduCodeParser::ReadExprContext *context) = 0;

    virtual std::any visitOrExpr(EduCodeParser::OrExprContext *context) = 0;

    virtual std::any visitMulDivModExpr(EduCodeParser::MulDivModExprContext *context) = 0;

    virtual std::any visitComparisonExpr(EduCodeParser::ComparisonExprContext *context) = 0;

    virtual std::any visitParenExpr(EduCodeParser::ParenExprContext *context) = 0;

    virtual std::any visitStringExpr(EduCodeParser::StringExprContext *context) = 0;

    virtual std::any visitLengthExpr(EduCodeParser::LengthExprContext *context) = 0;

    virtual std::any visitFloatExpr(EduCodeParser::FloatExprContext *context) = 0;

    virtual std::any visitArrayAccessExpr(EduCodeParser::ArrayAccessExprContext *context) = 0;

    virtual std::any visitNotExpr(EduCodeParser::NotExprContext *context) = 0;

    virtual std::any visitBoolExpr(EduCodeParser::BoolExprContext *context) = 0;

    virtual std::any visitIdExpr(EduCodeParser::IdExprContext *context) = 0;

    virtual std::any visitAndExpr(EduCodeParser::AndExprContext *context) = 0;


};

