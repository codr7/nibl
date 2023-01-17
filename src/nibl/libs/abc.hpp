#ifndef NIBL_LIBS_ABC_HPP
#define NIBL_LIBS_ABC_HPP

#include "nibl/error.hpp"
#include "nibl/lib.hpp"
#include "nibl/type.hpp"

namespace nibl::libs {
  using namespace nibl;
  
  struct BoolType: Type {
    BoolType(Lib &lib, string &&name);
    void dump(const Val &val, ostream &out) const override;
    optional<Error> emit(VM &vm, const Val &val) const override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct IntType: Type {
    IntType(Lib &lib, string &&name);
    void dump(const Val &val, ostream &out) const override;
    optional<Error> emit(VM &vm, const Val &val) const override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct MacroType: Type {
    MacroType(Lib &lib, string &&name);
    void dump(const Val &val, ostream &out) const override;
    optional<Error> emit(VM &vm, const Val &val) const override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct MetaType: Type {
    MetaType(Lib &lib, string &&name);
    void dump(const Val &val, ostream &out) const override;
    optional<Error> emit(VM &vm, const Val &val) const override;
    bool eq(const Val &val1, const Val &val2) const override;
  };

  struct ABC: Lib {
    BoolType bool_type;
    IntType int_type;
    MacroType macro_type;
    MetaType meta_type;

    const Macro add_macro, and_macro, div_macro, dup_macro, else_macro, eq_macro, gt_macro, if_macro, lt_macro,
      mod_macro, mul_macro, not_macro, or_macro, pop_macro, stop_macro, sub_macro, swap_macro, trace_macro,
      type_of_macro;
    
    ABC(VM &vm);
  };
}

#endif
