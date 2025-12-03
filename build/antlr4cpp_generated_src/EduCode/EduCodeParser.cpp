
// Generated from /mnt/c/TC-202502/TC-202502-TF/src/EduCode.g4 by ANTLR 4.13.2


#include "EduCodeVisitor.h"

#include "EduCodeParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct EduCodeParserStaticData final {
  EduCodeParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  EduCodeParserStaticData(const EduCodeParserStaticData&) = delete;
  EduCodeParserStaticData(EduCodeParserStaticData&&) = delete;
  EduCodeParserStaticData& operator=(const EduCodeParserStaticData&) = delete;
  EduCodeParserStaticData& operator=(EduCodeParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag educodeParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<EduCodeParserStaticData> educodeParserStaticData = nullptr;

void educodeParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (educodeParserStaticData != nullptr) {
    return;
  }
#else
  assert(educodeParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<EduCodeParserStaticData>(
    std::vector<std::string>{
      "program", "statement", "block", "varDeclaration", "assignment", "varDef", 
      "assignExpr", "printStatement", "readStatement", "ifStatement", "switchStatement", 
      "caseClause", "whileStatement", "doWhileStatement", "forStatement", 
      "arrayDeclaration", "arrayAssignment", "arrayAccess", "forEachStatement", 
      "expressionList", "expression"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "'='", "'('", "')'", "':'", "'['", "']'", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'+'", "'-'", 
      "'*'", "'/'", "'%'", "", "", "", "", "", "';'", "','"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "PRINT", "READ", "IF", "ELSE", 
      "ELSEIF", "SWITCH", "CASE", "DEFAULT", "WHILE", "DO", "FOR", "FOREACH", 
      "IN", "ARRAY", "LENGTH", "INT_TYPE", "FLOAT_TYPE", "STRING_TYPE", 
      "BOOL_TYPE", "AND", "OR", "NOT", "LT", "GT", "LE", "GE", "EQ", "NE", 
      "ADD", "SUB", "MUL", "DIV", "MOD", "BOOLEAN", "ID", "INT", "FLOAT", 
      "STRING", "SEMI", "COMMA", "WS", "COMMENT", "MULTILINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,292,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,5,
  	0,44,8,0,10,0,12,0,47,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,67,8,1,1,2,1,2,5,2,71,8,2,10,2,12,2,74,
  	9,2,1,2,1,2,1,3,1,3,1,3,1,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,88,8,5,1,6,1,
  	6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,5,7,99,8,7,10,7,12,7,102,9,7,1,7,1,7,1,
  	7,1,8,1,8,1,8,1,8,1,8,5,8,112,8,8,10,8,12,8,115,9,8,1,8,1,8,1,8,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,131,8,9,10,9,12,9,134,9,9,1,
  	9,1,9,3,9,138,8,9,1,10,1,10,1,10,1,10,1,10,1,10,4,10,146,8,10,11,10,12,
  	10,147,1,10,1,10,1,10,5,10,153,8,10,10,10,12,10,156,9,10,3,10,158,8,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,5,11,166,8,11,10,11,12,11,169,9,11,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,14,
  	1,14,1,14,1,14,1,14,3,14,190,8,14,1,14,1,14,3,14,194,8,14,1,14,1,14,1,
  	14,3,14,199,8,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,3,15,215,8,15,1,15,1,15,3,15,219,8,15,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,
  	1,18,1,18,1,18,1,18,1,19,1,19,1,19,5,19,245,8,19,10,19,12,19,248,9,19,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,3,20,270,8,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,5,20,287,8,20,10,20,
  	12,20,290,9,20,1,20,0,1,40,21,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,0,4,1,0,24,27,1,0,39,41,1,0,37,38,1,0,31,36,317,0,45,
  	1,0,0,0,2,66,1,0,0,0,4,68,1,0,0,0,6,77,1,0,0,0,8,80,1,0,0,0,10,83,1,0,
  	0,0,12,89,1,0,0,0,14,93,1,0,0,0,16,106,1,0,0,0,18,119,1,0,0,0,20,139,
  	1,0,0,0,22,161,1,0,0,0,24,170,1,0,0,0,26,176,1,0,0,0,28,184,1,0,0,0,30,
  	218,1,0,0,0,32,220,1,0,0,0,34,228,1,0,0,0,36,233,1,0,0,0,38,241,1,0,0,
  	0,40,269,1,0,0,0,42,44,3,2,1,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,
  	0,0,45,46,1,0,0,0,46,48,1,0,0,0,47,45,1,0,0,0,48,49,5,0,0,1,49,1,1,0,
  	0,0,50,67,3,6,3,0,51,67,3,8,4,0,52,67,3,14,7,0,53,67,3,16,8,0,54,67,3,
  	18,9,0,55,67,3,24,12,0,56,67,3,28,14,0,57,67,3,26,13,0,58,67,3,20,10,
  	0,59,67,3,30,15,0,60,67,3,32,16,0,61,67,3,36,18,0,62,67,3,4,2,0,63,64,
  	3,40,20,0,64,65,5,47,0,0,65,67,1,0,0,0,66,50,1,0,0,0,66,51,1,0,0,0,66,
  	52,1,0,0,0,66,53,1,0,0,0,66,54,1,0,0,0,66,55,1,0,0,0,66,56,1,0,0,0,66,
  	57,1,0,0,0,66,58,1,0,0,0,66,59,1,0,0,0,66,60,1,0,0,0,66,61,1,0,0,0,66,
  	62,1,0,0,0,66,63,1,0,0,0,67,3,1,0,0,0,68,72,5,1,0,0,69,71,3,2,1,0,70,
  	69,1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,75,1,0,0,0,74,
  	72,1,0,0,0,75,76,5,2,0,0,76,5,1,0,0,0,77,78,3,10,5,0,78,79,5,47,0,0,79,
  	7,1,0,0,0,80,81,3,12,6,0,81,82,5,47,0,0,82,9,1,0,0,0,83,84,7,0,0,0,84,
  	87,5,43,0,0,85,86,5,3,0,0,86,88,3,40,20,0,87,85,1,0,0,0,87,88,1,0,0,0,
  	88,11,1,0,0,0,89,90,5,43,0,0,90,91,5,3,0,0,91,92,3,40,20,0,92,13,1,0,
  	0,0,93,94,5,9,0,0,94,95,5,4,0,0,95,100,3,40,20,0,96,97,5,48,0,0,97,99,
  	3,40,20,0,98,96,1,0,0,0,99,102,1,0,0,0,100,98,1,0,0,0,100,101,1,0,0,0,
  	101,103,1,0,0,0,102,100,1,0,0,0,103,104,5,5,0,0,104,105,5,47,0,0,105,
  	15,1,0,0,0,106,107,5,10,0,0,107,108,5,4,0,0,108,113,5,43,0,0,109,110,
  	5,48,0,0,110,112,5,43,0,0,111,109,1,0,0,0,112,115,1,0,0,0,113,111,1,0,
  	0,0,113,114,1,0,0,0,114,116,1,0,0,0,115,113,1,0,0,0,116,117,5,5,0,0,117,
  	118,5,47,0,0,118,17,1,0,0,0,119,120,5,11,0,0,120,121,5,4,0,0,121,122,
  	3,40,20,0,122,123,5,5,0,0,123,132,3,4,2,0,124,125,5,13,0,0,125,126,5,
  	4,0,0,126,127,3,40,20,0,127,128,5,5,0,0,128,129,3,4,2,0,129,131,1,0,0,
  	0,130,124,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,
  	137,1,0,0,0,134,132,1,0,0,0,135,136,5,12,0,0,136,138,3,4,2,0,137,135,
  	1,0,0,0,137,138,1,0,0,0,138,19,1,0,0,0,139,140,5,14,0,0,140,141,5,4,0,
  	0,141,142,3,40,20,0,142,143,5,5,0,0,143,145,5,1,0,0,144,146,3,22,11,0,
  	145,144,1,0,0,0,146,147,1,0,0,0,147,145,1,0,0,0,147,148,1,0,0,0,148,157,
  	1,0,0,0,149,150,5,16,0,0,150,154,5,6,0,0,151,153,3,2,1,0,152,151,1,0,
  	0,0,153,156,1,0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,158,1,0,0,0,156,
  	154,1,0,0,0,157,149,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,0,159,160,5,
  	2,0,0,160,21,1,0,0,0,161,162,5,15,0,0,162,163,3,40,20,0,163,167,5,6,0,
  	0,164,166,3,2,1,0,165,164,1,0,0,0,166,169,1,0,0,0,167,165,1,0,0,0,167,
  	168,1,0,0,0,168,23,1,0,0,0,169,167,1,0,0,0,170,171,5,17,0,0,171,172,5,
  	4,0,0,172,173,3,40,20,0,173,174,5,5,0,0,174,175,3,4,2,0,175,25,1,0,0,
  	0,176,177,5,18,0,0,177,178,3,4,2,0,178,179,5,17,0,0,179,180,5,4,0,0,180,
  	181,3,40,20,0,181,182,5,5,0,0,182,183,5,47,0,0,183,27,1,0,0,0,184,185,
  	5,19,0,0,185,189,5,4,0,0,186,190,3,10,5,0,187,190,3,12,6,0,188,190,3,
  	40,20,0,189,186,1,0,0,0,189,187,1,0,0,0,189,188,1,0,0,0,189,190,1,0,0,
  	0,190,191,1,0,0,0,191,193,5,47,0,0,192,194,3,40,20,0,193,192,1,0,0,0,
  	193,194,1,0,0,0,194,195,1,0,0,0,195,198,5,47,0,0,196,199,3,12,6,0,197,
  	199,3,40,20,0,198,196,1,0,0,0,198,197,1,0,0,0,198,199,1,0,0,0,199,200,
  	1,0,0,0,200,201,5,5,0,0,201,202,3,4,2,0,202,29,1,0,0,0,203,204,5,22,0,
  	0,204,205,5,43,0,0,205,206,5,7,0,0,206,207,5,44,0,0,207,208,5,8,0,0,208,
  	219,5,47,0,0,209,210,5,22,0,0,210,211,5,43,0,0,211,212,5,3,0,0,212,214,
  	5,7,0,0,213,215,3,38,19,0,214,213,1,0,0,0,214,215,1,0,0,0,215,216,1,0,
  	0,0,216,217,5,8,0,0,217,219,5,47,0,0,218,203,1,0,0,0,218,209,1,0,0,0,
  	219,31,1,0,0,0,220,221,5,43,0,0,221,222,5,7,0,0,222,223,3,40,20,0,223,
  	224,5,8,0,0,224,225,5,3,0,0,225,226,3,40,20,0,226,227,5,47,0,0,227,33,
  	1,0,0,0,228,229,5,43,0,0,229,230,5,7,0,0,230,231,3,40,20,0,231,232,5,
  	8,0,0,232,35,1,0,0,0,233,234,5,20,0,0,234,235,5,4,0,0,235,236,5,43,0,
  	0,236,237,5,21,0,0,237,238,5,43,0,0,238,239,5,5,0,0,239,240,3,4,2,0,240,
  	37,1,0,0,0,241,246,3,40,20,0,242,243,5,48,0,0,243,245,3,40,20,0,244,242,
  	1,0,0,0,245,248,1,0,0,0,246,244,1,0,0,0,246,247,1,0,0,0,247,39,1,0,0,
  	0,248,246,1,0,0,0,249,250,6,20,-1,0,250,251,5,4,0,0,251,252,3,40,20,0,
  	252,253,5,5,0,0,253,270,1,0,0,0,254,270,3,34,17,0,255,270,5,43,0,0,256,
  	270,5,44,0,0,257,270,5,45,0,0,258,270,5,46,0,0,259,270,5,42,0,0,260,261,
  	5,30,0,0,261,270,3,40,20,3,262,263,5,10,0,0,263,264,5,4,0,0,264,270,5,
  	5,0,0,265,266,5,23,0,0,266,267,5,4,0,0,267,268,5,43,0,0,268,270,5,5,0,
  	0,269,249,1,0,0,0,269,254,1,0,0,0,269,255,1,0,0,0,269,256,1,0,0,0,269,
  	257,1,0,0,0,269,258,1,0,0,0,269,259,1,0,0,0,269,260,1,0,0,0,269,262,1,
  	0,0,0,269,265,1,0,0,0,270,288,1,0,0,0,271,272,10,8,0,0,272,273,7,1,0,
  	0,273,287,3,40,20,9,274,275,10,7,0,0,275,276,7,2,0,0,276,287,3,40,20,
  	8,277,278,10,6,0,0,278,279,7,3,0,0,279,287,3,40,20,7,280,281,10,5,0,0,
  	281,282,5,28,0,0,282,287,3,40,20,6,283,284,10,4,0,0,284,285,5,29,0,0,
  	285,287,3,40,20,5,286,271,1,0,0,0,286,274,1,0,0,0,286,277,1,0,0,0,286,
  	280,1,0,0,0,286,283,1,0,0,0,287,290,1,0,0,0,288,286,1,0,0,0,288,289,1,
  	0,0,0,289,41,1,0,0,0,290,288,1,0,0,0,21,45,66,72,87,100,113,132,137,147,
  	154,157,167,189,193,198,214,218,246,269,286,288
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  educodeParserStaticData = std::move(staticData);
}

}

EduCodeParser::EduCodeParser(TokenStream *input) : EduCodeParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

EduCodeParser::EduCodeParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  EduCodeParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *educodeParserStaticData->atn, educodeParserStaticData->decisionToDFA, educodeParserStaticData->sharedContextCache, options);
}

