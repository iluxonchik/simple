// $Id: read_node.h,v 1.1 2014/05/02 22:33:16 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_READNODE_H__
#define __SIMPLE_READNODE_H__

#include "ast/lvalue_node.h"

namespace simple {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::basic_node {
    simple::lvalue_node *_argument;

  public:
    inline read_node(int lineno, simple::lvalue_node *argument) :
        cdk::basic_node(lineno), _argument(argument) {
    }

  public:
    inline simple::lvalue_node *argument() {
      return _argument;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // simple

#endif
