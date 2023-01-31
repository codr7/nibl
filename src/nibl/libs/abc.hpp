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
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct FunType: Type {
    FunType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct IntType: Type {
    IntType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct LibType: Type {
    LibType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct MacroType: Type {
    MacroType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct MetaType: Type {
    MetaType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct PrimType: Type {
    PrimType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct StrType: Type {
    StrType(VM &vm, Env &env, const optional<Pos> &pos);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct ABC: Lib {
    BoolType bool_type;
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
