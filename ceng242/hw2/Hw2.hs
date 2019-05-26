module Hw2 where

data ASTResult = ASTError String | ASTJust (String, String, Int) deriving (Show, Read)
data ASTDatum = ASTSimpleDatum String | ASTLetDatum String deriving (Show, Read)
data AST = EmptyAST | ASTNode ASTDatum AST AST deriving (Show, Read)

isNumber :: String -> Bool
eagerEvaluation :: AST -> ASTResult
normalEvaluation :: AST -> ASTResult

-- DO NOT MODIFY OR DELETE THE LINES ABOVE -- 
-- IMPLEMENT isNumber, eagerEvaluation and normalEvaluation FUNCTIONS ACCORDING TO GIVEN SIGNATURES -- 

first  (x, _, _) = x
second (_, x, _) = x
third  (_, _, x) = x


isNumber' :: String -> Bool
isNumber' [] = True
isNumber' (x:xr) = (x >= '0' && x <= '9' && isNumber' (xr))

isNumber [] = False
isNumber (x:xr) =
	if x == '-' then isNumber' (xr)
	else isNumber' (x:xr)


eagerEvaluation EmptyAST = ASTError "Empty AST!"
eagerEvaluation a = eagerHelper (a)([])

findVariable v (x:xr)
 | fst (x) == v = snd (x)
 | otherwise = findVariable v xr


eagerHelper (EmptyAST) _ = ASTJust ("", "", 0)
eagerHelper (ASTNode (ASTSimpleDatum name) left right) variables
 | name == "plus" =  case left_result of
     (ASTError s) -> ASTError s
     (ASTJust (la, lb, lc)) -> case right_result of (ASTError s) -> ASTError s
						    (ASTJust (ra, rb, rc)) -> if lb == "str" && rb == "str"
				                                              then ASTError "plus operation is not defined between str and str!"
									      else
									      if lb == "num" && rb == "str"
									      then ASTError "plus operation is not defined between num and str!"
									      else
									      if lb == "str" && rb == "num"
									      then ASTError "plus operation is not defined between str and num!"
									      else ASTJust (show(read(la)+read(ra)), "num", lc+rc+1)
 | name == "times" = case left_result of
     (ASTError s) -> ASTError s
     (ASTJust (la, lb, lc)) -> case right_result of (ASTError s) -> ASTError s
						    (ASTJust (ra, rb, rc)) -> if lb == "str" && rb == "str"
				                                              then ASTError "times operation is not defined between str and str!"
									      else
									      if lb == "num" && rb == "str"
									      then ASTError "times operation is not defined between num and str!"
									      else
									      if lb == "str" && rb == "num"
									      then ASTError "times operation is not defined between str and num!"
									      else ASTJust (show(read(la)*read(ra)), "num", lc+rc+1)
 | name == "negate" = case left_result of
    (ASTError s) -> ASTError s
    (ASTJust (a, b, c)) -> if b == "str"
                           then ASTError "negate operation is not defined on str!"
			   else ASTJust (show(-read(a)), b, c+1)
 | name == "cat" = case left_result of
     (ASTError s) -> ASTError s
     (ASTJust (la, lb, lc)) -> case right_result of (ASTError s) -> ASTError s
						    (ASTJust (ra, rb, rc)) -> if lb == "num" && rb == "num"
				                                              then ASTError "cat operation is not defined between num and num!"
									      else
									      if lb == "num" && rb == "str"
									      then ASTError "cat operation is not defined between num and str!"
									      else
									      if lb == "str" && rb == "num"
									      then ASTError "cat operation is not defined between str and num!"
									      else ASTJust (la ++ ra, "str", lc+rc+1)
 | name == "len" = case left_result of (ASTError s) -> ASTError s
				       (ASTJust (a, b, c)) -> if b == "num"
						              then ASTError "len operation is not defined on num!"
				                              else ASTJust (show(length (a)), "num", c+1)
 | name == "num" = let (ASTNode (ASTSimpleDatum s) l r) = left
		   in if isNumber (s)
		   then ASTJust (s, name, 0)
		   else ASTError ("the value '" ++ s ++ "' is not a number!")
 | name == "str" = let (ASTNode (ASTSimpleDatum s) l r) = left
                   in ASTJust (s, name, 0)
 | otherwise = (findVariable name variables)
 where left_result  = eagerHelper left variables
       right_result = eagerHelper right variables

