#ifndef NIBL_FORM_HPP
#define NIBL_FORM_HPP

#include <memory>

#include "nibl/error.hpp"
#include "nibl/pos.hpp"

namespace nibl {
  struct VM;
  
  struct Form {
    struct Imp {      
      virtual ~Imp();
      virtual void dump(ostream& out) const = 0;
      virtual void emit(VM &vm) const = 0;
    };

    const Pos pos;
    const shared_ptr<const Imp> imp;
    
    Form(Pos pos, shared_ptr<const Imp> imp);
    void dump(ostream& out) const;
    void emit(VM &vm) const;
    
    template <typename T>
    const typename T::Imp &as() const { return *static_cast<const typename T::Imp *>(imp.get()); }
  };

  ostream &operator<<(ostream &out, Form val);
}

#endif
