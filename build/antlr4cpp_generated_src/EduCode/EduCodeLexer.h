
// Generated from /mnt/c/TC-202502/TC-202502-TF/src/EduCode.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  EduCodeLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, PRINT = 9, READ = 10, IF = 11, ELSE = 12, ELSEIF = 13, SWITCH = 14, 
    CASE = 15, DEFAULT = 16, WHILE = 17, DO = 18, FOR = 19, FOREACH = 20, 
    IN = 21, ARRAY = 22, LENGTH = 23, INT_TYPE = 24, FLOAT_TYPE = 25, STRING_TYPE = 26, 
    BOOL_TYPE = 27, AND = 28, OR = 29, NOT = 30, LT = 31, GT = 32, LE = 33, 
    GE = 34, EQ = 35, NE = 36, ADD = 37, SUB = 38, MUL = 39, DIV = 40, MOD = 41, 
    BOOLEAN = 42, ID = 43, INT = 44, FLOAT = 45, STRING = 46, SEMI = 47, 
    COMMA = 48, WS = 49, COMMENT = 50, MULTILINE_COMMENT = 51
  };

  explicit EduCodeLexer(antlr4::CharStream *input);

  ~EduCodeLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

