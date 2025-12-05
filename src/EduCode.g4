grammar EduCode;

/* Reglas del parser */
program: (statement)* EOF;

statement:
  varDeclaration
  | assignment
  | printStatement
  | readStatement
  | ifStatement
  | whileStatement
  | forStatement
  | doWhileStatement
  | switchStatement
  | arrayDeclaration
  | arrayAssignment
  | forEachStatement
  | block
  | expression SEMI
  ;

block: '{' statement* '}';

/* Declaraciones y asignaciones */
varDeclaration: varDef SEMI;
assignment: assignExpr SEMI;

varDef: (INT_TYPE | FLOAT_TYPE | STRING_TYPE | BOOL_TYPE) ID ('=' expression)?;
assignExpr: ID '=' expression;

/* Entrada/Salida */
printStatement: 
  PRINT '(' expression (',' expression)* ')' SEMI;

readStatement: 
  READ '(' ID (',' ID)* ')' SEMI;

ifStatement:
  IF '(' expression ')' block (ELSEIF '(' expression ')' block)* (ELSE block)?;

switchStatement:
  SWITCH '(' expression ')' '{' caseClause+ (DEFAULT ':' statement*)? '}';

caseClause: 
  CASE expression ':' statement*;

/* Bucles */
whileStatement: 
  WHILE '(' expression ')' block;

doWhileStatement:
  DO block WHILE '(' expression ')' SEMI;

forStatement:
  FOR '(' (varDef | assignExpr | expression)? SEMI
        expression? SEMI
        (assignExpr | expression)? ')' block;

/* Arreglos */
arrayDeclaration:
  ARRAY ID '[' INT ']' SEMI
  | ARRAY ID '=' '[' expressionList? ']' SEMI;

arrayAssignment:
  ID '[' expression ']' '=' expression SEMI;

arrayAccess: ID '[' expression ']';

forEachStatement:
  FOREACH '(' ID IN ID ')' block;

expressionList: expression (',' expression)*;

/* Expresiones */
expression:
  '(' expression ')'                                  # parenExpr
  | arrayAccess                                       # arrayAccessExpr
  | ID                                                # idExpr
  | INT                                               # intExpr
  | FLOAT                                             # floatExpr
  | STRING                                            # stringExpr
  | BOOLEAN                                           # boolExpr
  | expression op=(MUL | DIV | MOD) expression        # mulDivModExpr
  | expression op=(ADD | SUB) expression              # addSubExpr
  | expression op=(LT | GT | LE | GE | EQ | NE) expression  # comparisonExpr
  | expression AND expression                         # andExpr
  | expression OR expression                          # orExpr
  | NOT expression                                    # notExpr
  | READ '(' ')'                                      # readExpr
  | LENGTH '(' ID ')'                                 # lengthExpr
  ;

/* Tokens */
PRINT: 'print' | 'escribir' | 'mostrar';
READ: 'read' | 'leer' | 'input';
IF: 'if' | 'si';
ELSE: 'else' | 'sino';
ELSEIF: 'elseif' | 'sinosi';
SWITCH: 'switch' | 'segun';
CASE: 'case' | 'caso';
DEFAULT: 'default' | 'defecto';
WHILE: 'while' | 'mientras';
DO: 'do' | 'hacer';
FOR: 'for' | 'para';
FOREACH: 'foreach' | 'paracada';
IN: 'in' | 'en';
ARRAY: 'array' | 'vector' | 'arreglo';
LENGTH: 'length' | 'longitud' | 'tamano';

INT_TYPE: 'int' | 'entero';
FLOAT_TYPE: 'float' | 'real' | 'decimal';
STRING_TYPE: 'string' | 'cadena';
BOOL_TYPE: 'bool' | 'booleano';

AND: '&&' | 'and' | 'y';
OR: '||' | 'or' | 'o';
NOT: '!' | 'not' | 'no';

LT: '<';
GT: '>';
LE: '<=';
GE: '>=';
EQ: '==';
NE: '!=';

ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';
MOD: '%';

BOOLEAN: 'true' | 'false' | 'verdadero' | 'falso';

ID: [a-zA-Z_][a-zA-Z_0-9]*;
INT: [0-9]+;
FLOAT: [0-9]+ '.' [0-9]*;
STRING: '"' ( '\\' . | ~["\\\r\n] )* '"';

SEMI: ';';
COMMA: ',';

WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
MULTILINE_COMMENT: '/*' .*? '*/' -> skip;