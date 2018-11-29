type token =
  | SEMI
  | LPAREN
  | RPAREN
  | LBRACE
  | RBRACE
  | LBRACKET
  | RBRACKET
  | COMMA
  | PLUS
  | MINUS
  | TIMES
  | DIVIDE
  | ASSIGN
  | NOT
  | EQ
  | NEQ
  | LT
  | LEQ
  | GT
  | GEQ
  | AND
  | OR
  | RETURN
  | IF
  | ELSE
  | FOR
  | WHILE
  | INT
  | BOOL
  | FLOAT
  | VOID
  | DEFINE
  | LITERAL of (int)
  | BLIT of (bool)
  | ID of (string)
  | FLIT of (string)
  | EOF

open Parsing;;
let _ = parse_error;;
# 4 "parser.mly"
open Ast
# 45 "parser.ml"
let yytransl_const = [|
  257 (* SEMI *);
  258 (* LPAREN *);
  259 (* RPAREN *);
  260 (* LBRACE *);
  261 (* RBRACE *);
  262 (* LBRACKET *);
  263 (* RBRACKET *);
  264 (* COMMA *);
  265 (* PLUS *);
  266 (* MINUS *);
  267 (* TIMES *);
  268 (* DIVIDE *);
  269 (* ASSIGN *);
  270 (* NOT *);
  271 (* EQ *);
  272 (* NEQ *);
  273 (* LT *);
  274 (* LEQ *);
  275 (* GT *);
  276 (* GEQ *);
  277 (* AND *);
  278 (* OR *);
  279 (* RETURN *);
  280 (* IF *);
  281 (* ELSE *);
  282 (* FOR *);
  283 (* WHILE *);
  284 (* INT *);
  285 (* BOOL *);
  286 (* FLOAT *);
  287 (* VOID *);
  288 (* DEFINE *);
    0 (* EOF *);
    0|]

let yytransl_block = [|
  289 (* LITERAL *);
  290 (* BLIT *);
  291 (* ID *);
  292 (* FLIT *);
    0|]

let yylhs = "\255\255\
\001\000\002\000\002\000\002\000\004\000\006\000\006\000\009\000\
\009\000\005\000\005\000\005\000\005\000\007\000\007\000\003\000\
\008\000\008\000\010\000\010\000\010\000\010\000\010\000\010\000\
\010\000\012\000\012\000\011\000\011\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\011\000\011\000\011\000\011\000\
\011\000\011\000\011\000\011\000\011\000\011\000\011\000\011\000\
\013\000\013\000\014\000\014\000\000\000"

let yylen = "\002\000\
\002\000\000\000\002\000\002\000\010\000\000\000\001\000\002\000\
\004\000\001\000\001\000\001\000\001\000\000\000\002\000\003\000\
\000\000\002\000\002\000\003\000\003\000\005\000\007\000\009\000\
\005\000\000\000\001\000\001\000\001\000\001\000\001\000\003\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\002\000\002\000\003\000\004\000\003\000\
\000\000\001\000\001\000\003\000\002\000"

let yydefred = "\000\000\
\002\000\000\000\053\000\000\000\010\000\011\000\012\000\013\000\
\000\000\001\000\003\000\004\000\000\000\000\000\000\000\000\000\
\016\000\000\000\000\000\000\000\000\000\008\000\000\000\000\000\
\014\000\000\000\000\000\009\000\015\000\000\000\000\000\017\000\
\005\000\000\000\000\000\000\000\000\000\000\000\000\000\028\000\
\030\000\000\000\029\000\018\000\000\000\000\000\000\000\044\000\
\045\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\019\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\048\000\021\000\020\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\034\000\035\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\047\000\000\000\
\000\000\000\000\025\000\000\000\000\000\000\000\023\000\000\000\
\000\000\024\000"

let yydgoto = "\002\000\
\003\000\004\000\011\000\012\000\013\000\020\000\027\000\030\000\
\021\000\044\000\045\000\051\000\077\000\078\000"

