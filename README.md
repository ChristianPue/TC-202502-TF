# EduCode 🧩

EduCode es un compilador educativo inspirado en Pseint que utiliza **ANTLR4** para el análisis sintáctico y **LLVM** para la generación y ejecución de código intermedio.  
El proyecto permite compilar programas escritos en `.educ`, optimizarlos, ejecutarlos directamente con JIT y generar diagramas de flujo tipo PSeInt/Graphviz.

---

## 📂 Estructura de archivos y carpetas
```
├── examples/
│   ├── ej-total.educ
│   ├── ej-total.ll
│   ├── ej-imprimir.educ
│   └── ej-imprimir.ll
├── src/
│   ├── codegen/
│   │   ├── CodeGenerator.h
│   │   ├── ExpressionGen.h
│   │   ├── StatementGen.h
│   │   ├── SymbolTable.h
│   │   └── TypeSystem.h
│   ├── optimizer/
│   │   ├── ConstantFolding.h
│   │   ├── DeadCodeElimination.h
│   │   ├── LoopOptimizer.h
│   │   └── Optimizer.h
│   ├── runtime/
│   │   ├── JITEngine.h
│   │   └── RuntimeSupport.h
│   └── diagram/
│       ├── DotExporter.h
│       ├── FlowchartGenerator.h
│       └── FlowchartNodes.h
├── CMakeLists.txt
├── Driver.h
├── EduCode.g4
└── Main.cpp
```

- **codegen/** → Generación de LLVM IR a partir del AST.  
- **optimizer/** → Conjunto de optimizaciones (constant folding, dead code elimination, loop optimization).  
- **runtime/** → Motor JIT y soporte de ejecución en memoria.  
- **diagram/** → Generación de diagramas de flujo en formato DOT (Graphviz).  
- **examples/** → Programas de ejemplo en EduCode y sus correspondientes IR optimizados.  

---

## ⚙️ Cómo ejecutar el proyecto EduCode

Antes de correr cualquier ejemplo, asegúrate de compilar correctamente el proyecto.  
Si ya ejecutaste y creaste el directorio `build/` pero salió error, elimina la carpeta:
```bash
rm -rf build/
```

Luego, para ejecutar todo desde cero:
```bash
cmake -S src -B build
cmake --build build
```
(Ignora los warnings)

---

## 🎯 Formas de uso de EduCode

### 1. Compilación básica a LLVM IR
```bash
./build/EduCode ./examples/programa.educ
```

### Flujo:
- Parseo con ANTLR → AST.
- Generación de IR con Driver.
- Optimización por defecto (-O1).
- Exportación a archivo .ll.

### 2. Compilación con optimización específica
```bash
./build/EduCode ./examples/programa.educ -O0
./build/EduCode ./examples/programa.educ -O2
```

### Flujo:
Igual que el anterior, pero el optimizador (Optimizer) aplica el nivel indicado:
- -O0: sin optimizaciones.
- -O1: optimizaciones básicas (default).
- -O2: optimizaciones agresivas.
Resultado: archivo .ll optimizado según el nivel.

### 3. Ejecución directa con JIT
```bash
./build/EduCode ./examples/programa.educ -run
./build/EduCode ./examples/programa.educ -O2 -run
```

### Flujo:
- Parseo → IR → optimización.
- En vez de solo exportar .ll, se invoca executeModule(driver.getModule()) desde runtime/JITEngine.h.
- El programa .educ se ejecuta directamente en memoria, con soporte de input/output.

### 4. Generación de diagrama de flujo (Graphviz DOT)
```bash
./build/EduCode ./examples/programa.educ -diagram
```

### Flujo:
- Parseo → AST.
- Se invoca FlowchartGenerator (en diagram/FlowchartGenerator.h).
- Exporta un archivo .dot con el grafo del flujo del programa.
- Visualización con Graphviz: 
```bash
dot -Tpng ./examples/programa.dot -o ./examples/diagrama.png
```

## 📌 Conclusión
EduCode integra frontend (ANTLR), middle-end (LLVM IR + optimizaciones), backend (JIT) y visualización (diagramas de flujo) en un solo proyecto. Es una herramienta didáctica que permite comprender el ciclo completo de un compilador moderno y experimentar con optimización, ejecución inmediata y representación gráfica de programas.