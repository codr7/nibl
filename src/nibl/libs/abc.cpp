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
  
  void BoolType::dump(const Val &val, ostream &out) const {
    out << (val.as<bool>() ? 'T' : 'F');
  }

  E BoolType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_bool(val.as<bool>());
    return nullopt;
  }

  bool BoolType::eq(const Val &val1, const Val &val2) const {
    return val1.as<bool>() == val2.as<bool>();
  }

  FunType::FunType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Fun", pos) {}
  
  void FunType::dump(const Val &val, ostream &out) const {
    out << *val.as<Fun *>();
  }

  E FunType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Fun *>()->tag);
    return nullopt;
  }

  bool FunType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Fun *>() == val2.as<Fun *>();
  }

  IntType::IntType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Int", pos) {}
  
  void IntType::dump(const Val &val, ostream &out) const {
    out << val.as<Int>();
  }

  E IntType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_int(val.as<Int>());
    return nullopt;
  }

  bool IntType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Int>() == val2.as<Int>();
  }

  LibType::LibType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Lib", pos) {}
  
  void LibType::dump(const Val &val, ostream &out) const {
    out << *val.as<Lib *>();
  }

  E LibType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Lib *>()->tag);
    return nullopt;
  }

  bool LibType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Lib *>() == val2.as<Lib *>();
  }

  MacroType::MacroType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Macro", pos) {}
  
  void MacroType::dump(const Val &val, ostream &out) const {
    out << *val.as<Macro *>();
  }

  E MacroType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Macro *>()->tag);
    return nullopt;
  }

  bool MacroType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Macro *>() == val2.as<Macro *>();
  }

  MetaType::MetaType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "Meta", pos) {}
  
  void MetaType::dump(const Val &val, ostream &out) const {
    out << *val.as<Type *>();
  }

  E MetaType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(val.as<Type *>()->tag);
    return nullopt;
  }

  bool MetaType::eq(const Val &val1, const Val &val2) const {
    return val1.as<Type *>() == val2.as<Type *>();
  }

  StringType::StringType(VM &vm, Env &env, const optional<Pos> &pos): Type(vm, env, "String", pos) {}
  
  void StringType::dump(const Val &val, ostream &out) const {
    out << '"' << val.as<string>() << '"';
  }

  E StringType::emit(VM &vm, Env &env, const Val &val) {
    vm.ops[vm.emit()] = ops::push_tag(vm.tag(*this, val.as<string>()));
    return nullopt;
  }

  bool StringType::eq(const Val &val1, const Val &val2) const {
    return val1.as<string>() == val2.as<string>();
  }

  ABC::ABC(VM &vm, Env &env, const optional<Pos> &pos):
    Lib(vm, env, "abc", pos),
    bool_type(vm, env, pos),
    fun_type(vm, env, pos),
    int_type(vm, env, pos),
    lib_type(vm, env, pos),
    macro_type(vm, env, pos),
    meta_type(vm, env, pos),
    string_type(vm, env, pos),
    add_macro(vm, env, "+", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) {
      vm.ops[vm.emit()] = ops::add();
      return nullopt;
    }),
    and_macro(vm, env, "and:", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) -> E {
      const PC pc = vm.emit();
      if (auto e = pop_front(args).emit(vm, env, args); e) { return e; }
      vm.ops[pc] = ops::_and(vm.pc);
      return nullopt;
    }),
    call_macro(vm, env, "call", pos, ops::call()),
    div_macro(vm, env, "/", pos, ops::div()),
    dup_macro(vm, env, "dup", pos, ops::dup()),
    else_macro(vm, env, "else:", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) {
	return Error(pos, "Missing if");
    }),
    eq_macro(vm, env, "=", pos, ops::eq()),
    fun_macro(vm, env, "fun:", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) -> E {
	const PC skip_pc = vm.emit();
	const PC fun_pc = vm.pc;
	
	while (!args.empty()) {
	  Form f = pop_front(args);
	  if (f.imp == Form::END) { break; }	
	  if (auto e = f.emit(vm, env, args)) { return e; }
	}

	if (auto c = op_code(vm.ops.back()); c != OpCode::REC && c != OpCode::RET) {
	  vm.ops[vm.emit()] = ops::ret();
	}
	
	vm.ops[skip_pc] = ops::_goto(vm.pc);
	Fun *f = new Fun(vm, env, env.def_name, pos, fun_pc);
	if (!env.def_name) { args.emplace_front(forms::Lit(pos, vm.abc_lib.fun_type, f)); }
	return nullopt;
      }),
    gt_macro(vm, env, ">", pos, ops::gt()),
    if_macro(vm, env, "if:", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) -> E {
      const PC pc = vm.emit();
      optional<PC> else_pc1, else_pc2;
      
      while (!args.empty()) {
	Form f = pop_front(args);
	if (f.imp == Form::END) { break; }	

	if (auto id = f.is<forms::Id>(); id && id->name == "else:") {
	  else_pc1 = vm.emit();
	  else_pc2 = vm.pc;
	  continue;
	}
	
	if (auto e = f.emit(vm, env, args)) { return e; }
      }

      if (else_pc1) {
	vm.ops[*else_pc1] = ops::_goto(vm.pc);
      }
      
      vm.ops[pc] = ops::_if(else_pc2 ? *else_pc2 : vm.pc);
      return nullopt;
    }),
    lt_macro(vm, env, "<", pos, ops::lt()),
    mod_macro(vm, env, "%", pos, ops::mod()),
    mul_macro(vm, env, "*", pos, ops::mul()),
    not_macro(vm, env, "not", pos, ops::_not()),
    or_macro(vm, env, "or:", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) -> E {
      const PC pc = vm.emit();
      if (auto e = pop_front(args).emit(vm, env, args); e) { return e; }
      vm.ops[pc] = ops::_or(vm.pc);
      return nullopt;
    }),
    pop_macro(vm, env, "pop", pos, ops::pop()),
    rec_macro(vm, env, "rec", pos, ops::rec()),
    ret_macro(vm, env, "ret", pos, ops::ret()),
    stop_macro(vm, env, "stop", pos, ops::stop()),
    sub_macro(vm, env, "-", pos, ops::sub()),
    swap_macro(vm, env, "swap", pos, ops::swap()),
    test_macro(vm, env, "test:", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) -> E {
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
    trace_macro(vm, env, "trace", pos, [](VM &vm, Env &env, Macro &macro, deque<Form> &args, Pos pos) {
      vm.trace = !vm.trace;
      return nullopt;
    }),
    type_of_macro(vm, env, "type-of", pos, ops::type_of()) {
    bind("T", bool_type, true);
    bind("F", bool_type, false);    
  }
}