let yysindex = "\009\000\
\000\000\000\000\000\000\001\000\000\000\000\000\000\000\000\000\
\172\255\000\000\000\000\000\000\005\255\008\255\067\255\068\255\
\000\000\172\255\034\255\069\255\070\255\000\000\078\255\172\255\
\000\000\055\255\172\255\000\000\000\000\040\255\147\255\000\000\
\000\000\147\255\147\255\147\255\085\255\091\255\094\255\000\000\
\000\000\045\255\000\000\000\000\198\255\006\000\075\255\000\000\
\000\000\253\254\096\255\147\255\147\255\147\255\147\255\147\255\
\000\000\147\255\147\255\147\255\147\255\147\255\147\255\147\255\
\147\255\147\255\147\255\147\255\147\255\000\000\000\000\000\000\
\160\000\102\255\180\000\253\254\103\255\099\255\253\254\037\255\
\037\255\000\000\000\000\219\000\219\000\213\255\213\255\213\255\
\213\255\207\000\194\000\132\255\147\255\132\255\000\000\147\255\
\087\255\220\255\000\000\253\254\132\255\147\255\000\000\112\255\
\132\255\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\115\255\000\000\000\000\125\255\000\000\000\000\000\000\
\000\000\000\000\090\255\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\119\255\000\000\000\000\000\000\000\000\
\000\000\176\255\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\052\255\000\000\000\000\119\255\000\000\126\255\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\049\255\000\000\127\255\080\255\242\255\
\033\000\000\000\000\000\143\000\146\000\055\000\077\000\099\000\
\121\000\038\255\083\255\000\000\000\000\000\000\000\000\000\000\
\117\255\000\000\000\000\053\255\000\000\129\255\000\000\000\000\
\000\000\000\000"

let yygindex = "\000\000\
\000\000\000\000\106\000\000\000\002\000\000\000\000\000\103\000\
\000\000\068\000\225\255\205\255\000\000\000\000"

