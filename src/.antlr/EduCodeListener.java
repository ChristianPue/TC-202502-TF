// Generated from /mnt/c/TC-202502/TC-202502-TF/src/EduCode.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link EduCodeParser}.
 */
public interface EduCodeListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(EduCodeParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(EduCodeParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(EduCodeParser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(EduCodeParser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#block}.
	 * @param ctx the parse tree
	 */
	void enterBlock(EduCodeParser.BlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#block}.
	 * @param ctx the parse tree
	 */
	void exitBlock(EduCodeParser.BlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#varDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterVarDeclaration(EduCodeParser.VarDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#varDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitVarDeclaration(EduCodeParser.VarDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#assignment}.
	 * @param ctx the parse tree
	 */
	void enterAssignment(EduCodeParser.AssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#assignment}.
	 * @param ctx the parse tree
	 */
	void exitAssignment(EduCodeParser.AssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#varDef}.
	 * @param ctx the parse tree
	 */
	void enterVarDef(EduCodeParser.VarDefContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#varDef}.
	 * @param ctx the parse tree
	 */
	void exitVarDef(EduCodeParser.VarDefContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#assignExpr}.
	 * @param ctx the parse tree
	 */
	void enterAssignExpr(EduCodeParser.AssignExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#assignExpr}.
	 * @param ctx the parse tree
	 */
	void exitAssignExpr(EduCodeParser.AssignExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#printStatement}.
	 * @param ctx the parse tree
	 */
	void enterPrintStatement(EduCodeParser.PrintStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#printStatement}.
	 * @param ctx the parse tree
	 */
	void exitPrintStatement(EduCodeParser.PrintStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#readStatement}.
	 * @param ctx the parse tree
	 */
	void enterReadStatement(EduCodeParser.ReadStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#readStatement}.
	 * @param ctx the parse tree
	 */
	void exitReadStatement(EduCodeParser.ReadStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(EduCodeParser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(EduCodeParser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void enterSwitchStatement(EduCodeParser.SwitchStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#switchStatement}.
	 * @param ctx the parse tree
	 */
	void exitSwitchStatement(EduCodeParser.SwitchStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#caseClause}.
	 * @param ctx the parse tree
	 */
	void enterCaseClause(EduCodeParser.CaseClauseContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#caseClause}.
	 * @param ctx the parse tree
	 */
	void exitCaseClause(EduCodeParser.CaseClauseContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(EduCodeParser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(EduCodeParser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#doWhileStatement}.
	 * @param ctx the parse tree
	 */
	void enterDoWhileStatement(EduCodeParser.DoWhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#doWhileStatement}.
	 * @param ctx the parse tree
	 */
	void exitDoWhileStatement(EduCodeParser.DoWhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void enterForStatement(EduCodeParser.ForStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#forStatement}.
	 * @param ctx the parse tree
	 */
	void exitForStatement(EduCodeParser.ForStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#arrayDeclaration}.
	 * @param ctx the parse tree
	 */
	void enterArrayDeclaration(EduCodeParser.ArrayDeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#arrayDeclaration}.
	 * @param ctx the parse tree
	 */
	void exitArrayDeclaration(EduCodeParser.ArrayDeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#arrayAssignment}.
	 * @param ctx the parse tree
	 */
	void enterArrayAssignment(EduCodeParser.ArrayAssignmentContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#arrayAssignment}.
	 * @param ctx the parse tree
	 */
	void exitArrayAssignment(EduCodeParser.ArrayAssignmentContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#arrayAccess}.
	 * @param ctx the parse tree
	 */
	void enterArrayAccess(EduCodeParser.ArrayAccessContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#arrayAccess}.
	 * @param ctx the parse tree
	 */
	void exitArrayAccess(EduCodeParser.ArrayAccessContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#forEachStatement}.
	 * @param ctx the parse tree
	 */
	void enterForEachStatement(EduCodeParser.ForEachStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#forEachStatement}.
	 * @param ctx the parse tree
	 */
	void exitForEachStatement(EduCodeParser.ForEachStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link EduCodeParser#expressionList}.
	 * @param ctx the parse tree
	 */
	void enterExpressionList(EduCodeParser.ExpressionListContext ctx);
	/**
	 * Exit a parse tree produced by {@link EduCodeParser#expressionList}.
	 * @param ctx the parse tree
	 */
	void exitExpressionList(EduCodeParser.ExpressionListContext ctx);
	/**
	 * Enter a parse tree produced by the {@code intExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterIntExpr(EduCodeParser.IntExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code intExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitIntExpr(EduCodeParser.IntExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code addSubExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterAddSubExpr(EduCodeParser.AddSubExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code addSubExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitAddSubExpr(EduCodeParser.AddSubExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code readExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterReadExpr(EduCodeParser.ReadExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code readExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitReadExpr(EduCodeParser.ReadExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code orExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterOrExpr(EduCodeParser.OrExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code orExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitOrExpr(EduCodeParser.OrExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code mulDivModExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterMulDivModExpr(EduCodeParser.MulDivModExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code mulDivModExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitMulDivModExpr(EduCodeParser.MulDivModExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code comparisonExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterComparisonExpr(EduCodeParser.ComparisonExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code comparisonExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitComparisonExpr(EduCodeParser.ComparisonExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterParenExpr(EduCodeParser.ParenExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parenExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitParenExpr(EduCodeParser.ParenExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code stringExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterStringExpr(EduCodeParser.StringExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code stringExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitStringExpr(EduCodeParser.StringExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code lengthExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLengthExpr(EduCodeParser.LengthExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code lengthExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLengthExpr(EduCodeParser.LengthExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code floatExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterFloatExpr(EduCodeParser.FloatExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code floatExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitFloatExpr(EduCodeParser.FloatExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arrayAccessExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterArrayAccessExpr(EduCodeParser.ArrayAccessExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arrayAccessExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitArrayAccessExpr(EduCodeParser.ArrayAccessExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code notExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterNotExpr(EduCodeParser.NotExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code notExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitNotExpr(EduCodeParser.NotExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code boolExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterBoolExpr(EduCodeParser.BoolExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code boolExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitBoolExpr(EduCodeParser.BoolExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code idExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterIdExpr(EduCodeParser.IdExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code idExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitIdExpr(EduCodeParser.IdExprContext ctx);
	/**
	 * Enter a parse tree produced by the {@code andExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterAndExpr(EduCodeParser.AndExprContext ctx);
	/**
	 * Exit a parse tree produced by the {@code andExpr}
	 * labeled alternative in {@link EduCodeParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitAndExpr(EduCodeParser.AndExprContext ctx);
}