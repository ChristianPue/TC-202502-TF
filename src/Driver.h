#ifndef DRIVER_H
#define DRIVER_H

#include "antlr4-runtime.h"
#include "EduCodeBaseVisitor.h"
#include "codegen/CodeGenerator.h"
#include "codegen/ExpressionGen.h"
#include "codegen/StatementGen.h"

#include <memory>
#include <any>
#include <vector>

class Driver : public EduCodeBaseVisitor {
private:
    std::unique_ptr<CodeGenerator> codeGen;
    std::unique_ptr<ExpressionGen> exprGen;
    std::unique_ptr<StatementGen> stmtGen;

public:
    Driver() {
        codeGen = std::make_unique<CodeGenerator>();
        exprGen = std::make_unique<ExpressionGen>(codeGen.get());
        stmtGen = std::make_unique<StatementGen>(codeGen.get());
    }

    void saveIR(const std::string& filename) {
        codeGen->saveIR(filename);
    }

    // ==================== PROGRAM ====================
    std::any visitProgram(EduCodeParser::ProgramContext *ctx) override {
        codeGen->createMainFunction();
        visitChildren(ctx);
        codeGen->finalizeMainFunction();
        return std::any();
    }

    // ==================== DECLARACIONES ====================
    std::any visitVarDeclaration(EduCodeParser::VarDeclarationContext *ctx) override {
        return visit(ctx->varDef());
    }

    std::any visitVarDef(EduCodeParser::VarDefContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::string typeStr = ctx->children[0]->getText();
        
        Value* initVal = nullptr;
        if (ctx->expression()) {
            std::any valAny = visit(ctx->expression());
            if (valAny.has_value()) {
                initVal = std::any_cast<Value*>(valAny);
            }
        }

        stmtGen->generateVarDeclaration(name, typeStr, initVal);
        return std::any();
    }

    // ==================== ASIGNACIONES ====================
    std::any visitAssignment(EduCodeParser::AssignmentContext *ctx) override {
        return visit(ctx->assignExpr());
    }

    std::any visitAssignExpr(EduCodeParser::AssignExprContext *ctx) override {
        std::string name = ctx->ID()->getText();
        
        std::any valAny = visit(ctx->expression());
        if (valAny.has_value()) {
            Value* val = std::any_cast<Value*>(valAny);
            stmtGen->generateAssignment(name, val);
        }
        return std::any();
    }

    // ==================== I/O ====================
    std::any visitPrintStatement(EduCodeParser::PrintStatementContext *ctx) override {
        std::vector<Value*> values;
        
        for (auto expr : ctx->expression()) {
            std::any valAny = visit(expr);
            if (valAny.has_value()) {
                values.push_back(std::any_cast<Value*>(valAny));
            }
        }
        
        stmtGen->generatePrint(values);
        return std::any();
    }

    std::any visitReadStatement(EduCodeParser::ReadStatementContext *ctx) override {
        std::vector<std::string> varNames;
        
        for (auto idNode : ctx->ID()) {
            varNames.push_back(idNode->getText());
        }
        
        stmtGen->generateRead(varNames);
        return std::any();
    }

    // ==================== CONTROL DE FLUJO ====================
    std::any visitBlock(EduCodeParser::BlockContext *ctx) override {
        // 1. Abrir nuevo ámbito
        codeGen->getSymbolTable()->pushScope();
        
        // 2. Visitar instrucciones del bloque
        visitChildren(ctx);
        
        // 3. Cerrar ámbito
        codeGen->getSymbolTable()->popScope();
        
        return std::any();
    }

    std::any visitIfStatement(EduCodeParser::IfStatementContext *ctx) override {
        // 1. Evaluar condición
        std::any condAny = visit(ctx->expression(0));
        Value* condVal = std::any_cast<Value*>(condAny);
        
        bool hasElse = (ctx->ELSE() != nullptr);
        
        // 2. Generar estructura if
        auto blocks = stmtGen->generateIfStart(condVal, hasElse);
        
        // 3. Then block
        visit(ctx->block(0));
        
        // 4. Else block (si existe)
        if (hasElse) {
            stmtGen->generateIfElse(blocks);
            visit(ctx->block(1));
        }
        
        // 5. Merge
        stmtGen->generateIfEnd(blocks);
        
        return std::any();
    }

    std::any visitWhileStatement(EduCodeParser::WhileStatementContext *ctx) override {
        // 1. Preparar bloques
        auto blocks = stmtGen->generateWhileStart();
        
        // 2. Evaluar condición
        std::any condAny = visit(ctx->expression());
        Value* condVal = std::any_cast<Value*>(condAny);
        stmtGen->generateWhileCondition(blocks, condVal);
        
        // 3. Cuerpo
        visit(ctx->block());
        
        // 4. Finalizar
        stmtGen->generateWhileEnd(blocks);
        
        return std::any();
    }

