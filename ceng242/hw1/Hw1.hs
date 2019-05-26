module Hw1 where

type Mapping = [(String, String, String)]
data AST = EmptyAST | ASTNode String AST AST deriving (Show, Read)

writeExpression :: (AST, Mapping) -> String
evaluateAST :: (AST, Mapping) -> (AST, String)
-- DO NOT MODIFY OR DELETE THE LINES ABOVE -- 
-- IMPLEMENT writeExpression and evaluateAST FUNCTION ACCORDING TO GIVEN SIGNATURES -- 

first  (a,_,_) = a
second (_,a,_) = a
third  (_,_,a) = a

writeVariables [] = ""
writeVariables (x:xs)
	|second (x) == "num" = first (x) ++ "=" ++ third (x) ++ (if xs /= [] then ";" else "") ++ writeVariables (xs)
	|second (x) == "str" = first (x) ++ "=\"" ++ third (x) ++ "\"" ++ (if xs /= [] then ";" else "")  ++ writeVariables (xs)
	|otherwise = ""

writeExpression (ASTNode operator left right, variables)
	|variables /= [] = "let " ++ writeVariables (variables) ++ " in " ++ extractStringAST (ASTNode operator left right)
	|otherwise = extractStringAST (ASTNode operator left right)
writeExpression (EmptyAST, _) = ""

-- define better later
extractStringAST (EmptyAST) = ""
extractStringAST (ASTNode operator left right)
	| operator == "plus"   = "(" ++ left_result ++ "+" ++ right_result ++ ")"
	| operator == "times"  = "(" ++ left_result ++ "*" ++ right_result ++ ")"
	| operator == "negate" = "(-" ++ left_result ++ ")"
	| operator == "cat"    = "(" ++ left_result ++ "++" ++ right_result ++ ")"
	| operator == "len"    = "(" ++ "length " ++ left_result ++ ")"
	| operator == "num"    = left_result
	| operator == "str"    = "\"" ++ left_result ++ "\""
	| otherwise            = operator
	where left_result  = extractStringAST (left)
	      right_result = extractStringAST (right)


varToAST [] x = EmptyAST 
varToAST (h:t) x
	| first (h) == x = (ASTNode (second(h)) (ASTNode (third(h)) EmptyAST EmptyAST) EmptyAST)
	| otherwise = (varToAST t x)

findInVars [] x = 0
findInVars (h:t) x
	| first (h) == x = 1
	| otherwise = (findInVars t x)

evaluateAST (EmptyAST, variables) = (EmptyAST, "")
evaluateAST (ASTNode operator left right, variables)
	| operator == "plus"    = (subtree, show((read l_s)+(read r_s)))
	| operator == "times"   = (subtree, show((read l_s)*(read r_s)))
	| operator == "negate"  = (subtree, show(-(read l_s)))
	| operator == "cat"     = (subtree, l_s ++ r_s)
	| operator == "len"     = (subtree, show (length l_s))
	| operator == "num"     = (subtree, l_s)
	| operator == "str"     = (subtree, l_s)
	| (findInVars variables operator) == 1 = (let ASTNode op l r = varToAST variables operator in (ASTNode op l r, snd(evaluateAST (ASTNode op l r, variables))))
	| otherwise = (subtree, operator)
	where (left_child, l_s)  = evaluateAST (left, variables)
	      (right_child, r_s)  = evaluateAST (right, variables)
	      subtree = (ASTNode operator left_child right_child)

