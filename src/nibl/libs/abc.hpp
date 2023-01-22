#ifndef NIBL_LIBS_ABC_HPP
#define NIBL_LIBS_ABC_HPP

#include "nibl/error.hpp"
#include "nibl/lib.hpp"
#include "nibl/macro.hpp"
#include "nibl/type.hpp"

namespace nibl::libs {
  using namespace nibl;
  
  struct BoolType: Type {
    BoolType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct FuncType: Type {
    FuncType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct IntType: Type {
    IntType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct LibType: Type {
    LibType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct MacroType: Type {
    MacroType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct MetaType: Type {
    MetaType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct StringType: Type {
    StringType(VM &vm, Env &env);
    void dump(const Val &val, ostream &out) const override;
    E emit(VM &vm, Env &env, const Val &val) override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct ABC: Lib {
    BoolType bool_type;
    FuncType func_type;
    IntType int_type;
    LibType lib_type;
    MacroType macro_type;
    MetaType meta_type;
    StringType string_type;

    Macro add_macro, and_macro, call_macro, div_macro, dup_macro, else_macro, eq_macro, func_macro, gt_macro,
      if_macro, lt_macro, mod_macro, mul_macro, not_macro, or_macro, pop_macro, stop_macro, sub_macro,
      swap_macro, test_macro, trace_macro, type_of_macro;
    
    ABC(VM &vm, Env &env);
  };
}

#endif
