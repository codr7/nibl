#ifndef NIBL_LIBS_ABC_HPP
#define NIBL_LIBS_ABC_HPP

#include "nibl/error.hpp"
#include "nibl/lib.hpp"
#include "nibl/type.hpp"

namespace nibl::libs {
  using namespace nibl;
  
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
    const IntType int_type;
    const MacroType macro_type;
    const MetaType meta_type;

    const Macro dup_macro, pop_macro, swap_macro, trace_macro;
    
    ABC(VM &vm);
  };
}

#endif
