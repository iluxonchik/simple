// $Id: symbol.h,v 1.2 2014/05/04 22:40:57 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_SEMANTICS_SYMBOL_H__
#define __SIMPLE_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace simple {

    class symbol {
      const basic_type *_type;
      std::string _name;
      int _value; // hack!

    public:
      inline symbol(const basic_type *type, const std::string &name, int value) :
          _type(type), _name(name), _value(value) {
      }

      virtual ~symbol() {
        delete _type;
      }

      inline const basic_type *type() const {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline int value() const {
        return _value;
      }
      inline int value(int v) {
        return _value = v;
      }
    };

} // simple

#endif