let yytablesize = 495
let yytable = "\046\000\
\010\000\074\000\048\000\049\000\050\000\058\000\059\000\060\000\
\061\000\001\000\014\000\062\000\063\000\064\000\065\000\066\000\
\067\000\068\000\069\000\019\000\073\000\050\000\075\000\076\000\
\079\000\026\000\080\000\081\000\082\000\083\000\084\000\085\000\
\086\000\087\000\088\000\089\000\090\000\091\000\042\000\015\000\
\042\000\031\000\016\000\032\000\033\000\042\000\055\000\060\000\
\061\000\034\000\104\000\051\000\027\000\035\000\027\000\052\000\
\051\000\056\000\042\000\042\000\052\000\098\000\036\000\037\000\
\100\000\038\000\039\000\017\000\022\000\018\000\050\000\023\000\
\040\000\041\000\042\000\043\000\031\000\024\000\032\000\071\000\
\046\000\025\000\046\000\043\000\034\000\043\000\052\000\046\000\
\035\000\028\000\043\000\017\000\053\000\017\000\017\000\054\000\
\072\000\036\000\037\000\017\000\038\000\039\000\093\000\017\000\
\043\000\095\000\096\000\040\000\041\000\042\000\043\000\101\000\
\017\000\017\000\105\000\017\000\017\000\006\000\022\000\026\000\
\022\000\022\000\017\000\017\000\017\000\017\000\022\000\007\000\
\049\000\050\000\022\000\026\000\029\000\031\000\047\000\032\000\
\000\000\000\000\000\000\022\000\022\000\034\000\022\000\022\000\
\000\000\035\000\000\000\000\000\031\000\022\000\022\000\022\000\
\022\000\000\000\036\000\037\000\034\000\038\000\039\000\097\000\
\035\000\099\000\000\000\000\000\040\000\041\000\042\000\043\000\
\103\000\000\000\000\000\000\000\106\000\000\000\000\000\000\000\
\031\000\000\000\031\000\040\000\041\000\042\000\043\000\031\000\
\031\000\031\000\031\000\031\000\000\000\000\000\031\000\031\000\
\031\000\031\000\031\000\031\000\031\000\031\000\057\000\005\000\
\006\000\007\000\008\000\000\000\000\000\000\000\058\000\059\000\
\060\000\061\000\000\000\000\000\062\000\063\000\064\000\065\000\
\066\000\067\000\068\000\069\000\102\000\058\000\059\000\060\000\
\061\000\000\000\000\000\000\000\058\000\059\000\060\000\061\000\
\000\000\000\000\062\000\063\000\064\000\065\000\066\000\067\000\
\068\000\069\000\032\000\000\000\032\000\000\000\000\000\000\000\
\000\000\032\000\032\000\032\000\000\000\000\000\000\000\000\000\
\032\000\032\000\032\000\032\000\032\000\032\000\032\000\032\000\
\070\000\000\000\000\000\000\000\000\000\000\000\058\000\059\000\
\060\000\061\000\000\000\000\000\062\000\063\000\064\000\065\000\
\066\000\067\000\068\000\069\000\005\000\006\000\007\000\008\000\
\009\000\033\000\000\000\033\000\000\000\000\000\000\000\000\000\
\033\000\033\000\033\000\000\000\000\000\000\000\000\000\033\000\
\033\000\033\000\033\000\033\000\033\000\033\000\033\000\038\000\
\000\000\038\000\000\000\000\000\000\000\000\000\038\000\000\000\
\000\000\000\000\000\000\000\000\000\000\038\000\038\000\038\000\
\038\000\038\000\038\000\038\000\038\000\039\000\000\000\039\000\
\000\000\000\000\000\000\000\000\039\000\000\000\000\000\000\000\
\000\000\000\000\000\000\039\000\039\000\039\000\039\000\039\000\
\039\000\039\000\039\000\040\000\000\000\040\000\000\000\000\000\
\000\000\000\000\040\000\000\000\000\000\000\000\000\000\000\000\
\000\000\040\000\040\000\040\000\040\000\040\000\040\000\040\000\
\040\000\041\000\000\000\041\000\000\000\000\000\000\000\000\000\
\041\000\000\000\000\000\000\000\000\000\000\000\000\000\041\000\
\041\000\041\000\041\000\041\000\041\000\041\000\041\000\036\000\
\000\000\036\000\037\000\000\000\037\000\000\000\036\000\000\000\
\000\000\037\000\000\000\000\000\000\000\036\000\036\000\000\000\
\037\000\037\000\092\000\036\000\036\000\000\000\037\000\037\000\
\058\000\059\000\060\000\061\000\000\000\000\000\062\000\063\000\
\064\000\065\000\066\000\067\000\068\000\069\000\094\000\000\000\
\000\000\000\000\000\000\000\000\058\000\059\000\060\000\061\000\
\000\000\000\000\062\000\063\000\064\000\065\000\066\000\067\000\
\068\000\069\000\058\000\059\000\060\000\061\000\000\000\000\000\
\062\000\063\000\064\000\065\000\066\000\067\000\068\000\058\000\
\059\000\060\000\061\000\000\000\000\000\062\000\063\000\064\000\
\065\000\066\000\067\000\058\000\059\000\060\000\061\000\000\000\
\000\000\000\000\000\000\064\000\065\000\066\000\067\000"

