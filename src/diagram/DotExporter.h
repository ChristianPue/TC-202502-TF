#ifndef DOT_EXPORTER_H
#define DOT_EXPORTER_H

#include "FlowchartNodes.h"
#include <fstream>
#include <sstream>
#include <iostream>

class DotExporter {
public:
    // Exportar grafo a archivo DOT
    static bool exportToFile(const FlowchartGraph& graph, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
            return false;
        }

        file << generateDot(graph);
        file.close();

        std::cout << "✓ Diagrama de flujo generado en: " << filename << std::endl;
        return true;
    }

    // Generar código DOT
    static std::string generateDot(const FlowchartGraph& graph) {
        std::stringstream ss;

        // Header
        ss << "digraph Flowchart {\n";
        ss << "    // Configuración global\n";
        ss << "    rankdir=TB;\n";  // Top to Bottom
        ss << "    node [style=filled, fontname=\"Arial\", fontsize=12];\n";
        ss << "    edge [fontname=\"Arial\", fontsize=10];\n";
        ss << "    bgcolor=\"#F5F5F5\";\n\n";

        // Nodos
        ss << "    // Nodos del diagrama\n";
        for (const auto& node : graph.getNodes()) {
            ss << generateNodeDot(node);
        }

        ss << "\n    // Conexiones\n";
        for (const auto& node : graph.getNodes()) {
            ss << generateEdgesDot(node);
        }

        ss << "}\n";

        return ss.str();
    }

private:
    // Generar DOT para un nodo
    static std::string generateNodeDot(const std::shared_ptr<FlowchartNode>& node) {
        std::stringstream ss;

        ss << "    node" << node->getId() << " [";
        ss << "label=\"" << escapeLabel(node->getLabel()) << "\", ";
        ss << "shape=" << node->getDotShape() << ", ";
        ss << "fillcolor=\"" << node->getDotColor() << "\"";
        
        // Estilos especiales para ciertos tipos
        if (node->getType() == NodeType::START || node->getType() == NodeType::END) {
            ss << ", penwidth=2";
        }
        
        ss << "];\n";

        return ss.str();
    }

    // Generar DOT para las aristas de un nodo
    static std::string generateEdgesDot(const std::shared_ptr<FlowchartNode>& node) {
        std::stringstream ss;

        // Nodo de decisión tiene labels en las aristas
        if (auto decisionNode = std::dynamic_pointer_cast<DecisionNode>(node)) {
            const auto& nextNodes = decisionNode->getNextNodes();
            const auto& labels = decisionNode->getEdgeLabels();

            for (size_t i = 0; i < nextNodes.size(); i++) {
                ss << "    node" << node->getId() << " -> node" << nextNodes[i];
                
                if (i < labels.size() && !labels[i].empty()) {
                    ss << " [label=\"" << escapeLabel(labels[i]) << "\"";
                    
                    // Colores diferentes para Verdadero/Falso
                    if (labels[i] == "Verdadero" || labels[i] == "Sí" || labels[i] == "True") {
                        ss << ", color=\"#2E8B57\", fontcolor=\"#2E8B57\"";
                    } else if (labels[i] == "Falso" || labels[i] == "No" || labels[i] == "False") {
                        ss << ", color=\"#DC143C\", fontcolor=\"#DC143C\"";
                    }
                    
                    ss << "]";
                }
                
                ss << ";\n";
            }
        } else {
            // Nodo normal
            for (int nextId : node->getNextNodes()) {
                ss << "    node" << node->getId() << " -> node" << nextId << ";\n";
            }
        }

        return ss.str();
    }

    // Escapar caracteres especiales en labels
    static std::string escapeLabel(const std::string& label) {
        std::string escaped = label;
        
        // Reemplazar caracteres especiales
        size_t pos = 0;
        while ((pos = escaped.find("\"", pos)) != std::string::npos) {
            escaped.replace(pos, 1, "\\\"");
            pos += 2;
        }
        
        // Limitar longitud de labels
        if (escaped.length() > 50) {
            escaped = escaped.substr(0, 47) + "...";
        }

        return escaped;
    }
};

// Función auxiliar para generar HTML con visualización embebida
class HtmlExporter {
public:
    static bool exportToHtml(const FlowchartGraph& graph, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo crear el archivo " << filename << std::endl;
            return false;
        }

        file << generateHtml(graph);
        file.close();

        std::cout << "✓ Visualización HTML generada en: " << filename << std::endl;
        std::cout << "  → Abre el archivo en tu navegador para ver el diagrama" << std::endl;
        return true;
    }

private:
    static std::string generateHtml(const FlowchartGraph& graph) {
        std::stringstream ss;

        ss << "<!DOCTYPE html>\n";
        ss << "<html>\n<head>\n";
        ss << "    <title>Diagrama de Flujo - EduCode</title>\n";
        ss << "    <script src=\"https://d3js.org/d3.v7.min.js\"></script>\n";
        ss << "    <script src=\"https://unpkg.com/@hpcc-js/wasm/dist/graphviz.umd.js\"></script>\n";
        ss << "    <script src=\"https://unpkg.com/d3-graphviz@5.0.2/build/d3-graphviz.js\"></script>\n";
        ss << "    <style>\n";
        ss << "        body { font-family: Arial, sans-serif; margin: 20px; background: #f0f0f0; }\n";
        ss << "        #graph { background: white; border: 2px solid #ddd; border-radius: 8px; padding: 20px; }\n";
        ss << "        h1 { color: #333; }\n";
        ss << "        .info { background: #e3f2fd; padding: 10px; border-radius: 5px; margin: 10px 0; }\n";
        ss << "    </style>\n";
        ss << "</head>\n<body>\n";
        ss << "    <h1>📊 Diagrama de Flujo - EduCode</h1>\n";
        ss << "    <div class=\"info\">Nodos: " << graph.size() << "</div>\n";
        ss << "    <div id=\"graph\"></div>\n";
        ss << "    <script>\n";
        ss << "        const dotString = `\n";
        ss << DotExporter::generateDot(graph);
        ss << "        `;\n";
        ss << "        d3.select(\"#graph\").graphviz().renderDot(dotString);\n";
        ss << "    </script>\n";
        ss << "</body>\n</html>\n";

        return ss.str();
    }
};

#endif // DOT_EXPORTER_H