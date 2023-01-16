#ifndef NIBL_FORMS_ID_HPP
#define NIBL_FORMS_ID_HPP

#include "nibl/form.hpp"
#include "nibl/val.hpp"

namespace nibl::forms {
  using namespace nibl;
  
  struct Id: Form {
    struct Imp: Form::Imp {
      const string name;
      
      Imp(string &&name);    
      void dump(Form &form, ostream& out) const override;
      optional<Error> emit(VM &vm, Form &form, deque<Form> &args) const override;
    };

    Id(const Pos &pos, string &&name);
  };
}

#endif
