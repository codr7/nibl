#ifndef NIBL_LIBS_ABC_HPP
#define NIBL_LIBS_ABC_HPP

#include "nibl/error.hpp"
#include "nibl/lib.hpp"
#include "nibl/macro.hpp"
#include "nibl/prim.hpp"
#include "nibl/type.hpp"

namespace nibl::libs {
  using namespace nibl;
  
  struct BoolType: Type {
    BoolType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << (val.as<bool>() ? 'T' : 'F'); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<bool>() == val2.as<bool>(); }
  };

  struct CharType: Type {
    CharType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << val.as<Char>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Char>() == val2.as<Char>(); }
  };

  struct FunType: Type {
    FunType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << *val.as<Fun *>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Fun *>() == val2.as<Fun *>(); }
  };

  struct IntType: Type {
    IntType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << val.as<Int>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Int>() == val2.as<Int>(); }
  };

  struct LibType: Type {
    LibType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << *val.as<Lib *>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Lib *>() == val2.as<Lib *>(); }
  };

  struct MacroType: Type {
    MacroType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << *val.as<Macro *>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    
    bool eq(const Val &val1, const Val &val2) const override {
      return val1.as<Macro *>() == val2.as<Macro *>();
    }
  };

  struct MetaType: Type {
    MetaType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << *val.as<Type *>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Type *>() == val2.as<Type *>(); }
  };

  struct PrimType: Type {
    PrimType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << *val.as<Prim *>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Prim *>() == val2.as<Prim *>(); }
  };

  struct StrType: Type {
    StrType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override { out << '"' << val.as<Str>() << '"'; }
    void write(const Val &val, ostream &out) const override { out << val.as<Str>(); }
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override { return val1.as<Str>() == val2.as<Str>(); }
  };

  struct ABC: Lib {
    BoolType bool_type;
    CharType char_type;
    FunType fun_type;
    IntType int_type;
    LibType lib_type;
    MacroType macro_type;
    MetaType meta_type;
    PrimType prim_type;
    StrType str_type;

    Macro add_macro, and_macro, bench_macro, dec_macro, def_macro, div_macro, dup_macro, dup_rotl_macro,
      else_macro, eq_macro, fun_macro, gt_macro, if_macro, lt_macro, mod_macro, mul_macro, not_macro,
      or_macro, pop_macro, rec_macro, ret_macro, rotl_macro, rotr_macro, stop_macro, sub_macro, swap_macro,
      test_macro, trace_macro;

    Prim ask_prim, call_prim, load_prim, parse_int_prim, say_prim, to_str_prim, type_of_prim;
    
    ABC(VM &vm, Env &env, const optional<Pos> &pos);
  };
}

#endif
