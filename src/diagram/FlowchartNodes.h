#ifndef FLOWCHART_NODES_H
#define FLOWCHART_NODES_H

#include <string>
#include <vector>
#include <memory>

// Tipos de nodos en el diagrama de flujo
enum class NodeType {
    START,          // Inicio (óvalo)
    END,            // Fin (óvalo)
    PROCESS,        // Proceso (rectángulo)
    DECISION,       // Decisión (rombo)
    INPUT,          // Entrada (paralelogramo)
    OUTPUT,         // Salida (paralelogramo)
    LOOP,           // Bucle (hexágono)
    CONNECTOR       // Conector (círculo pequeño)
};

// Clase base para todos los nodos
class FlowchartNode {
protected:
    int id;
    NodeType type;
    std::string label;
    std::vector<int> nextNodes;  // IDs de nodos siguientes

public:
    FlowchartNode(int id, NodeType type, const std::string& label)
        : id(id), type(type), label(label) {}

    virtual ~FlowchartNode() = default;

    int getId() const { return id; }
    NodeType getType() const { return type; }
    std::string getLabel() const { return label; }
    const std::vector<int>& getNextNodes() const { return nextNodes; }

    void addNext(int nodeId) {
        nextNodes.push_back(nodeId);
    }

    // Obtener forma DOT según el tipo
    std::string getDotShape() const {
        switch (type) {
            case NodeType::START:
            case NodeType::END:
                return "oval";
            case NodeType::PROCESS:
                return "box";
            case NodeType::DECISION:
                return "diamond";
            case NodeType::INPUT:
            case NodeType::OUTPUT:
                return "parallelogram";
            case NodeType::LOOP:
                return "hexagon";
            case NodeType::CONNECTOR:
                return "circle";
            default:
                return "box";
        }
    }

    // Obtener color según el tipo
    std::string getDotColor() const {
        switch (type) {
            case NodeType::START:
                return "#90EE90"; // Verde claro
            case NodeType::END:
                return "#FFB6C1"; // Rosa claro
            case NodeType::PROCESS:
                return "#87CEEB"; // Azul cielo
            case NodeType::DECISION:
                return "#FFD700"; // Dorado
            case NodeType::INPUT:
                return "#DDA0DD"; // Púrpura claro
            case NodeType::OUTPUT:
                return "#FFA07A"; // Salmón claro
            case NodeType::LOOP:
                return "#98FB98"; // Verde pálido
            case NodeType::CONNECTOR:
                return "#D3D3D3"; // Gris claro
            default:
                return "#FFFFFF";
        }
    }
};

// Nodo específico para decisiones (tiene labels en aristas)
class DecisionNode : public FlowchartNode {
private:
    std::vector<std::string> edgeLabels;  // Labels para cada rama

public:
    DecisionNode(int id, const std::string& condition)
        : FlowchartNode(id, NodeType::DECISION, condition) {}

    void addBranch(int nodeId, const std::string& label) {
        addNext(nodeId);
        edgeLabels.push_back(label);
    }

    std::string getEdgeLabel(size_t index) const {
        if (index < edgeLabels.size()) {
            return edgeLabels[index];
        }
        return "";
    }

    const std::vector<std::string>& getEdgeLabels() const {
        return edgeLabels;
    }
};

// Nodo específico para bucles
class LoopNode : public FlowchartNode {
private:
    std::string loopType;  // "while", "for", "do-while", "foreach"

public:
    LoopNode(int id, const std::string& condition, const std::string& type)
        : FlowchartNode(id, NodeType::LOOP, condition), loopType(type) {}

    std::string getLoopType() const { return loopType; }
};

// Contenedor de nodos del diagrama
class FlowchartGraph {
private:
    std::vector<std::shared_ptr<FlowchartNode>> nodes;
    int nextId;

public:
    FlowchartGraph() : nextId(0) {}

    int getNextId() { return nextId++; }

    void addNode(std::shared_ptr<FlowchartNode> node) {
        nodes.push_back(node);
    }

    const std::vector<std::shared_ptr<FlowchartNode>>& getNodes() const {
        return nodes;
    }

    std::shared_ptr<FlowchartNode> getNode(int id) const {
        for (const auto& node : nodes) {
            if (node->getId() == id) {
                return node;
            }
        }
        return nullptr;
    }

    void clear() {
        nodes.clear();
        nextId = 0;
    }

    size_t size() const {
        return nodes.size();
    }
};

#endif // FLOWCHART_NODES_H