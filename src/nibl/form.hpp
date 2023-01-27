#ifndef NIBL_FORM_HPP
#define NIBL_FORM_HPP

#include <deque>
#include <memory>
#include <optional>

#include "nibl/error.hpp"
#include "nibl/pos.hpp"

namespace nibl {
  struct Env;
  struct VM;

  struct Form {
    struct Imp {      
      const Pos pos;
      
      Imp(const Pos &pos);
      virtual ~Imp();
      virtual void dump(ostream& out) const = 0;
      virtual E emit(VM &vm, Env &env, deque<Form> &args) const = 0;
    };

    static const shared_ptr<const Imp> END;
    
    const shared_ptr<const Imp> imp;
    
    Form(shared_ptr<const Imp> imp);
    void dump(ostream& out);
    E emit(VM &vm, Env &env, deque<Form> &args);
    
    template <typename T>
    const typename T::Imp *is() const { return dynamic_cast<const typename T::Imp *>(imp.get()); }

    template <typename T>
    const typename T::Imp &as() const { return *static_cast<const typename T::Imp *>(imp.get()); }
  };

  using Forms = deque<Form>;

  ostream &operator<<(ostream &out, Form val);
}

#endif
