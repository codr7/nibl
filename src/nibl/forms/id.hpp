#ifndef NIBL_FORMS_ID_HPP
#define NIBL_FORMS_ID_HPP

#include "nibl/form.hpp"
#include "nibl/val.hpp"

namespace nibl::forms {
  using namespace nibl;
  
  struct Id: Form {
    struct Imp: Form::Imp {
      const string name;
      
      Imp(Pos pos, string &&name);    
      void dump(ostream& out) const override;
      optional<Error> emit(VM &vm) const override;
    };

    Id(Pos pos, string &&name);
  };
}

#endif
