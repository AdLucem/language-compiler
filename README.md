# A Language

## Micro Syntax 

After we have defined our CFG, we need to define how Name and Constant are created using Regular Expression. This uses REGEX syntax.

1. Name => [a-z][a-z_0-9]*
2. Constant => [0-9]+ | "[unicode]*"
3. Op => + | - | * | div | & | '|' | ~ | ^ | ++ | == | %
4. ExpOp => and | or | not | && | '||'  // Operations to create condition statements 
5. Def => "def"
6. Type => {int, uint, char, string, bool, array <type> <size>, matrix <type> <size> <size>}
7. If, Else, Return, Import => "if", "else", "return", "import"

## Grammar (Macro-Syntax)

The base element is a 'line'.

[A] denotes a 'sequence of items in category A'.

S : Start Symbol

T : {//, Constant, Def, Declaration, Constant, Name, Op,,ExpOp, If, Then, Type }

### Production Rules
```
1. S -> [Line]
2. Line -> Expr        // expression
         | Cond        // condition 
         | Import Name
         | Def Name ( [Name] ) { [Expr] Return Atomic }     // function definition 
         | Name = Term          // assignment
         | //Constant
         | Import Name
3. Expr ->  Type [TypeArgs] Name     // type declaration 
          | Term                        // mathematical expression
          | Name ( [Atomic] )           // function call
          | If { Cond } [Line]                    // if-statement
          | If ( Cond ) [Line] Else { [Line] }           // if-then-else
          | Cond ? [Line] : [Line]      // Ternanry Operator
4. Cond -> Term ExpOp Term          
5. Term -> Atomic | Term Op Term | Op Term | ( Term )  // if a line is just an atomic, ignore it 
6. Atomic -> Constant | Name
7. TypeArgs -> Constant
```

## For Loop

'for' loops are syntactic sugar for this function:

```
def for (fn, loop_var, init, step_fn, condition) { 
	If (condition) {
		fn
    	loop_var << step_fn
    	for (fn, loop_var, init, step_fn, condition)
    }
```

This is syntactically converted to:

```
for(loop_var?; init, step_fn, condition):
{ fn }
```

## Where Loop

'where' loops are syntactic sugar for this function:

```
def where(fn, condition) {
	If (condition) {
		fn
		where(fn, condition)
	} 
}
```

This is syntactically converted to:

```
where(condition) {
fn }
```

<=, >= and != are also implemented as syntactic sugar.

## Arrays and Matrices

1. array[n] points to the element at the n'th place of that array
2. matrix[n] points to the array at the n'th row of that matrix.
3. The above are counted as type Name
4. The above, when used in an assignment statement, replace the value at that pointer with the value assigned
5. The above, when used in a Term, are replaced by the value at that pointer 

# Semantic Checks 
1. **Defination Check** =>  A Name can not be used in an expression unless declared or imported 
2. **Type Check** => Every symbol during assignement should be of same type. Similiarly every operation should be performed between the same type 
3. **Parameter check** => Number of parameters and the type of each parameter must remain the same during the declaration,defination and call to the function.
4. **Indentation check** => Similiar to python we are using tab and spa**ces for indentation hence we need a check** for correct indentation.
5. **List element check** => Check whether index exists in the list 
