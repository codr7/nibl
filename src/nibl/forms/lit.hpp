#ifndef NIBL_FORMS_LIT_HPP
#define NIBL_FORMS_LIT_HPP

#include "nibl/form.hpp"
#include "nibl/val.hpp"

namespace nibl::forms {
  using namespace nibl;
  
  struct Lit: Form {
    struct Imp: Form::Imp {
      const Val val;
      
      Imp(const Type &type, any &&data);    
      void dump(ostream& out) const override;
      void emit(VM &vm) const override;
    };

    Lit(Pos pos, const Type &type, any &&data);
  };
}

#endif
