#include <iostream>

#include <ostream>

#include "nibl/form.hpp"
#include "nibl/forms/id.hpp"
#include "nibl/forms/lit.hpp"
#include "nibl/fun.hpp"
#include "nibl/libs/abc.hpp"
#include "nibl/types.hpp"
#include "nibl/vm.hpp"

namespace nibl::libs {
  BoolType::BoolType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Bool", pos) {}
  
  E BoolType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_bool(val.as<bool>());
    return nullopt;
  }

  CharType::CharType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Char", pos) {}
  
  E CharType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_char(val.as<Char>());
    return nullopt;
  }

  FunType::FunType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Fun", pos) {}
  
  E FunType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Fun *>()->tag);
    return nullopt;
  }

  IntType::IntType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Int", pos) {}
  
  E IntType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_int(val.as<Int>());
    return nullopt;
  }

  LibType::LibType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Lib", pos) {}
  
  E LibType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Lib *>()->tag);
    return nullopt;
  }

  MacroType::MacroType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Macro", pos) {}
  
  E MacroType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Macro *>()->tag);
    return nullopt;
  }

  MetaType::MetaType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Meta", pos) {}
  
  E MetaType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Type *>()->tag);
    return nullopt;
  }

  PrimType::PrimType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Prim", pos) {}
  
  E PrimType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Prim *>()->tag);
    return nullopt;
  }

  StrType::StrType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Str", pos) {}
  
  E StrType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(vm.tag(*this, val.as<Str>()));
    return nullopt;
  }

  ABC::ABC(VM &vm, Env &env, const optional<Pos> &pos):
    Lib(vm, env, "abc", pos),

    /* Types */
    bool_type(vm, env, pos),
    char_type(vm, env, pos),
    fun_type(vm, env, pos),
    int_type(vm, env, pos),
    lib_type(vm, env, pos),
    macro_type(vm, env, pos),
    meta_type(vm, env, pos),
    prim_type(vm, env, pos),
    str_type(vm, env, pos),

    /* Macros */
    add_macro(vm, env, "+", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) {
      vm.ops[vm.emit()] = ops::add();
      return nullopt;
    }),
    and_macro(vm, env, "and:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      const PC pc = vm.emit();
      if (auto e = pop_front(args).emit(vm, env, args); e) { return e; }
      vm.ops[pc] = ops::_and(vm.emit_pc());
      return nullopt;
    }),
    bench_macro(vm, env, "bench:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      vm.ops[vm.emit()] = ops::bench();
      
      while (!args.empty()) {
	Form f(pop_front(args));
	if (f.imp == Form::END) { break; }	
	if (auto e = f.emit(vm, env, args)) { return e; }
      }

      vm.ops[vm.emit()] = ops::stop();
      return nullopt;
    }),
    dec_macro(vm, env, "dec", pos, ops::dec()),
    def_macro(vm, env, "def:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      string id(pop_front(args).as<forms::Id>().name);
      optional<string> prev_name(env.def_name);
      env.def_name = id;
      if (auto e = pop_front(args).emit(vm, env, args); e) { return e; }
      env.def_name = prev_name;
      Val val(pop_front(args).as<forms::Lit>().val);
      env.bind(id, *val.type, val.data);
      return nullopt;
    }),
    div_macro(vm, env, "/", pos, ops::div()),
    dup_macro(vm, env, "dup", pos, ops::dup()),
    dup_rotl_macro(vm, env, "dup-rotl", pos, ops::dup_rotl()),
    else_macro(vm, env, "else:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) {
      return Error(pos, "Missing if");
    }),
    eq_macro(vm, env, "=", pos, ops::eq()),
    fun_macro(vm, env, "fun:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      const PC skip_pc = vm.emit(), fun_pc = vm.emit_pc();
      Fun *f = new Fun(vm, env, env.def_name, pos, fun_pc);
      if (f->name) { env.bind(*f->name, vm.abc_lib.fun_type, f); }

      while (!args.empty()) {
	Form f(pop_front(args));
	if (f.imp == Form::END) { break; }
	if (auto e = f.emit(vm, env, args)) { return e; }
      }

      if (auto c = op_code(vm.ops.back()); c != OpCode::RET) {
	vm.ops[vm.emit()] = ops::ret();
      }
	
      vm.ops[skip_pc] = ops::_goto(vm.emit_pc());
      args.emplace_front(forms::Lit(pos, vm.abc_lib.fun_type, f));
      return nullopt;
    }),
    gt_macro(vm, env, ">", pos, ops::gt()),
    if_macro(vm, env, "if:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      const PC pc = vm.emit();
      optional<PC> else_pc1, else_pc2;
      
      while (!args.empty()) {
	Form f(pop_front(args));
	if (f.imp == Form::END) { break; }	

	if (auto id = f.is<forms::Id>(); id && id->name == "else:") {
	  else_pc1 = vm.emit();
	  else_pc2 = vm.emit_pc();
	  continue;
	}
	
	if (auto e = f.emit(vm, env, args)) { return e; }
      }

      if (else_pc1) { vm.ops[*else_pc1] = ops::_goto(vm.emit_pc()); }
      
      vm.ops[pc] = ops::_if(else_pc2 ? *else_pc2 : vm.emit_pc());
      return nullopt;
    }),
    lt_macro(vm, env, "<", pos, ops::lt()),
    mod_macro(vm, env, "%", pos, ops::mod()),
    mul_macro(vm, env, "*", pos, ops::mul()),
    not_macro(vm, env, "not", pos, ops::_not()),
    or_macro(vm, env, "or:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      const PC pc = vm.emit();
      if (auto e = pop_front(args).emit(vm, env, args); e) { return e; }
      vm.ops[pc] = ops::_or(vm.emit_pc());
      return nullopt;
    }),
    pop_macro(vm, env, "pop", pos, ops::pop()),
    rec_macro(vm, env, "rec", pos, ops::rec()),
    ret_macro(vm, env, "ret", pos, ops::ret()),
    rotl_macro(vm, env, "rotl", pos, ops::rotl()),
    rotr_macro(vm, env, "rotr", pos, ops::rotr()),
    stop_macro(vm, env, "stop", pos, ops::stop()),
    sub_macro(vm, env, "-", pos, ops::sub()),
    swap_macro(vm, env, "swap", pos, ops::swap()),
    test_macro(vm, env, "test:", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) -> E {
      const PC pc = vm.emit();
      
      while (!args.empty()) {
	Form f = pop_front(args);
	if (f.imp == Form::END) { break; }	
	if (auto e = f.emit(vm, env, args)) { return e; }
      }

      vm.ops[vm.emit()] = ops::stop();
      vm.ops[pc] = ops::test();
      return nullopt;
    }),
    trace_macro(vm, env, "trace", pos, [](VM &vm, Env &env, Macro &macro, Forms &args, const Pos &pos) {
      vm.trace = !vm.trace;
      return nullopt;
    }),

    /* Prims */
    ask_prim(vm, env, "ask", [](VM &vm, Prim &prim, PC &pc) {
      Val &v = vm.stack.back();
      vm.stdout() << v.as<Str>();
      Str a;
      getline(vm.stdin(), a);
      v.data = a;
      return nullopt;
    }),
    call_prim(vm, env, "call", [](VM &vm, Prim &prim, PC &pc) {
      vm.call(*pop_back(vm.stack).as<Fun *>(), pc);
      return nullopt;
    }),
    load_prim(vm, env, "load", [](VM &vm, Prim &prim, PC &pc) {
      Pos pos("load", 1, 1);
      return vm.load(vm.pop().as<Str>(), pos, true);
    }),
    parse_int_prim(vm, env, "parse-int", [](VM &vm, Prim &prim, PC &pc) {      
      Val &v(vm.stack.back());
      istringstream s(v.as<Str>());

      Int i;
      s >> i;

      if (s.fail()) {
	v = Val(vm.abc_lib.bool_type, false);
	return nullopt;
      }
      
      v = Val(vm.abc_lib.int_type, i);
      vm.push(vm.abc_lib.str_type, s.str().substr(s.tellg()));
      return nullopt;
    }),
    say_prim(vm, env, "say", [](VM &vm, Prim &prim, PC &pc) {
      Val v(vm.pop());
      v.write(vm.stdout());
      vm.stdout() << endl;
      flush(vm.stdout());
      return nullopt;
    }),
    to_str_prim(vm, env, "to-str", [](VM &vm, Prim &prim, PC &pc) {
      Val &v(vm.stack.back());
      if (*v.type == vm.abc_lib.str_type) { return nullopt; }
      stringstream buf;
      buf << v;
      v = Val(vm.abc_lib.str_type, buf.str());
      return nullopt;
    }),
    type_of_prim(vm, env, "type-of", [](VM &vm, Prim &prim, PC &pc) {
      vm.stack.back() = Val(vm.abc_lib.meta_type, vm.stack.back().type);
      return nullopt;
    }) {
    bind("T", bool_type, true);
    bind("F", bool_type, false);    
  }
}
