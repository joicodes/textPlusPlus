(* Semantic checking for textPlusPlus compiler *)

open Ast
open Sast

module StringMap = Map.Make(String)

(* Semantic checking of the AST. Returns an SAST if successful,
   throws an exception if something is wrong.

   Check each global variable, then check each function *)

let check (globals, functions) =

  (* Verify a list of bindings has no void types or duplicate names *)
  let check_binds (kind : string) (binds : bind list) =
    List.iter (function
	(Void, b) -> raise (Failure ("Illegal void " ^ kind ^ " " ^ b))
      | _ -> ()) binds;
    let rec dups = function
        [] -> ()
      |	((_,n1) :: (_,n2) :: _) when n1 = n2 ->
	  raise (Failure ("Duplicate name" ^ kind ^ " " ^ n1))
      | _ :: t -> dups t
    in dups (List.sort (fun (_,a) (_,b) -> compare a b) binds)
  in

  (**** Check global variables ****)

  check_binds "global" globals;

  (**** Check functions ****)

  (* Collect function declarations for built-in functions: no bodies *)
   
    let built_in_decls =  
    
    StringMap.add "addPage"
     { typ = Int; fname = "addPage"; formals = [];
       locals = []; body = [] }



       (StringMap.add "left"
     { typ = Void; fname = "left"; formals = [];
       locals = []; body = [] }

       (StringMap.add "right"
     { typ = Void; fname = "right"; formals = [];
       locals = []; body = [] }

       (StringMap.add "center"
     { typ = Void; fname = "center"; formals = [];
       locals = []; body = [] }

       (StringMap.add "write"
       { typ = Void; fname = "write"; formals = [(String, "x")];
          locals = []; body = [] }

        (StringMap.add "textOut"
      { typ = Void; fname = "textOut"; formals = [(Int, "y"); (Int, "z"); (String, "x");];
        locals = []; body = [] }

        ( StringMap.add "moveTo"
      { typ = Void; fname = "moveTo"; formals = [(Int, "x"); (Int, "y")];
        locals = []; body = [] } 
  


       (StringMap.add "bold"
     { typ = Void; fname = "bold"; formals = [];
       locals = []; body = [] }

        (StringMap.add "italic"
    { typ = Void; fname = "italic"; formals = [];
        locals = []; body = [] }

        (StringMap.add "regular"
    { typ = Void; fname = "regular"; formals = [];
        locals = []; body = [] }

        (StringMap.add "changeColor"
    { typ = Void; fname = "changeColor"; formals = [(Float, "x"); (Float, "y"); (Float, "z")];
        locals = []; body = [] }

        (StringMap.add "changeFontSize"
    { typ = Void; fname = "changeFontSize"; formals = [(String, "x"); (Int, "y")];
        locals = []; body = [] }



        (StringMap.add "drawLine"
    { typ = Void; fname = "drawLine"; formals = [(Int, "x"); (Int, "y"); (Int, "z"); (Int, "a")];
        locals = []; body = [] }

        (StringMap.add "drawRectangle"
     { typ = Void; fname = "drawRectangle"; formals = [(Int, "x"); (Int, "y"); (Int, "z"); (Int, "a")];
        locals = []; body = [] }



        (StringMap.add "pageNumber"
        { typ = Int; fname = "pageNumber"; formals = [(Int, "x"); (Int, "y");];
           locals = []; body = [] }
           


        (StringMap.add "getTextWidth"
     { typ = Int; fname = "getTextWidth"; formals = [(String, "x")];
        locals = []; body = [] }

        (StringMap.add "getPageHeight"
     { typ = Int; fname = "getPageHeight"; formals = [];
        locals = []; body = [] }

        (StringMap.add "getPageWidth"
     { typ = Int; fname = "getPageWidth"; formals = [];
        locals = []; body = [] } 


        (StringMap.add "pageTitle"
     { typ = Void; fname = "pageTitle"; formals = [(String, "x");];
        locals = []; body = [] } 

        (StringMap.add "table"
        { typ = Void; fname = "table"; formals = [(Int, "x"); (Int, "y"); (Int, "z"); (Int, "a")];
           locals = []; body = [] } 

        
        (StringMap.add "heading1"
        { typ = Void; fname = "heading1"; formals = [];
           locals = []; body = [] } 

        (StringMap.add "heading2"
        { typ = Void; fname = "heading2"; formals = [];
          locals = []; body = [] } 
        
        (StringMap.add "heading3"
        { typ = Void; fname = "heading3"; formals = [];
            locals = []; body = [] }    

        (StringMap.add "heading4"
        { typ = Void; fname = "heading4"; formals = [];
            locals = []; body = [] } 

        (StringMap.add "heading5"
        { typ = Void; fname = "heading5"; formals = [];
          locals = []; body = [] } 

        (StringMap.add "heading6"
        { typ = Void; fname = "heading6"; formals = [];
            locals = []; body = [] }

        (StringMap.add "getCurrentY"
        { typ = Int; fname = "getCurrentY"; formals = [];
            locals = []; body = [] }

        (StringMap.add "getCurrentX"
        { typ = Int; fname = "getCurrentX"; formals = [];
            locals = []; body = [] }

        (StringMap.add "getCapHeight"
        { typ = Int; fname = "getCapHeight"; formals = [];
            locals = []; body = [] }

        (StringMap.add "getLowHeight"
        { typ = Int; fname = "getLowHeight"; formals = [];
            locals = []; body = [] }

        (StringMap.add "getTextBytes"
        { typ = Int; fname = "getTextBytes"; formals = [(String, "x"); (Int, "y"); (Int, "z")];
            locals = []; body = [] }
        
        (StringMap.add "setRMargin"
        { typ = Int; fname = "setRMargin"; formals = [(Int, "y")];
            locals = []; body = [] }

        (StringMap.add "setLMargin"
        { typ = Int; fname = "setLMargin"; formals = [(Int, "y")];
            locals = []; body = [] }

        (StringMap.add "setTopMargin"
        { typ = Int; fname = "setTopMargin"; formals = [(Int, "y")];
            locals = []; body = [] }

        (StringMap.add "setBotMargin"
        { typ = Int; fname = "setBotMargin"; formals = [(Int, "y")];
            locals = []; body = [] } StringMap.empty

     ))))))))))))))))))))))))))))))))))
  
  in

  (* Add function name to symbol table *)
  let add_func map fd = 
    let built_in_err = "The function " ^ fd.fname ^ " is a built in function and may not be defined."
    and dup_err = "Duplicate function name: " ^ fd.fname 
    and make_err er = raise (Failure er)
    and n = fd.fname (* Name of the function *)
    in match fd with (* No duplicate functions or redefinitions of built-ins *)
         _ when StringMap.mem n built_in_decls -> make_err built_in_err
       | _ when StringMap.mem n map -> make_err dup_err  
       | _ ->  StringMap.add n fd map 
  in

  (* Collect all function names into one symbol table *)
  let function_decls = List.fold_left add_func built_in_decls functions
  in
  
  (* Return a function from our symbol table *)
  let find_func s = 
    try StringMap.find s function_decls
    with Not_found -> raise (Failure ("The following function is undefined: " ^ s))
  in

  (* let _ = find_func "main" in (* Ensure "main" is defined *) *)

  let check_function func =
    (* Make sure no formals or locals are void or duplicates *)
    check_binds "formal" func.formals;
    check_binds "local" func.locals;

    (* Raise an exception if the given rvalue type cannot be assigned to
       the given lvalue type *)
    let check_assign lvaluet rvaluet err =
       if lvaluet = rvaluet then lvaluet else raise (Failure err)
    in   

    (* Build local symbol table of variables for this function *)
    let symbols = List.fold_left (fun m (ty, name) -> StringMap.add name ty m)
	                StringMap.empty (globals @ func.formals @ func.locals )
    in

    (* Return a variable from our local symbol table *)
    let type_of_identifier s =
      try StringMap.find s symbols
      with Not_found -> raise (Failure ("The following variable is undeclared: " ^ s))
    in

    (* Return a semantically-checked expression, i.e., with a type *)
    let rec expr = function
        Literal  l -> (Int, SLiteral l)
      | StrLiteral l -> (String, SStrLiteral l)
      | Fliteral l -> (Float, SFliteral l)
      | BoolLit l  -> (Bool, SBoolLit l)
      | Noexpr     -> (Void, SNoexpr)
      | Id s       -> (type_of_identifier s, SId s)
      | Assign(var, e) as ex -> 
          let lt = type_of_identifier var
          and (rt, e') = expr e in
          let err = "Illegal assignment of a" ^ string_of_typ lt ^ " to a " ^ 
            string_of_typ rt ^ " in " ^ string_of_expr ex
          in (check_assign lt rt err, SAssign(var, (rt, e')))
      | Unop(op, e) as ex -> 
          let (t, e') = expr e in
          let ty = match op with
            Neg when t = Int || t = Float -> t
          | Not when t = Bool -> Bool
          | _ -> raise (Failure ("Illegal use of unary operator with a " ^ 
                                 string_of_uop op ^ string_of_typ t ^
                                 " in " ^ string_of_expr ex))
          in (ty, SUnop(op, (t, e')))
      | Binop(e1, op, e2) as e -> 
          let (t1, e1') = expr e1 
          and (t2, e2') = expr e2 in
          (* All binary operators require operands of the same type *)
          let same = t1 = t2 in
          (* Determine expression type based on operator and operand types *)
          let ty = match op with
            Add | Sub | Mult | Div when same && t1 = Int   -> Int
          | Add | Sub | Mult | Div when same && t1 = Float -> Float
          | Equal | Neq            when same               -> Bool
          | Less | Leq | Greater | Geq
                     when same && (t1 = Int || t1 = Float) -> Bool
          | And | Or when same && t1 = Bool -> Bool
          | _ -> raise (
	      Failure ("Illegal binary operator " ^
                       string_of_typ t1 ^ " " ^ string_of_op op ^ " " ^
                       string_of_typ t2 ^ " in " ^ string_of_expr e))
          in (ty, SBinop((t1, e1'), op, (t2, e2')))
      | Call(fname, args) as call -> 
          let fd = find_func fname in
          let param_length = List.length fd.formals in
          if List.length args != param_length then
            raise (Failure ("The function expected " ^ string_of_int param_length ^ 
                            " arguments in " ^ string_of_expr call))
          else let check_call (ft, _) e = 
            let (et, e') = expr e in 
            let err = "Illegal argument found " ^ string_of_typ et ^
              " expected " ^ string_of_typ ft ^ " in " ^ string_of_expr e
            in (check_assign ft et err, e')
          in 
          let args' = List.map2 check_call fd.formals args
          in (fd.typ, SCall(fname, args'))
    in

    let check_bool_expr e = 
      let (t', e') = expr e
      and err = "Expected Boolean expression in " ^ string_of_expr e
      in if t' != Bool then raise (Failure err) else (t', e') 
    in

    (* Return a semantically-checked statement i.e. containing sexprs *)
    let rec check_stmt = function
        Expr e -> SExpr (expr e)
      | If(p, b1, b2) -> SIf(check_bool_expr p, check_stmt b1, check_stmt b2)
      | For(e1, e2, e3, st) ->
	  SFor(expr e1, check_bool_expr e2, expr e3, check_stmt st)
      | While(p, s) -> SWhile(check_bool_expr p, check_stmt s)
      | Return e -> let (t, e') = expr e in
        if t = func.typ then SReturn (t, e') 
        else raise (
	  Failure ("Return gives " ^ string_of_typ t ^ " expected " ^
		   string_of_typ func.typ ^ " in " ^ string_of_expr e))
	    
	    (* A block is correct if each statement is correct and nothing
	       follows any Return statement.  Nested blocks are flattened. *)
      | Block sl -> 
          let rec check_stmt_list = function
              [Return _ as s] -> [check_stmt s]
            | Return _ :: _   -> raise (Failure "Nothing may follow a return statement.")
            | Block sl :: ss  -> check_stmt_list (sl @ ss) (* Flatten blocks *)
            | s :: ss         -> check_stmt s :: check_stmt_list ss
            | []              -> []
          in SBlock(check_stmt_list sl)

    in (* body of check_function *)
    { styp = func.typ;
      sfname = func.fname;
      sformals = func.formals;
      slocals  = func.locals;
      sbody = match check_stmt (Block func.body) with
	SBlock(sl) -> sl
      | _ -> raise (Failure ("internal error: block didn't become a block?"))
    }
  in (globals, List.map check_function functions)
