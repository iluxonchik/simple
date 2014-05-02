// $Id: assignment_node.h,v 1.1 2014/05/02 22:33:16 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_ASSIGNMENTNODE_H__
#define __SIMPLE_ASSIGNMENTNODE_H__

#include "ast/lvalue_node.h"

namespace simple {

  /**
   * Class for describing assignment nodes.
   */
  class assignment_node: public cdk::expression_node {
    simple::lvalue_node *_lvalue;
    cdk::expression_node *_rvalue;

  public:
    inline assignment_node(int lineno, simple::lvalue_node *lvalue, cdk::expression_node *rvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue), _rvalue(rvalue) {
    }

  public:
    inline simple::lvalue_node *lvalue() {
      return _lvalue;
    }
    inline cdk::expression_node *rvalue() {
      return _rvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_assignment_node(this, level);
    }

  };

} // simple

#endif