    std::any visitDoWhileStatement(EduCodeParser::DoWhileStatementContext *ctx) override {
        // 1. Preparar bloques
        auto blocks = stmtGen->generateDoWhileStart();
        
        // 2. Cuerpo
        visit(ctx->block());
        
        // 3. Condición y finalizar
        std::any condAny = visit(ctx->expression());
        Value* condVal = std::any_cast<Value*>(condAny);
        stmtGen->generateDoWhileEnd(blocks, condVal);
        
        return std::any();
    }

    std::any visitForStatement(EduCodeParser::ForStatementContext *ctx) override {
        // 1. Inicialización
        if (ctx->varDef()) {
            visit(ctx->varDef());
        } else if (ctx->assignExpr().size() > 0 && ctx->children[2] == ctx->assignExpr(0)) {
            visit(ctx->assignExpr(0));
        } else if (ctx->expression().size() > 0 && ctx->children[2] == ctx->expression(0)) {
            visit(ctx->expression(0));
        }

        auto blocks = stmtGen->generateWhileStart();

        // 2. Condición
        EduCodeParser::ExpressionContext* condExpr = nullptr;
        bool firstSemiFound = false;
        for (auto child : ctx->children) {
            if (child->getText() == ";") {
                if (!firstSemiFound) firstSemiFound = true;
                else break;
            } else if (firstSemiFound) {
                if (auto expr = dynamic_cast<EduCodeParser::ExpressionContext*>(child)) {
                    condExpr = expr;
                }
            }
        }

        Value* condVal = nullptr;
        if (condExpr) {
            std::any condAny = visit(condExpr);
            condVal = std::any_cast<Value*>(condAny);
        } else {
            condVal = ConstantInt::get(Type::getInt1Ty(*codeGen->getContext()), 1);
        }

        stmtGen->generateWhileCondition(blocks, condVal);

        // 3. Cuerpo
        visit(ctx->block());

        // 4. Incremento
        if (ctx->assignExpr().size() > 0) {
            bool initIsAssign = (ctx->children[2] == ctx->assignExpr(0));
            size_t updateIdx = initIsAssign ? 1 : 0;
            if (ctx->assignExpr().size() > updateIdx) {
                visit(ctx->assignExpr(updateIdx));
            }
        } else if (ctx->expression().size() > 0) {
            auto lastChild = ctx->children[ctx->children.size()-2];
            if (auto expr = dynamic_cast<EduCodeParser::ExpressionContext*>(lastChild)) {
                visit(expr);
            }
        }

        stmtGen->generateWhileEnd(blocks);
        return std::any();
    }

    std::any visitSwitchStatement(EduCodeParser::SwitchStatementContext *ctx) override {
        // 1. Evaluar expresión
        std::any condAny = visit(ctx->expression());
        Value* switchVal = std::any_cast<Value*>(condAny);

        BasicBlock* defaultBB = nullptr;
        BasicBlock* mergeBB = nullptr;
        SwitchInst* switchInst = stmtGen->generateSwitchStart(switchVal, defaultBB, mergeBB);

        // 2. Generar casos
        for (auto caseCtx : ctx->caseClause()) {
            std::any caseValAny = visit(caseCtx->expression());
            Value* caseValPtr = std::any_cast<Value*>(caseValAny);
            
            ConstantInt* caseConst = dyn_cast<ConstantInt>(caseValPtr);
            if (!caseConst) {
                std::cerr << "Error: Los casos del switch deben ser constantes enteras." << std::endl;
                continue;
            }

            stmtGen->generateSwitchCase(switchInst, caseConst);
            
            for (auto stmt : caseCtx->statement()) {
                visit(stmt);
            }
            
            stmtGen->generateSwitchCaseEnd(mergeBB);
        }

        // 3. Default
        codeGen->getBuilder()->SetInsertPoint(defaultBB);
        if (ctx->DEFAULT()) {
            for (auto stmt : ctx->statement()) {
                visit(stmt);
            }
        }

        stmtGen->generateSwitchEnd(defaultBB, mergeBB);
        return std::any();
    }

    // ==================== ARRAYS ====================
    std::any visitArrayDeclaration(EduCodeParser::ArrayDeclarationContext *ctx) override {
        std::string name = ctx->ID()->getText();
        uint64_t size = 0;
        std::vector<Value*> initValues;

        if (ctx->INT()) {
            size = std::stoi(ctx->INT()->getText());
        } else if (ctx->expressionList()) {
            size = ctx->expressionList()->expression().size();
            for (auto expr : ctx->expressionList()->expression()) {
                std::any valAny = visit(expr);
                initValues.push_back(std::any_cast<Value*>(valAny));
            }
        }

        stmtGen->generateArrayDeclaration(name, size, initValues);
        return std::any();
    }

