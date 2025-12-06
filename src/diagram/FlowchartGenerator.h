#ifndef FLOWCHART_GENERATOR_H
#define FLOWCHART_GENERATOR_H

#include "FlowchartNodes.h"
#include "DotExporter.h"
#include "EduCodeParser.h"
#include "EduCodeBaseVisitor.h"

#include <stack>
#include <memory>

class FlowchartGenerator : public EduCodeBaseVisitor {
private:
    FlowchartGraph graph;
    std::stack<int> contextStack;  // Para manejar contextos anidados
    int currentNode;
    int startNode;
    int endNode;

public:
    FlowchartGenerator() : currentNode(-1), startNode(-1), endNode(-1) {}

    // Generar diagrama desde el AST
    void generate(EduCodeParser::ProgramContext* ctx) {
        graph.clear();

        // Nodo INICIO
        startNode = graph.getNextId();
        auto start = std::make_shared<FlowchartNode>(startNode, NodeType::START, "INICIO");
        graph.addNode(start);
        currentNode = startNode;

        // Procesar programa
        visitProgram(ctx);

        // Nodo FIN
        endNode = graph.getNextId();
        auto end = std::make_shared<FlowchartNode>(endNode, NodeType::END, "FIN");
        graph.addNode(end);

        // Conectar último nodo con FIN
        if (currentNode != -1) {
            auto lastNode = graph.getNode(currentNode);
            if (lastNode) {
                lastNode->addNext(endNode);
            }
        }
    }

    // Exportar a archivo DOT
    bool exportDot(const std::string& filename) {
        return DotExporter::exportToFile(graph, filename);
    }

    // Exportar a HTML con visualización
    bool exportHtml(const std::string& filename) {
        return HtmlExporter::exportToHtml(graph, filename);
    }

    // Obtener el grafo generado
    const FlowchartGraph& getGraph() const {
        return graph;
    }

    // ==================== VISITORS ====================

    std::any visitProgram(EduCodeParser::ProgramContext *ctx) override {
        visitChildren(ctx);
        return std::any();
    }

    std::any visitVarDeclaration(EduCodeParser::VarDeclarationContext *ctx) override {
        std::string typeStr = ctx->varDef()->children[0]->getText();
        std::string name = ctx->varDef()->ID()->getText();
        std::string label = typeStr + " " + name;

        if (ctx->varDef()->expression()) {
            label += " = " + ctx->varDef()->expression()->getText();
        }

        int nodeId = graph.getNextId();
        auto node = std::make_shared<FlowchartNode>(nodeId, NodeType::PROCESS, label);
        graph.addNode(node);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(nodeId);
        }
        currentNode = nodeId;

