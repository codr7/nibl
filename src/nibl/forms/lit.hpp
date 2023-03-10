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
      Imp(const Pos &pos, Type &type, const any &data);    
      void dump(ostream& out) const override;
      E emit(VM &vm, Env &env, deque<Form> &args) const override;
    };

    Lit(const Pos &pos, Type &type, any &&data);
    Lit(const Pos &pos, Type &type, const any &data);
  };
}

#endif