eagerHelper (ASTNode (ASTLetDatum name) left right) variables = 
	case left_result of (ASTError s) -> (ASTError s)
	                    (ASTJust (a, b, c)) -> let (ASTJust (ra, rb, rc)) = eagerHelper right ((name, ASTJust (a, b, 0)):variables)
			                           in ASTJust (ra, rb, c+rc)
	where left_result  = eagerHelper left variables




normalEvaluation EmptyAST = ASTError "Empty AST!"
normalEvaluation a = normalHelper (a)([])

normalHelper (EmptyAST) _ = ASTJust ("", "", 0)
normalHelper (ASTNode (ASTSimpleDatum name) left right) variables
 | name == "plus" =  case left_result of
     (ASTError s) -> ASTError s
     (ASTJust (la, lb, lc)) -> case right_result of (ASTError s) -> ASTError s
						    (ASTJust (ra, rb, rc)) -> if lb == "str" && rb == "str"
				                                              then ASTError "plus operation is not defined between str and str!"
									      else
									      if lb == "num" && rb == "str"
									      then ASTError "plus operation is not defined between num and str!"
									      else
									      if lb == "str" && rb == "num"
									      then ASTError "plus operation is not defined between str and num!"
									      else ASTJust (show(read(la)+read(ra)), "num", lc+rc+1)
 | name == "times" = case left_result of
     (ASTError s) -> ASTError s
     (ASTJust (la, lb, lc)) -> case right_result of (ASTError s) -> ASTError s
						    (ASTJust (ra, rb, rc)) -> if lb == "str" && rb == "str"
				                                              then ASTError "times operation is not defined between str and str!"
									      else
									      if lb == "num" && rb == "str"
									      then ASTError "times operation is not defined between num and str!"
									      else
									      if lb == "str" && rb == "num"
									      then ASTError "times operation is not defined between str and num!"
									      else ASTJust (show(read(la)*read(ra)), "num", lc+rc+1)
 | name == "negate" = case left_result of
    (ASTError s) -> ASTError s
    (ASTJust (a, b, c)) -> if b == "str"
                           then ASTError "negate operation is not defined on str!"
			   else ASTJust (show(-read(a)), b, c+1)
 | name == "cat" = case left_result of
     (ASTError s) -> ASTError s
     (ASTJust (la, lb, lc)) -> case right_result of (ASTError s) -> ASTError s
						    (ASTJust (ra, rb, rc)) -> if lb == "num" && rb == "num"
				                                              then ASTError "cat operation is not defined between num and num!"
									      else
									      if lb == "num" && rb == "str"
									      then ASTError "cat operation is not defined between num and str!"
									      else
									      if lb == "str" && rb == "num"
									      then ASTError "cat operation is not defined between str and num!"
									      else ASTJust (la ++ ra, "str", lc+rc+1)
 | name == "len" = case left_result of (ASTError s) -> ASTError s
				       (ASTJust (a, b, c)) -> if b == "num"
						              then ASTError "len operation is not defined on num!"
				                              else ASTJust (show(length (a)), "num", c+1)
 | name == "num" = let (ASTNode (ASTSimpleDatum s) l r) = left
		   in if isNumber (s)
		   then ASTJust (s, name, 0)
		   else ASTError ("the value '" ++ s ++ "' is not a number!")
 | name == "str" = let (ASTNode (ASTSimpleDatum s) l r) = left
                   in ASTJust (s, name, 0)
 | otherwise = normalHelper (findVariable name variables) variables
 where left_result  = normalHelper left variables
       right_result = normalHelper right variables

normalHelper (ASTNode (ASTLetDatum name) left right) variables = normalHelper right ((name, left):variables)