        return std::any();
    }

    std::any visitAssignment(EduCodeParser::AssignmentContext *ctx) override {
        std::string name = ctx->assignExpr()->ID()->getText();
        std::string expr = ctx->assignExpr()->expression()->getText();
        std::string label = name + " = " + expr;

        int nodeId = graph.getNextId();
        auto node = std::make_shared<FlowchartNode>(nodeId, NodeType::PROCESS, label);
        graph.addNode(node);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(nodeId);
        }
        currentNode = nodeId;

        return std::any();
    }

    std::any visitPrintStatement(EduCodeParser::PrintStatementContext *ctx) override {
        std::string output = "Escribir ";
        bool first = true;

        for (auto expr : ctx->expression()) {
            if (!first) output += ", ";
            output += expr->getText();
            first = false;
        }

        int nodeId = graph.getNextId();
        auto node = std::make_shared<FlowchartNode>(nodeId, NodeType::OUTPUT, output);
        graph.addNode(node);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(nodeId);
        }
        currentNode = nodeId;

        return std::any();
    }

    std::any visitReadStatement(EduCodeParser::ReadStatementContext *ctx) override {
        std::string input = "Leer ";
        bool first = true;

        for (auto id : ctx->ID()) {
            if (!first) input += ", ";
            input += id->getText();
            first = false;
        }

        int nodeId = graph.getNextId();
        auto node = std::make_shared<FlowchartNode>(nodeId, NodeType::INPUT, input);
        graph.addNode(node);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(nodeId);
        }
        currentNode = nodeId;

        return std::any();
    }

    std::any visitIfStatement(EduCodeParser::IfStatementContext *ctx) override {
        // Nodo de decisión
        std::string condition = ctx->expression(0)->getText();
        int decisionId = graph.getNextId();
        auto decision = std::make_shared<DecisionNode>(decisionId, condition);
        graph.addNode(decision);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(decisionId);
        }

        // Guardar nodo actual
        int beforeIf = decisionId;

        // Rama THEN
        currentNode = beforeIf;
        contextStack.push(currentNode);
        visit(ctx->block(0));
        int afterThen = currentNode;
        contextStack.pop();

        // Rama ELSE (si existe)
        int afterElse = -1;
        if (ctx->ELSE()) {
            currentNode = beforeIf;
            contextStack.push(currentNode);
            visit(ctx->block(1));
            afterElse = currentNode;
            contextStack.pop();
        }

        // Nodo de convergencia
        int mergeId = graph.getNextId();
        auto merge = std::make_shared<FlowchartNode>(mergeId, NodeType::CONNECTOR, "");
        graph.addNode(merge);

        // Conectar ramas
        decision->addBranch(graph.getNode(afterThen) ? 
                           (graph.getNode(afterThen)->getNextNodes().empty() ? afterThen : 
                            graph.getNode(afterThen)->getNextNodes()[0]) : mergeId, 
                           "Verdadero");

        if (afterElse != -1) {
            decision->addBranch(graph.getNode(afterElse) ? 
                               (graph.getNode(afterElse)->getNextNodes().empty() ? afterElse : 
                                graph.getNode(afterElse)->getNextNodes()[0]) : mergeId, 
                               "Falso");
        } else {
            decision->addBranch(mergeId, "Falso");
        }

        // Conectar con merge
        if (afterThen != -1 && graph.getNode(afterThen)) {
            graph.getNode(afterThen)->addNext(mergeId);
        }
        if (afterElse != -1 && graph.getNode(afterElse)) {
            graph.getNode(afterElse)->addNext(mergeId);
        }

        currentNode = mergeId;
        return std::any();
    }

    std::any visitWhileStatement(EduCodeParser::WhileStatementContext *ctx) override {
        // Nodo de bucle
        std::string condition = ctx->expression()->getText();
        int loopId = graph.getNextId();
        auto loop = std::make_shared<LoopNode>(loopId, "Mientras " + condition, "while");
        graph.addNode(loop);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(loopId);
        }

        // Cuerpo del bucle
        int beforeBody = loopId;
        currentNode = beforeBody;
        contextStack.push(currentNode);
        visit(ctx->block());
        int afterBody = currentNode;
        contextStack.pop();

        // Conectar cuerpo de vuelta al bucle
        if (afterBody != -1 && graph.getNode(afterBody)) {
            graph.getNode(afterBody)->addNext(loopId);
        }

        // Nodo de salida
        int exitId = graph.getNextId();
        auto exit = std::make_shared<FlowchartNode>(exitId, NodeType::CONNECTOR, "");
        graph.addNode(exit);

        loop->addNext(afterBody != -1 ? afterBody : exitId);
        loop->addNext(exitId);

        currentNode = exitId;
        return std::any();
    }

    std::any visitForStatement(EduCodeParser::ForStatementContext *ctx) override {
        // Inicialización
        if (ctx->varDef()) {
            visit(ctx->varDef());
        } else if (ctx->assignExpr().size() > 0) {
            visitAssignExpr(ctx->assignExpr(0));
        }

        // Nodo de bucle
        std::string condition = "Para (condición)";
        int loopId = graph.getNextId();
        auto loop = std::make_shared<LoopNode>(loopId, condition, "for");
        graph.addNode(loop);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(loopId);
        }

        // Cuerpo
        currentNode = loopId;
        visit(ctx->block());
        
        // Salida
        int exitId = graph.getNextId();
        auto exit = std::make_shared<FlowchartNode>(exitId, NodeType::CONNECTOR, "");
        graph.addNode(exit);

        loop->addNext(exitId);
        currentNode = exitId;

        return std::any();
    }

    std::any visitForEachStatement(EduCodeParser::ForEachStatementContext *ctx) override {
        std::string iterator = ctx->ID(0)->getText();
        std::string array = ctx->ID(1)->getText();
        std::string label = "Para cada " + iterator + " en " + array;

        int loopId = graph.getNextId();
        auto loop = std::make_shared<LoopNode>(loopId, label, "foreach");
        graph.addNode(loop);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(loopId);
        }

        currentNode = loopId;
        visit(ctx->block());

        int exitId = graph.getNextId();
        auto exit = std::make_shared<FlowchartNode>(exitId, NodeType::CONNECTOR, "");
        graph.addNode(exit);

        loop->addNext(exitId);
        currentNode = exitId;

        return std::any();
    }

    std::any visitArrayDeclaration(EduCodeParser::ArrayDeclarationContext *ctx) override {
        std::string name = ctx->ID()->getText();
        std::string label = "array " + name;

        if (ctx->INT()) {
            label += "[" + ctx->INT()->getText() + "]";
        } else if (ctx->expressionList()) {
            label += " = [...]";
        }

        int nodeId = graph.getNextId();
        auto node = std::make_shared<FlowchartNode>(nodeId, NodeType::PROCESS, label);
        graph.addNode(node);

        if (currentNode != -1) {
            graph.getNode(currentNode)->addNext(nodeId);
        }
        currentNode = nodeId;

        return std::any();
    }

    std::any visitBlock(EduCodeParser::BlockContext *ctx) override {
        visitChildren(ctx);
        return std::any();
    }
};

#endif // FLOWCHART_GENERATOR_H