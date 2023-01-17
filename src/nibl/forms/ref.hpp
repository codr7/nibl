#ifndef NIBL_FORMS_REF_HPP
#define NIBL_FORMS_REF_HPP

#include "nibl/form.hpp"
#include "nibl/val.hpp"

namespace nibl::forms {
  using namespace nibl;
  
  struct Ref: Form {
    struct Imp: Form::Imp {
      const string name;
      
      Imp(const Pos &pos, string &&name);    
      void dump(ostream& out) const override;
      optional<Error> emit(VM &vm, deque<Form> &args) const override;
    };

    Ref(const Pos &pos, string &&name);
  };
}

#endif
