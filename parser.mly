/* Ocamlyacc parser for textPlusPlus */

%{
open Ast
%}

%token SEMI LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA PLUS MINUS TIMES DIVIDE ASSIGN
%token NOT EQ NEQ LT LEQ GT GEQ AND OR
%token RETURN IF ELSE FOR WHILE INT BOOL FLOAT STRING VOID DEFINE
%token <int> LITERAL
%token <bool> BLIT
%token <string> STRLITERAL
%token <string> ID FLIT
%token EOF

%start program
%type <Ast.program> program

%nonassoc NOELSE
%nonassoc ELSE
%right ASSIGN
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIVIDE
%right NOT

%%

program:
  declarations EOF { $1 }

declarations:
   /* nothing */ { ([], [])               }
 | declarations variable_declaration { (($2 :: fst $1), snd $1) }
 | declarations function_declaration { (fst $1, ($2 :: snd $1)) }

function_declaration:
   DEFINE typ ID LPAREN parameters RPAREN LBRACE vdecl_list codeblock RBRACE
     { { typ = $2;
	 fname = $3;
	 formals = List.rev $5;
	 locals = List.rev $8;
	 body = List.rev $9 } }

parameters:
    /* nothing */ { [] }
  | formal_list   { $1 }

formal_list:
    typ ID                   { [($1,$2)]     }
  | formal_list COMMA typ ID { ($3,$4) :: $1 }

typ:
    INT   { Int   }
  | STRING { String }
  | BOOL  { Bool  }
  | FLOAT { Float }
  | VOID  { Void  }

vdecl_list:
    /* nothing */    { [] }
  | vdecl_list variable_declaration { $2 :: $1 }

variable_declaration:
   typ ID SEMI { ($1, $2) }

codeblock:
    /* nothing */  { [] }
  | codeblock stmt { $2 :: $1 }

stmt:
    expression SEMI                                 { Expr $1            }
  | RETURN expr_opt SEMI                            { Return $2          }
  | LBRACE codeblock RBRACE                         { Block(List.rev $2) }
  | IF LPAREN expression RPAREN stmt %prec NOELSE   { If($3, $5, Block([])) }
  | IF LPAREN expression RPAREN stmt ELSE stmt      { If($3, $5, $7) }
  | FOR LPAREN expr_opt SEMI expression SEMI expr_opt RPAREN stmt
                                                    { For($3, $5, $7, $9) }
  | WHILE LPAREN expression RPAREN stmt             { While($3, $5) }

expr_opt:
    /* nothing */       { Noexpr }
  | expression          { $1 }

expression:
    LITERAL                             { Literal($1) }
  | STRLITERAL                          { StrLiteral($1) }
  | FLIT	                              { Fliteral($1) }
  | BLIT                                { BoolLit($1) }
  | ID                                  { Id($1) }
  | expression PLUS   expression        { Binop($1, Add,   $3)   }
  | expression MINUS  expression        { Binop($1, Sub,   $3)   }
  | expression TIMES  expression        { Binop($1, Mult,  $3)   }
  | expression DIVIDE expression        { Binop($1, Div,   $3)   }
  | expression EQ     expression        { Binop($1, Equal, $3)   }
  | expression NEQ    expression        { Binop($1, Neq,   $3)   }
  | expression LT     expression        { Binop($1, Less,  $3)   }
  | expression LEQ    expression        { Binop($1, Leq,   $3)   }
  | expression GT     expression        { Binop($1, Greater, $3) }
  | expression GEQ    expression        { Binop($1, Geq,   $3)   }
  | expression AND    expression        { Binop($1, And,   $3)   }
  | expression OR     expression        { Binop($1, Or,    $3)   }
  | MINUS expression %prec NOT          { Unop(Neg, $2)  }
  | NOT expression                      { Unop(Not, $2)  }
  | ID ASSIGN expression                { Assign($1, $3) }
  | ID LPAREN optional_arguments RPAREN { Call($1, $3)   }
  | LPAREN expression RPAREN            { $2 }

optional_arguments:
    /* nothing */  { [] }
  | arguments      { List.rev $1 }

arguments:
    expression                    { [$1] }
  | arguments COMMA expression    { $3 :: $1 }