let yycheck = "\031\000\
\000\000\053\000\034\000\035\000\036\000\009\001\010\001\011\001\
\012\001\001\000\009\000\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001\018\000\052\000\053\000\054\000\055\000\
\056\000\024\000\058\000\059\000\060\000\061\000\062\000\063\000\
\064\000\065\000\066\000\067\000\068\000\069\000\001\001\035\001\
\003\001\002\001\035\001\004\001\005\001\008\001\002\001\011\001\
\012\001\010\001\102\000\003\001\001\001\014\001\003\001\003\001\
\008\001\013\001\021\001\022\001\008\001\093\000\023\001\024\001\
\096\000\026\001\027\001\001\001\035\001\002\001\102\000\003\001\
\033\001\034\001\035\001\036\001\002\001\008\001\004\001\005\001\
\001\001\004\001\003\001\001\001\010\001\003\001\002\001\008\001\
\014\001\035\001\008\001\002\001\002\001\004\001\005\001\002\001\
\001\001\023\001\024\001\010\001\026\001\027\001\001\001\014\001\
\022\001\003\001\008\001\033\001\034\001\035\001\036\001\025\001\
\023\001\024\001\003\001\026\001\027\001\003\001\002\001\001\001\
\004\001\005\001\033\001\034\001\035\001\036\001\010\001\003\001\
\003\001\003\001\014\001\003\001\027\000\002\001\032\000\004\001\
\255\255\255\255\255\255\023\001\024\001\010\001\026\001\027\001\
\255\255\014\001\255\255\255\255\002\001\033\001\034\001\035\001\
\036\001\255\255\023\001\024\001\010\001\026\001\027\001\092\000\
\014\001\094\000\255\255\255\255\033\001\034\001\035\001\036\001\
\101\000\255\255\255\255\255\255\105\000\255\255\255\255\255\255\
\001\001\255\255\003\001\033\001\034\001\035\001\036\001\008\001\
\009\001\010\001\011\001\012\001\255\255\255\255\015\001\016\001\
\017\001\018\001\019\001\020\001\021\001\022\001\001\001\028\001\
\029\001\030\001\031\001\255\255\255\255\255\255\009\001\010\001\
\011\001\012\001\255\255\255\255\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\001\001\009\001\010\001\011\001\
\012\001\255\255\255\255\255\255\009\001\010\001\011\001\012\001\
\255\255\255\255\015\001\016\001\017\001\018\001\019\001\020\001\
\021\001\022\001\001\001\255\255\003\001\255\255\255\255\255\255\
\255\255\008\001\009\001\010\001\255\255\255\255\255\255\255\255\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\022\001\
\003\001\255\255\255\255\255\255\255\255\255\255\009\001\010\001\
\011\001\012\001\255\255\255\255\015\001\016\001\017\001\018\001\
\019\001\020\001\021\001\022\001\028\001\029\001\030\001\031\001\
\032\001\001\001\255\255\003\001\255\255\255\255\255\255\255\255\
\008\001\009\001\010\001\255\255\255\255\255\255\255\255\015\001\
\016\001\017\001\018\001\019\001\020\001\021\001\022\001\001\001\
\255\255\003\001\255\255\255\255\255\255\255\255\008\001\255\255\
\255\255\255\255\255\255\255\255\255\255\015\001\016\001\017\001\
\018\001\019\001\020\001\021\001\022\001\001\001\255\255\003\001\
\255\255\255\255\255\255\255\255\008\001\255\255\255\255\255\255\
\255\255\255\255\255\255\015\001\016\001\017\001\018\001\019\001\
\020\001\021\001\022\001\001\001\255\255\003\001\255\255\255\255\
\255\255\255\255\008\001\255\255\255\255\255\255\255\255\255\255\
\255\255\015\001\016\001\017\001\018\001\019\001\020\001\021\001\
\022\001\001\001\255\255\003\001\255\255\255\255\255\255\255\255\
\008\001\255\255\255\255\255\255\255\255\255\255\255\255\015\001\
\016\001\017\001\018\001\019\001\020\001\021\001\022\001\001\001\
\255\255\003\001\001\001\255\255\003\001\255\255\008\001\255\255\
\255\255\008\001\255\255\255\255\255\255\015\001\016\001\255\255\
\015\001\016\001\003\001\021\001\022\001\255\255\021\001\022\001\
\009\001\010\001\011\001\012\001\255\255\255\255\015\001\016\001\
\017\001\018\001\019\001\020\001\021\001\022\001\003\001\255\255\
\255\255\255\255\255\255\255\255\009\001\010\001\011\001\012\001\
\255\255\255\255\015\001\016\001\017\001\018\001\019\001\020\001\
\021\001\022\001\009\001\010\001\011\001\012\001\255\255\255\255\
\015\001\016\001\017\001\018\001\019\001\020\001\021\001\009\001\
\010\001\011\001\012\001\255\255\255\255\015\001\016\001\017\001\
\018\001\019\001\020\001\009\001\010\001\011\001\012\001\255\255\
\255\255\255\255\255\255\017\001\018\001\019\001\020\001"

