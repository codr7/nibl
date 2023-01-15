#ifndef NIBL_LIBS_ABC_HPP
#define NIBL_LIBS_ABC_HPP

#include "nibl/error.hpp"
#include "nibl/lib.hpp"
#include "nibl/type.hpp"

namespace nibl::libs {
  using namespace nibl;
  
  struct BoolType: Type {
    BoolType(Lib &lib, string &&name);
    optional<Error> emit(VM &vm, const any &data) const override;
    void dump(any data, ostream &out) const override;
  };

  struct IntType: Type {
    IntType(Lib &lib, string &&name);
    optional<Error> emit(VM &vm, const any &data) const override;
    void dump(any data, ostream &out) const override;
  };

  struct MacroType: Type {
    MacroType(Lib &lib, string &&name);
    optional<Error> emit(VM &vm, const any &data) const override;
    void dump(any data, ostream &out) const override;
  };

  struct MetaType: Type {
    MetaType(Lib &lib, string &&name);
    optional<Error> emit(VM &vm, const any &data) const override;
    void dump(any data, ostream &out) const override;
  };

  struct ABC: Lib {
    const BoolType bool_type;
    const IntType int_type;
    const MacroType macro_type;
    const MetaType meta_type;

    const Macro add_macro, div_macro, dup_macro, gt_macro, lt_macro, mod_macro, mul_macro, pop_macro,
      sub_macro, swap_macro, trace_macro, typeof_macro;
    
    ABC(VM &vm);
  };
}

#endif