EduCodeParser::~EduCodeParser() {
  delete _interpreter;
}

const atn::ATN& EduCodeParser::getATN() const {
  return *educodeParserStaticData->atn;
}

std::string EduCodeParser::getGrammarFileName() const {
  return "EduCode.g4";
}

const std::vector<std::string>& EduCodeParser::getRuleNames() const {
  return educodeParserStaticData->ruleNames;
}

const dfa::Vocabulary& EduCodeParser::getVocabulary() const {
  return educodeParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView EduCodeParser::getSerializedATN() const {
  return educodeParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

EduCodeParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ProgramContext::EOF() {
  return getToken(EduCodeParser::EOF, 0);
}

std::vector<EduCodeParser::StatementContext *> EduCodeParser::ProgramContext::statement() {
  return getRuleContexts<EduCodeParser::StatementContext>();
}

EduCodeParser::StatementContext* EduCodeParser::ProgramContext::statement(size_t i) {
  return getRuleContext<EduCodeParser::StatementContext>(i);
}


size_t EduCodeParser::ProgramContext::getRuleIndex() const {
  return EduCodeParser::RuleProgram;
}


std::any EduCodeParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ProgramContext* EduCodeParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, EduCodeParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 136340781813266) != 0)) {
      setState(42);
      statement();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(48);
    match(EduCodeParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

EduCodeParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EduCodeParser::VarDeclarationContext* EduCodeParser::StatementContext::varDeclaration() {
  return getRuleContext<EduCodeParser::VarDeclarationContext>(0);
}

EduCodeParser::AssignmentContext* EduCodeParser::StatementContext::assignment() {
  return getRuleContext<EduCodeParser::AssignmentContext>(0);
}

EduCodeParser::PrintStatementContext* EduCodeParser::StatementContext::printStatement() {
  return getRuleContext<EduCodeParser::PrintStatementContext>(0);
}

EduCodeParser::ReadStatementContext* EduCodeParser::StatementContext::readStatement() {
  return getRuleContext<EduCodeParser::ReadStatementContext>(0);
}

EduCodeParser::IfStatementContext* EduCodeParser::StatementContext::ifStatement() {
  return getRuleContext<EduCodeParser::IfStatementContext>(0);
}

EduCodeParser::WhileStatementContext* EduCodeParser::StatementContext::whileStatement() {
  return getRuleContext<EduCodeParser::WhileStatementContext>(0);
}

EduCodeParser::ForStatementContext* EduCodeParser::StatementContext::forStatement() {
  return getRuleContext<EduCodeParser::ForStatementContext>(0);
}

EduCodeParser::DoWhileStatementContext* EduCodeParser::StatementContext::doWhileStatement() {
  return getRuleContext<EduCodeParser::DoWhileStatementContext>(0);
}

EduCodeParser::SwitchStatementContext* EduCodeParser::StatementContext::switchStatement() {
  return getRuleContext<EduCodeParser::SwitchStatementContext>(0);
}

EduCodeParser::ArrayDeclarationContext* EduCodeParser::StatementContext::arrayDeclaration() {
  return getRuleContext<EduCodeParser::ArrayDeclarationContext>(0);
}

EduCodeParser::ArrayAssignmentContext* EduCodeParser::StatementContext::arrayAssignment() {
  return getRuleContext<EduCodeParser::ArrayAssignmentContext>(0);
}

EduCodeParser::ForEachStatementContext* EduCodeParser::StatementContext::forEachStatement() {
  return getRuleContext<EduCodeParser::ForEachStatementContext>(0);
}

EduCodeParser::BlockContext* EduCodeParser::StatementContext::block() {
  return getRuleContext<EduCodeParser::BlockContext>(0);
}

EduCodeParser::ExpressionContext* EduCodeParser::StatementContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

tree::TerminalNode* EduCodeParser::StatementContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}


size_t EduCodeParser::StatementContext::getRuleIndex() const {
  return EduCodeParser::RuleStatement;
}


std::any EduCodeParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::StatementContext* EduCodeParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, EduCodeParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(66);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(50);
      varDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(51);
      assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(52);
      printStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(53);
      readStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(54);
      ifStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(55);
      whileStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(56);
      forStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(57);
      doWhileStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(58);
      switchStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(59);
      arrayDeclaration();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(60);
      arrayAssignment();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(61);
      forEachStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(62);
      block();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(63);
      expression(0);
      setState(64);
      match(EduCodeParser::SEMI);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

EduCodeParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EduCodeParser::StatementContext *> EduCodeParser::BlockContext::statement() {
  return getRuleContexts<EduCodeParser::StatementContext>();
}

EduCodeParser::StatementContext* EduCodeParser::BlockContext::statement(size_t i) {
  return getRuleContext<EduCodeParser::StatementContext>(i);
}


size_t EduCodeParser::BlockContext::getRuleIndex() const {
  return EduCodeParser::RuleBlock;
}


std::any EduCodeParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::BlockContext* EduCodeParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 4, EduCodeParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(EduCodeParser::T__0);
    setState(72);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 136340781813266) != 0)) {
      setState(69);
      statement();
      setState(74);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(75);
    match(EduCodeParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclarationContext ------------------------------------------------------------------

EduCodeParser::VarDeclarationContext::VarDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EduCodeParser::VarDefContext* EduCodeParser::VarDeclarationContext::varDef() {
  return getRuleContext<EduCodeParser::VarDefContext>(0);
}

tree::TerminalNode* EduCodeParser::VarDeclarationContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}


size_t EduCodeParser::VarDeclarationContext::getRuleIndex() const {
  return EduCodeParser::RuleVarDeclaration;
}


std::any EduCodeParser::VarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::VarDeclarationContext* EduCodeParser::varDeclaration() {
  VarDeclarationContext *_localctx = _tracker.createInstance<VarDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 6, EduCodeParser::RuleVarDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    varDef();
    setState(78);
    match(EduCodeParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

EduCodeParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

EduCodeParser::AssignExprContext* EduCodeParser::AssignmentContext::assignExpr() {
  return getRuleContext<EduCodeParser::AssignExprContext>(0);
}

tree::TerminalNode* EduCodeParser::AssignmentContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}


size_t EduCodeParser::AssignmentContext::getRuleIndex() const {
  return EduCodeParser::RuleAssignment;
}


std::any EduCodeParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::AssignmentContext* EduCodeParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 8, EduCodeParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    assignExpr();
    setState(81);
    match(EduCodeParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

EduCodeParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::VarDefContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

tree::TerminalNode* EduCodeParser::VarDefContext::INT_TYPE() {
  return getToken(EduCodeParser::INT_TYPE, 0);
}

tree::TerminalNode* EduCodeParser::VarDefContext::FLOAT_TYPE() {
  return getToken(EduCodeParser::FLOAT_TYPE, 0);
}

tree::TerminalNode* EduCodeParser::VarDefContext::STRING_TYPE() {
  return getToken(EduCodeParser::STRING_TYPE, 0);
}

tree::TerminalNode* EduCodeParser::VarDefContext::BOOL_TYPE() {
  return getToken(EduCodeParser::BOOL_TYPE, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::VarDefContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}


size_t EduCodeParser::VarDefContext::getRuleIndex() const {
  return EduCodeParser::RuleVarDef;
}


std::any EduCodeParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::VarDefContext* EduCodeParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 10, EduCodeParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 251658240) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(84);
    match(EduCodeParser::ID);
    setState(87);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EduCodeParser::T__2) {
      setState(85);
      match(EduCodeParser::T__2);
      setState(86);
      expression(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignExprContext ------------------------------------------------------------------

EduCodeParser::AssignExprContext::AssignExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::AssignExprContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::AssignExprContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}


size_t EduCodeParser::AssignExprContext::getRuleIndex() const {
  return EduCodeParser::RuleAssignExpr;
}


std::any EduCodeParser::AssignExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitAssignExpr(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::AssignExprContext* EduCodeParser::assignExpr() {
  AssignExprContext *_localctx = _tracker.createInstance<AssignExprContext>(_ctx, getState());
  enterRule(_localctx, 12, EduCodeParser::RuleAssignExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    match(EduCodeParser::ID);
    setState(90);
    match(EduCodeParser::T__2);
    setState(91);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintStatementContext ------------------------------------------------------------------

EduCodeParser::PrintStatementContext::PrintStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::PrintStatementContext::PRINT() {
  return getToken(EduCodeParser::PRINT, 0);
}

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::PrintStatementContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::PrintStatementContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::PrintStatementContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}

std::vector<tree::TerminalNode *> EduCodeParser::PrintStatementContext::COMMA() {
  return getTokens(EduCodeParser::COMMA);
}

tree::TerminalNode* EduCodeParser::PrintStatementContext::COMMA(size_t i) {
  return getToken(EduCodeParser::COMMA, i);
}


size_t EduCodeParser::PrintStatementContext::getRuleIndex() const {
  return EduCodeParser::RulePrintStatement;
}


std::any EduCodeParser::PrintStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitPrintStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::PrintStatementContext* EduCodeParser::printStatement() {
  PrintStatementContext *_localctx = _tracker.createInstance<PrintStatementContext>(_ctx, getState());
  enterRule(_localctx, 14, EduCodeParser::RulePrintStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(93);
    match(EduCodeParser::PRINT);
    setState(94);
    match(EduCodeParser::T__3);
    setState(95);
    expression(0);
    setState(100);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == EduCodeParser::COMMA) {
      setState(96);
      match(EduCodeParser::COMMA);
      setState(97);
      expression(0);
      setState(102);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(103);
    match(EduCodeParser::T__4);
    setState(104);
    match(EduCodeParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReadStatementContext ------------------------------------------------------------------

EduCodeParser::ReadStatementContext::ReadStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ReadStatementContext::READ() {
  return getToken(EduCodeParser::READ, 0);
}

std::vector<tree::TerminalNode *> EduCodeParser::ReadStatementContext::ID() {
  return getTokens(EduCodeParser::ID);
}

tree::TerminalNode* EduCodeParser::ReadStatementContext::ID(size_t i) {
  return getToken(EduCodeParser::ID, i);
}

tree::TerminalNode* EduCodeParser::ReadStatementContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}

std::vector<tree::TerminalNode *> EduCodeParser::ReadStatementContext::COMMA() {
  return getTokens(EduCodeParser::COMMA);
}

tree::TerminalNode* EduCodeParser::ReadStatementContext::COMMA(size_t i) {
  return getToken(EduCodeParser::COMMA, i);
}


size_t EduCodeParser::ReadStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleReadStatement;
}


std::any EduCodeParser::ReadStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitReadStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ReadStatementContext* EduCodeParser::readStatement() {
  ReadStatementContext *_localctx = _tracker.createInstance<ReadStatementContext>(_ctx, getState());
  enterRule(_localctx, 16, EduCodeParser::RuleReadStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    match(EduCodeParser::READ);
    setState(107);
    match(EduCodeParser::T__3);
    setState(108);
    match(EduCodeParser::ID);
    setState(113);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == EduCodeParser::COMMA) {
      setState(109);
      match(EduCodeParser::COMMA);
      setState(110);
      match(EduCodeParser::ID);
      setState(115);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(116);
    match(EduCodeParser::T__4);
    setState(117);
    match(EduCodeParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

EduCodeParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::IfStatementContext::IF() {
  return getToken(EduCodeParser::IF, 0);
}

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::IfStatementContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::IfStatementContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

std::vector<EduCodeParser::BlockContext *> EduCodeParser::IfStatementContext::block() {
  return getRuleContexts<EduCodeParser::BlockContext>();
}

EduCodeParser::BlockContext* EduCodeParser::IfStatementContext::block(size_t i) {
  return getRuleContext<EduCodeParser::BlockContext>(i);
}

std::vector<tree::TerminalNode *> EduCodeParser::IfStatementContext::ELSEIF() {
  return getTokens(EduCodeParser::ELSEIF);
}

tree::TerminalNode* EduCodeParser::IfStatementContext::ELSEIF(size_t i) {
  return getToken(EduCodeParser::ELSEIF, i);
}

tree::TerminalNode* EduCodeParser::IfStatementContext::ELSE() {
  return getToken(EduCodeParser::ELSE, 0);
}


size_t EduCodeParser::IfStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleIfStatement;
}


std::any EduCodeParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::IfStatementContext* EduCodeParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, EduCodeParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(EduCodeParser::IF);
    setState(120);
    match(EduCodeParser::T__3);
    setState(121);
    expression(0);
    setState(122);
    match(EduCodeParser::T__4);
    setState(123);
    block();
    setState(132);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == EduCodeParser::ELSEIF) {
      setState(124);
      match(EduCodeParser::ELSEIF);
      setState(125);
      match(EduCodeParser::T__3);
      setState(126);
      expression(0);
      setState(127);
      match(EduCodeParser::T__4);
      setState(128);
      block();
      setState(134);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EduCodeParser::ELSE) {
      setState(135);
      match(EduCodeParser::ELSE);
      setState(136);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SwitchStatementContext ------------------------------------------------------------------

EduCodeParser::SwitchStatementContext::SwitchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::SwitchStatementContext::SWITCH() {
  return getToken(EduCodeParser::SWITCH, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::SwitchStatementContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

std::vector<EduCodeParser::CaseClauseContext *> EduCodeParser::SwitchStatementContext::caseClause() {
  return getRuleContexts<EduCodeParser::CaseClauseContext>();
}

EduCodeParser::CaseClauseContext* EduCodeParser::SwitchStatementContext::caseClause(size_t i) {
  return getRuleContext<EduCodeParser::CaseClauseContext>(i);
}

tree::TerminalNode* EduCodeParser::SwitchStatementContext::DEFAULT() {
  return getToken(EduCodeParser::DEFAULT, 0);
}

std::vector<EduCodeParser::StatementContext *> EduCodeParser::SwitchStatementContext::statement() {
  return getRuleContexts<EduCodeParser::StatementContext>();
}

EduCodeParser::StatementContext* EduCodeParser::SwitchStatementContext::statement(size_t i) {
  return getRuleContext<EduCodeParser::StatementContext>(i);
}


size_t EduCodeParser::SwitchStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleSwitchStatement;
}


std::any EduCodeParser::SwitchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitSwitchStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::SwitchStatementContext* EduCodeParser::switchStatement() {
  SwitchStatementContext *_localctx = _tracker.createInstance<SwitchStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, EduCodeParser::RuleSwitchStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    match(EduCodeParser::SWITCH);
    setState(140);
    match(EduCodeParser::T__3);
    setState(141);
    expression(0);
    setState(142);
    match(EduCodeParser::T__4);
    setState(143);
    match(EduCodeParser::T__0);
    setState(145); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(144);
      caseClause();
      setState(147); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == EduCodeParser::CASE);
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == EduCodeParser::DEFAULT) {
      setState(149);
      match(EduCodeParser::DEFAULT);
      setState(150);
      match(EduCodeParser::T__5);
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 136340781813266) != 0)) {
        setState(151);
        statement();
        setState(156);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(159);
    match(EduCodeParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaseClauseContext ------------------------------------------------------------------

EduCodeParser::CaseClauseContext::CaseClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::CaseClauseContext::CASE() {
  return getToken(EduCodeParser::CASE, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::CaseClauseContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

std::vector<EduCodeParser::StatementContext *> EduCodeParser::CaseClauseContext::statement() {
  return getRuleContexts<EduCodeParser::StatementContext>();
}

EduCodeParser::StatementContext* EduCodeParser::CaseClauseContext::statement(size_t i) {
  return getRuleContext<EduCodeParser::StatementContext>(i);
}


size_t EduCodeParser::CaseClauseContext::getRuleIndex() const {
  return EduCodeParser::RuleCaseClause;
}


std::any EduCodeParser::CaseClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitCaseClause(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::CaseClauseContext* EduCodeParser::caseClause() {
  CaseClauseContext *_localctx = _tracker.createInstance<CaseClauseContext>(_ctx, getState());
  enterRule(_localctx, 22, EduCodeParser::RuleCaseClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(EduCodeParser::CASE);
    setState(162);
    expression(0);
    setState(163);
    match(EduCodeParser::T__5);
    setState(167);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 136340781813266) != 0)) {
      setState(164);
      statement();
      setState(169);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

EduCodeParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::WhileStatementContext::WHILE() {
  return getToken(EduCodeParser::WHILE, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::WhileStatementContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

EduCodeParser::BlockContext* EduCodeParser::WhileStatementContext::block() {
  return getRuleContext<EduCodeParser::BlockContext>(0);
}


size_t EduCodeParser::WhileStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleWhileStatement;
}


std::any EduCodeParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::WhileStatementContext* EduCodeParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 24, EduCodeParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(EduCodeParser::WHILE);
    setState(171);
    match(EduCodeParser::T__3);
    setState(172);
    expression(0);
    setState(173);
    match(EduCodeParser::T__4);
    setState(174);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DoWhileStatementContext ------------------------------------------------------------------

EduCodeParser::DoWhileStatementContext::DoWhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::DoWhileStatementContext::DO() {
  return getToken(EduCodeParser::DO, 0);
}

EduCodeParser::BlockContext* EduCodeParser::DoWhileStatementContext::block() {
  return getRuleContext<EduCodeParser::BlockContext>(0);
}

tree::TerminalNode* EduCodeParser::DoWhileStatementContext::WHILE() {
  return getToken(EduCodeParser::WHILE, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::DoWhileStatementContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

tree::TerminalNode* EduCodeParser::DoWhileStatementContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}


size_t EduCodeParser::DoWhileStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleDoWhileStatement;
}


std::any EduCodeParser::DoWhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitDoWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::DoWhileStatementContext* EduCodeParser::doWhileStatement() {
  DoWhileStatementContext *_localctx = _tracker.createInstance<DoWhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, EduCodeParser::RuleDoWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    match(EduCodeParser::DO);
    setState(177);
    block();
    setState(178);
    match(EduCodeParser::WHILE);
    setState(179);
    match(EduCodeParser::T__3);
    setState(180);
    expression(0);
    setState(181);
    match(EduCodeParser::T__4);
    setState(182);
    match(EduCodeParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStatementContext ------------------------------------------------------------------

EduCodeParser::ForStatementContext::ForStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ForStatementContext::FOR() {
  return getToken(EduCodeParser::FOR, 0);
}

std::vector<tree::TerminalNode *> EduCodeParser::ForStatementContext::SEMI() {
  return getTokens(EduCodeParser::SEMI);
}

tree::TerminalNode* EduCodeParser::ForStatementContext::SEMI(size_t i) {
  return getToken(EduCodeParser::SEMI, i);
}

EduCodeParser::BlockContext* EduCodeParser::ForStatementContext::block() {
  return getRuleContext<EduCodeParser::BlockContext>(0);
}

EduCodeParser::VarDefContext* EduCodeParser::ForStatementContext::varDef() {
  return getRuleContext<EduCodeParser::VarDefContext>(0);
}

std::vector<EduCodeParser::AssignExprContext *> EduCodeParser::ForStatementContext::assignExpr() {
  return getRuleContexts<EduCodeParser::AssignExprContext>();
}

EduCodeParser::AssignExprContext* EduCodeParser::ForStatementContext::assignExpr(size_t i) {
  return getRuleContext<EduCodeParser::AssignExprContext>(i);
}

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::ForStatementContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::ForStatementContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}


size_t EduCodeParser::ForStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleForStatement;
}


std::any EduCodeParser::ForStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitForStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ForStatementContext* EduCodeParser::forStatement() {
  ForStatementContext *_localctx = _tracker.createInstance<ForStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, EduCodeParser::RuleForStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(184);
    match(EduCodeParser::FOR);
    setState(185);
    match(EduCodeParser::T__3);
    setState(189);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(186);
      varDef();
      break;
    }

    case 2: {
      setState(187);
      assignExpr();
      break;
    }

    case 3: {
      setState(188);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(191);
    match(EduCodeParser::SEMI);
    setState(193);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 136340523975696) != 0)) {
      setState(192);
      expression(0);
    }
    setState(195);
    match(EduCodeParser::SEMI);
    setState(198);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(196);
      assignExpr();
      break;
    }

    case 2: {
      setState(197);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(200);
    match(EduCodeParser::T__4);
    setState(201);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDeclarationContext ------------------------------------------------------------------

EduCodeParser::ArrayDeclarationContext::ArrayDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ArrayDeclarationContext::ARRAY() {
  return getToken(EduCodeParser::ARRAY, 0);
}

tree::TerminalNode* EduCodeParser::ArrayDeclarationContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

tree::TerminalNode* EduCodeParser::ArrayDeclarationContext::INT() {
  return getToken(EduCodeParser::INT, 0);
}

tree::TerminalNode* EduCodeParser::ArrayDeclarationContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}

EduCodeParser::ExpressionListContext* EduCodeParser::ArrayDeclarationContext::expressionList() {
  return getRuleContext<EduCodeParser::ExpressionListContext>(0);
}


size_t EduCodeParser::ArrayDeclarationContext::getRuleIndex() const {
  return EduCodeParser::RuleArrayDeclaration;
}


std::any EduCodeParser::ArrayDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitArrayDeclaration(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ArrayDeclarationContext* EduCodeParser::arrayDeclaration() {
  ArrayDeclarationContext *_localctx = _tracker.createInstance<ArrayDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 30, EduCodeParser::RuleArrayDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(218);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(203);
      match(EduCodeParser::ARRAY);
      setState(204);
      match(EduCodeParser::ID);
      setState(205);
      match(EduCodeParser::T__6);
      setState(206);
      match(EduCodeParser::INT);
      setState(207);
      match(EduCodeParser::T__7);
      setState(208);
      match(EduCodeParser::SEMI);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(209);
      match(EduCodeParser::ARRAY);
      setState(210);
      match(EduCodeParser::ID);
      setState(211);
      match(EduCodeParser::T__2);
      setState(212);
      match(EduCodeParser::T__6);
      setState(214);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 136340523975696) != 0)) {
        setState(213);
        expressionList();
      }
      setState(216);
      match(EduCodeParser::T__7);
      setState(217);
      match(EduCodeParser::SEMI);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayAssignmentContext ------------------------------------------------------------------

EduCodeParser::ArrayAssignmentContext::ArrayAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ArrayAssignmentContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::ArrayAssignmentContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::ArrayAssignmentContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::ArrayAssignmentContext::SEMI() {
  return getToken(EduCodeParser::SEMI, 0);
}


size_t EduCodeParser::ArrayAssignmentContext::getRuleIndex() const {
  return EduCodeParser::RuleArrayAssignment;
}


std::any EduCodeParser::ArrayAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitArrayAssignment(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ArrayAssignmentContext* EduCodeParser::arrayAssignment() {
  ArrayAssignmentContext *_localctx = _tracker.createInstance<ArrayAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 32, EduCodeParser::RuleArrayAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
    match(EduCodeParser::ID);
    setState(221);
    match(EduCodeParser::T__6);
    setState(222);
    expression(0);
    setState(223);
    match(EduCodeParser::T__7);
    setState(224);
    match(EduCodeParser::T__2);
    setState(225);
    expression(0);
    setState(226);
    match(EduCodeParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayAccessContext ------------------------------------------------------------------

EduCodeParser::ArrayAccessContext::ArrayAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ArrayAccessContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::ArrayAccessContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}


size_t EduCodeParser::ArrayAccessContext::getRuleIndex() const {
  return EduCodeParser::RuleArrayAccess;
}


std::any EduCodeParser::ArrayAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitArrayAccess(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ArrayAccessContext* EduCodeParser::arrayAccess() {
  ArrayAccessContext *_localctx = _tracker.createInstance<ArrayAccessContext>(_ctx, getState());
  enterRule(_localctx, 34, EduCodeParser::RuleArrayAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(228);
    match(EduCodeParser::ID);
    setState(229);
    match(EduCodeParser::T__6);
    setState(230);
    expression(0);
    setState(231);
    match(EduCodeParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForEachStatementContext ------------------------------------------------------------------

EduCodeParser::ForEachStatementContext::ForEachStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* EduCodeParser::ForEachStatementContext::FOREACH() {
  return getToken(EduCodeParser::FOREACH, 0);
}

std::vector<tree::TerminalNode *> EduCodeParser::ForEachStatementContext::ID() {
  return getTokens(EduCodeParser::ID);
}

tree::TerminalNode* EduCodeParser::ForEachStatementContext::ID(size_t i) {
  return getToken(EduCodeParser::ID, i);
}

tree::TerminalNode* EduCodeParser::ForEachStatementContext::IN() {
  return getToken(EduCodeParser::IN, 0);
}

EduCodeParser::BlockContext* EduCodeParser::ForEachStatementContext::block() {
  return getRuleContext<EduCodeParser::BlockContext>(0);
}


size_t EduCodeParser::ForEachStatementContext::getRuleIndex() const {
  return EduCodeParser::RuleForEachStatement;
}


std::any EduCodeParser::ForEachStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitForEachStatement(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ForEachStatementContext* EduCodeParser::forEachStatement() {
  ForEachStatementContext *_localctx = _tracker.createInstance<ForEachStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, EduCodeParser::RuleForEachStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(233);
    match(EduCodeParser::FOREACH);
    setState(234);
    match(EduCodeParser::T__3);
    setState(235);
    match(EduCodeParser::ID);
    setState(236);
    match(EduCodeParser::IN);
    setState(237);
    match(EduCodeParser::ID);
    setState(238);
    match(EduCodeParser::T__4);
    setState(239);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

EduCodeParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::ExpressionListContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> EduCodeParser::ExpressionListContext::COMMA() {
  return getTokens(EduCodeParser::COMMA);
}

tree::TerminalNode* EduCodeParser::ExpressionListContext::COMMA(size_t i) {
  return getToken(EduCodeParser::COMMA, i);
}


size_t EduCodeParser::ExpressionListContext::getRuleIndex() const {
  return EduCodeParser::RuleExpressionList;
}


std::any EduCodeParser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ExpressionListContext* EduCodeParser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 38, EduCodeParser::RuleExpressionList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    expression(0);
    setState(246);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == EduCodeParser::COMMA) {
      setState(242);
      match(EduCodeParser::COMMA);
      setState(243);
      expression(0);
      setState(248);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

EduCodeParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t EduCodeParser::ExpressionContext::getRuleIndex() const {
  return EduCodeParser::RuleExpression;
}

void EduCodeParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::IntExprContext::INT() {
  return getToken(EduCodeParser::INT, 0);
}

EduCodeParser::IntExprContext::IntExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::IntExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitIntExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubExprContext ------------------------------------------------------------------

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::AddSubExprContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::AddSubExprContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::AddSubExprContext::ADD() {
  return getToken(EduCodeParser::ADD, 0);
}

tree::TerminalNode* EduCodeParser::AddSubExprContext::SUB() {
  return getToken(EduCodeParser::SUB, 0);
}

EduCodeParser::AddSubExprContext::AddSubExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReadExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::ReadExprContext::READ() {
  return getToken(EduCodeParser::READ, 0);
}

EduCodeParser::ReadExprContext::ReadExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::ReadExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitReadExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::OrExprContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::OrExprContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::OrExprContext::OR() {
  return getToken(EduCodeParser::OR, 0);
}

EduCodeParser::OrExprContext::OrExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivModExprContext ------------------------------------------------------------------

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::MulDivModExprContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::MulDivModExprContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::MulDivModExprContext::MUL() {
  return getToken(EduCodeParser::MUL, 0);
}

tree::TerminalNode* EduCodeParser::MulDivModExprContext::DIV() {
  return getToken(EduCodeParser::DIV, 0);
}

tree::TerminalNode* EduCodeParser::MulDivModExprContext::MOD() {
  return getToken(EduCodeParser::MOD, 0);
}

EduCodeParser::MulDivModExprContext::MulDivModExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::MulDivModExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitMulDivModExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonExprContext ------------------------------------------------------------------

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::ComparisonExprContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::ComparisonExprContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::ComparisonExprContext::LT() {
  return getToken(EduCodeParser::LT, 0);
}

tree::TerminalNode* EduCodeParser::ComparisonExprContext::GT() {
  return getToken(EduCodeParser::GT, 0);
}

tree::TerminalNode* EduCodeParser::ComparisonExprContext::LE() {
  return getToken(EduCodeParser::LE, 0);
}

tree::TerminalNode* EduCodeParser::ComparisonExprContext::GE() {
  return getToken(EduCodeParser::GE, 0);
}

tree::TerminalNode* EduCodeParser::ComparisonExprContext::EQ() {
  return getToken(EduCodeParser::EQ, 0);
}

tree::TerminalNode* EduCodeParser::ComparisonExprContext::NE() {
  return getToken(EduCodeParser::NE, 0);
}

EduCodeParser::ComparisonExprContext::ComparisonExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::ComparisonExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitComparisonExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

EduCodeParser::ExpressionContext* EduCodeParser::ParenExprContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

EduCodeParser::ParenExprContext::ParenExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::StringExprContext::STRING() {
  return getToken(EduCodeParser::STRING, 0);
}

EduCodeParser::StringExprContext::StringExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::StringExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitStringExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LengthExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::LengthExprContext::LENGTH() {
  return getToken(EduCodeParser::LENGTH, 0);
}

tree::TerminalNode* EduCodeParser::LengthExprContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

EduCodeParser::LengthExprContext::LengthExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::LengthExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitLengthExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::FloatExprContext::FLOAT() {
  return getToken(EduCodeParser::FLOAT, 0);
}

EduCodeParser::FloatExprContext::FloatExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::FloatExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitFloatExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayAccessExprContext ------------------------------------------------------------------

EduCodeParser::ArrayAccessContext* EduCodeParser::ArrayAccessExprContext::arrayAccess() {
  return getRuleContext<EduCodeParser::ArrayAccessContext>(0);
}

EduCodeParser::ArrayAccessExprContext::ArrayAccessExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::ArrayAccessExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitArrayAccessExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::NotExprContext::NOT() {
  return getToken(EduCodeParser::NOT, 0);
}

EduCodeParser::ExpressionContext* EduCodeParser::NotExprContext::expression() {
  return getRuleContext<EduCodeParser::ExpressionContext>(0);
}

EduCodeParser::NotExprContext::NotExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::NotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitNotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BoolExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::BoolExprContext::BOOLEAN() {
  return getToken(EduCodeParser::BOOLEAN, 0);
}

EduCodeParser::BoolExprContext::BoolExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::BoolExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitBoolExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdExprContext ------------------------------------------------------------------

tree::TerminalNode* EduCodeParser::IdExprContext::ID() {
  return getToken(EduCodeParser::ID, 0);
}

EduCodeParser::IdExprContext::IdExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::IdExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitIdExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<EduCodeParser::ExpressionContext *> EduCodeParser::AndExprContext::expression() {
  return getRuleContexts<EduCodeParser::ExpressionContext>();
}

EduCodeParser::ExpressionContext* EduCodeParser::AndExprContext::expression(size_t i) {
  return getRuleContext<EduCodeParser::ExpressionContext>(i);
}

tree::TerminalNode* EduCodeParser::AndExprContext::AND() {
  return getToken(EduCodeParser::AND, 0);
}

EduCodeParser::AndExprContext::AndExprContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any EduCodeParser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<EduCodeVisitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

EduCodeParser::ExpressionContext* EduCodeParser::expression() {
   return expression(0);
}

EduCodeParser::ExpressionContext* EduCodeParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  EduCodeParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  EduCodeParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 40;
  enterRecursionRule(_localctx, 40, EduCodeParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(269);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(250);
      match(EduCodeParser::T__3);
      setState(251);
      expression(0);
      setState(252);
      match(EduCodeParser::T__4);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArrayAccessExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(254);
      arrayAccess();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<IdExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(255);
      match(EduCodeParser::ID);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<IntExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(256);
      match(EduCodeParser::INT);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<FloatExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(257);
      match(EduCodeParser::FLOAT);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<StringExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(258);
      match(EduCodeParser::STRING);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<BoolExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(259);
      match(EduCodeParser::BOOLEAN);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<NotExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(260);
      match(EduCodeParser::NOT);
      setState(261);
      expression(3);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ReadExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(262);
      match(EduCodeParser::READ);
      setState(263);
      match(EduCodeParser::T__3);
      setState(264);
      match(EduCodeParser::T__4);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<LengthExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(265);
      match(EduCodeParser::LENGTH);
      setState(266);
      match(EduCodeParser::T__3);
      setState(267);
      match(EduCodeParser::ID);
      setState(268);
      match(EduCodeParser::T__4);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(288);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(286);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivModExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(271);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(272);
          antlrcpp::downCast<MulDivModExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 3848290697216) != 0))) {
            antlrcpp::downCast<MulDivModExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(273);
          expression(9);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(274);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(275);
          antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == EduCodeParser::ADD

          || _la == EduCodeParser::SUB)) {
            antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(276);
          expression(8);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ComparisonExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(277);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(278);
          antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 135291469824) != 0))) {
            antlrcpp::downCast<ComparisonExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(279);
          expression(7);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(280);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(281);
          match(EduCodeParser::AND);
          setState(282);
          expression(6);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(283);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(284);
          match(EduCodeParser::OR);
          setState(285);
          expression(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(290);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool EduCodeParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 20: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool EduCodeParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);
    case 4: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void EduCodeParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  educodeParserInitialize();
#else
  ::antlr4::internal::call_once(educodeParserOnceFlag, educodeParserInitialize);
#endif
}