let yynames_const = "\
  SEMI\000\
  LPAREN\000\
  RPAREN\000\
  LBRACE\000\
  RBRACE\000\
  LBRACKET\000\
  RBRACKET\000\
  COMMA\000\
  PLUS\000\
  MINUS\000\
  TIMES\000\
  DIVIDE\000\
  ASSIGN\000\
  NOT\000\
  EQ\000\
  NEQ\000\
  LT\000\
  LEQ\000\
  GT\000\
  GEQ\000\
  AND\000\
  OR\000\
  RETURN\000\
  IF\000\
  ELSE\000\
  FOR\000\
  WHILE\000\
  INT\000\
  BOOL\000\
  FLOAT\000\
  VOID\000\
  DEFINE\000\
  EOF\000\
  "

let yynames_block = "\
  LITERAL\000\
  BLIT\000\
  ID\000\
  FLIT\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decls) in
    Obj.repr(
# 32 "parser.mly"
            ( _1 )
# 342 "parser.ml"
               : Ast.program))
; (fun __caml_parser_env ->
    Obj.repr(
# 35 "parser.mly"
                 ( ([], [])               )
# 348 "parser.ml"
               : 'decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decls) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'vdecl) in
    Obj.repr(
# 36 "parser.mly"
               ( ((_2 :: fst _1), snd _1) )
# 356 "parser.ml"
               : 'decls))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decls) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'fdecl) in
    Obj.repr(
# 37 "parser.mly"
               ( (fst _1, (_2 :: snd _1)) )
# 364 "parser.ml"
               : 'decls))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 8 : 'typ) in
    let _3 = (Parsing.peek_val __caml_parser_env 7 : string) in
    let _5 = (Parsing.peek_val __caml_parser_env 5 : 'formals_opt) in
    let _8 = (Parsing.peek_val __caml_parser_env 2 : 'vdecl_list) in
    let _9 = (Parsing.peek_val __caml_parser_env 1 : 'stmt_list) in
    Obj.repr(
# 41 "parser.mly"
     ( { typ = _2;
	 fname = _3;
	 formals = List.rev _5;
	 locals = List.rev _8;
	 body = List.rev _9 } )
# 379 "parser.ml"
               : 'fdecl))
; (fun __caml_parser_env ->
    Obj.repr(
# 48 "parser.mly"
                  ( [] )
# 385 "parser.ml"
               : 'formals_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'formal_list) in
    Obj.repr(
# 49 "parser.mly"
                  ( _1 )
# 392 "parser.ml"
               : 'formals_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'typ) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 52 "parser.mly"
                             ( [(_1,_2)]     )
# 400 "parser.ml"
               : 'formal_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'formal_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'typ) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 53 "parser.mly"
                             ( (_3,_4) :: _1 )
# 409 "parser.ml"
               : 'formal_list))
; (fun __caml_parser_env ->
    Obj.repr(
# 56 "parser.mly"
          ( Int   )
# 415 "parser.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 57 "parser.mly"
          ( Bool  )
# 421 "parser.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 58 "parser.mly"
          ( Float )
# 427 "parser.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 59 "parser.mly"
          ( Void  )
# 433 "parser.ml"
               : 'typ))
; (fun __caml_parser_env ->
    Obj.repr(
# 62 "parser.mly"
                     ( [] )
# 439 "parser.ml"
               : 'vdecl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'vdecl_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'vdecl) in
    Obj.repr(
# 63 "parser.mly"
                     ( _2 :: _1 )
# 447 "parser.ml"
               : 'vdecl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'typ) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string) in
    Obj.repr(
# 66 "parser.mly"
               ( (_1, _2) )
# 455 "parser.ml"
               : 'vdecl))
; (fun __caml_parser_env ->
    Obj.repr(
# 69 "parser.mly"
                   ( [] )
# 461 "parser.ml"
               : 'stmt_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'stmt_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 70 "parser.mly"
                   ( _2 :: _1 )
# 469 "parser.ml"
               : 'stmt_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 73 "parser.mly"
                                            ( Expr _1               )
# 476 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr_opt) in
    Obj.repr(
# 74 "parser.mly"
                                            ( Return _2             )
# 483 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'stmt_list) in
    Obj.repr(
# 75 "parser.mly"
                                            ( Block(List.rev _2)    )
# 490 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 76 "parser.mly"
                                            ( If(_3, _5, Block([])) )
# 498 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'stmt) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 77 "parser.mly"
                                            ( If(_3, _5, _7)        )
# 507 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 6 : 'expr_opt) in
    let _5 = (Parsing.peek_val __caml_parser_env 4 : 'expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 2 : 'expr_opt) in
    let _9 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 79 "parser.mly"
                                            ( For(_3, _5, _7, _9)   )
# 517 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'stmt) in
    Obj.repr(
# 80 "parser.mly"
                                            ( While(_3, _5)         )
# 525 "parser.ml"
               : 'stmt))
; (fun __caml_parser_env ->
    Obj.repr(
# 83 "parser.mly"
                  ( Noexpr )
# 531 "parser.ml"
               : 'expr_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 84 "parser.mly"
                  ( _1 )
# 538 "parser.ml"
               : 'expr_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : int) in
    Obj.repr(
# 87 "parser.mly"
                     ( Literal(_1)            )
# 545 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 88 "parser.mly"
              ( Fliteral(_1)           )
# 552 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : bool) in
    Obj.repr(
# 89 "parser.mly"
                     ( BoolLit(_1)            )
# 559 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string) in
    Obj.repr(
# 90 "parser.mly"
                     ( Id(_1)                 )
# 566 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 91 "parser.mly"
                     ( Binop(_1, Add,   _3)   )
# 574 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 92 "parser.mly"
                     ( Binop(_1, Sub,   _3)   )
# 582 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 93 "parser.mly"
                     ( Binop(_1, Mult,  _3)   )
# 590 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 94 "parser.mly"
                     ( Binop(_1, Div,   _3)   )
# 598 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 95 "parser.mly"
                     ( Binop(_1, Equal, _3)   )
# 606 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 96 "parser.mly"
                     ( Binop(_1, Neq,   _3)   )
# 614 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 97 "parser.mly"
                     ( Binop(_1, Less,  _3)   )
# 622 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 98 "parser.mly"
                     ( Binop(_1, Leq,   _3)   )
# 630 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 99 "parser.mly"
                     ( Binop(_1, Greater, _3) )
# 638 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 100 "parser.mly"
                     ( Binop(_1, Geq,   _3)   )
# 646 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 101 "parser.mly"
                     ( Binop(_1, And,   _3)   )
# 654 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 102 "parser.mly"
                     ( Binop(_1, Or,    _3)   )
# 662 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 103 "parser.mly"
                         ( Unop(Neg, _2)      )
# 669 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 104 "parser.mly"
                     ( Unop(Not, _2)          )
# 676 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 105 "parser.mly"
                     ( Assign(_1, _3)         )
# 684 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'args_opt) in
    Obj.repr(
# 106 "parser.mly"
                              ( Call(_1, _3)  )
# 692 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'expr) in
    Obj.repr(
# 107 "parser.mly"
                       ( _2                   )
# 699 "parser.ml"
               : 'expr))
; (fun __caml_parser_env ->
    Obj.repr(
# 110 "parser.mly"
                  ( [] )
# 705 "parser.ml"
               : 'args_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'args_list) in
    Obj.repr(
# 111 "parser.mly"
               ( List.rev _1 )
# 712 "parser.ml"
               : 'args_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 114 "parser.mly"
                            ( [_1] )
# 719 "parser.ml"
               : 'args_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'args_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'expr) in
    Obj.repr(
# 115 "parser.mly"
                         ( _3 :: _1 )
# 727 "parser.ml"
               : 'args_list))
(* Entry program *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let program (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Ast.program)
