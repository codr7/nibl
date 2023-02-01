#ifndef NIBL_FORMS_INTERP_HPP
#define NIBL_FORMS_INTERP_HPP

#include "nibl/form.hpp"
#include "nibl/types.hpp"
#include "nibl/val.hpp"

namespace nibl::forms {
  using namespace nibl;
  
  struct Interp: Form {
    struct Imp: Form::Imp {
      const Str spec;
      
      Imp(const Pos &pos, Str &&spec);    
      void dump(ostream& out) const override;
      E emit(VM &vm, Env &env, deque<Form> &args) const override;
    };

    Interp(const Pos &pos, Str &&spec);
  };
}

#endif