    std::any visitArrayAssignment(EduCodeParser::ArrayAssignmentContext *ctx) override {
        std::string name = ctx->ID()->getText();
        
        std::any idxAny = visit(ctx->expression(0));
        Value* indexVal = std::any_cast<Value*>(idxAny);
        
        std::any valAny = visit(ctx->expression(1));
        Value* val = std::any_cast<Value*>(valAny);

        stmtGen->generateArrayAssignment(name, indexVal, val);
        return std::any();
    }

    std::any visitForEachStatement(EduCodeParser::ForEachStatementContext *ctx) override {
        std::string iteratorName = ctx->ID(0)->getText();
        std::string arrayName = ctx->ID(1)->getText();
        
        BasicBlock* condBB = nullptr;
        BasicBlock* bodyBB = nullptr;
        BasicBlock* afterBB = nullptr;

        auto info = stmtGen->generateForEachStart(iteratorName, arrayName, condBB, bodyBB, afterBB);
        
        if (!info.idxVar) return std::any();

        stmtGen->generateForEachBody(info, arrayName, bodyBB, afterBB);
        
        visit(ctx->block());
        
        stmtGen->generateForEachEnd(info, condBB, afterBB);
        
        return std::any();
    }

    // ==================== EXPRESIONES ====================
    std::any visitParenExpr(EduCodeParser::ParenExprContext *ctx) override {
        return visit(ctx->expression());
    }

    std::any visitIdExpr(EduCodeParser::IdExprContext *ctx) override {
        std::string name = ctx->ID()->getText();
        Value* val = exprGen->generateIdLoad(name);
        return val ? std::any(val) : std::any();
    }

    std::any visitIntExpr(EduCodeParser::IntExprContext *ctx) override {
        return (Value*)exprGen->generateInt(ctx->INT()->getText());
    }

    std::any visitFloatExpr(EduCodeParser::FloatExprContext *ctx) override {
        return (Value*)exprGen->generateFloat(ctx->FLOAT()->getText());
    }

    std::any visitBoolExpr(EduCodeParser::BoolExprContext *ctx) override {
        return (Value*)exprGen->generateBool(ctx->BOOLEAN()->getText());
    }

    std::any visitStringExpr(EduCodeParser::StringExprContext *ctx) override {
        return (Value*)exprGen->generateString(ctx->STRING()->getText());
    }

    std::any visitAddSubExpr(EduCodeParser::AddSubExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        return (Value*)exprGen->generateBinaryOp(L, R, ctx->op->getType());
    }

    std::any visitMulDivModExpr(EduCodeParser::MulDivModExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        return (Value*)exprGen->generateBinaryOp(L, R, ctx->op->getType());
    }

    std::any visitComparisonExpr(EduCodeParser::ComparisonExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        return (Value*)exprGen->generateComparison(L, R, ctx->op->getType());
    }

    std::any visitAndExpr(EduCodeParser::AndExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        return (Value*)exprGen->generateAnd(L, R);
    }

    std::any visitOrExpr(EduCodeParser::OrExprContext *ctx) override {
        Value* L = std::any_cast<Value*>(visit(ctx->expression(0)));
        Value* R = std::any_cast<Value*>(visit(ctx->expression(1)));
        return (Value*)exprGen->generateOr(L, R);
    }

    std::any visitNotExpr(EduCodeParser::NotExprContext *ctx) override {
        Value* val = std::any_cast<Value*>(visit(ctx->expression()));
        return (Value*)exprGen->generateNot(val);
    }

    std::any visitArrayAccessExpr(EduCodeParser::ArrayAccessExprContext *ctx) override {
        std::string name = ctx->arrayAccess()->ID()->getText();
        std::any idxAny = visit(ctx->arrayAccess()->expression());
        Value* indexVal = std::any_cast<Value*>(idxAny);
        
        Value* val = exprGen->generateArrayAccess(name, indexVal);
        return val ? std::any(val) : std::any();
    }

    std::any visitLengthExpr(EduCodeParser::LengthExprContext *ctx) override {
        std::string name = ctx->ID()->getText();
        return (Value*)exprGen->generateLength(name);
    }

    std::any visitReadExpr(EduCodeParser::ReadExprContext* /*ctx*/) override {
        return (Value*)exprGen->generateReadExpr();
    }
};

#endif // DRIVER_H