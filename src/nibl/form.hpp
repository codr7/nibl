#ifndef NIBL_FORM_HPP
#define NIBL_FORM_HPP

#include <deque>
#include <memory>
#include <optional>

#include "nibl/error.hpp"
#include "nibl/pos.hpp"

namespace nibl {
  struct VM;
  
  struct Form {
    struct Imp {      
      const Pos pos;

      Imp(Pos pos);
      virtual ~Imp();
      virtual void dump(ostream& out) const = 0;
      virtual optional<Error> emit(VM &vm, deque<Form> &args) const = 0;
    };

    const shared_ptr<const Imp> imp;
    
    Form(shared_ptr<const Imp> imp);
    void dump(ostream& out) const;
    optional<Error> emit(VM &vm, deque<Form> &args) const;
    
    template <typename T>
    const typename T::Imp &as() const { return *static_cast<const typename T::Imp *>(imp.get()); }
  };

  ostream &operator<<(ostream &out, Form val);
}

#endif
