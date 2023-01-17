#ifndef NIBL_FORMS_LIT_HPP
#define NIBL_FORMS_LIT_HPP

#include "nibl/form.hpp"
#include "nibl/val.hpp"

namespace nibl::forms {
  using namespace nibl;
  
  struct Lit: Form {
    struct Imp: Form::Imp {
      const Val val;
      
      Imp(const Pos &pos, Type &type, any &&data);    
      void dump(ostream& out) const override;
      optional<Error> emit(VM &vm, deque<Form> &args) const override;
    };

    Lit(const Pos &pos, Type &type, any &&data);
  };
}

#endif
