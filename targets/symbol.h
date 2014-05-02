// $Id: symbol.h,v 1.1 2014/05/02 22:33:16 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_SEMANTICS_SYMBOL_H__
#define __SIMPLE_SEMANTICS_SYMBOL_H__

#include <string>

namespace simple {

    class symbol {
      int _type;
      std::string _name;
      int _value;

    public:
      inline symbol(int type, const std::string &name, int value) :
          _type(type), _name(name), _value(value) {
      }

      inline symbol(int type, const char *name, int value) :
          _type(type), _name(name), _value(value) {
      }

      virtual ~symbol() {
      }

      inline int type() const {
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
