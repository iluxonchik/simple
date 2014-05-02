// $Id: rvalue_node.h,v 1.1 2014/05/02 22:33:16 david Exp $
#ifndef __SIMPLE_RVALUE_NODE_H__
#define __SIMPLE_RVALUE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace simple {

  /**
   * Class for describing rvalue nodes.
   */
  class rvalue_node: public cdk::expression_node {
    simple::lvalue_node *_lvalue;

  public:
    inline rvalue_node(int lineno, simple::lvalue_node *lvalue) :
        cdk::expression_node(lineno), _lvalue(lvalue) {
    }

  public:
    inline cdk::expression_node *lvalue() {
      return _lvalue;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_rvalue_node(this, level);
    }

  };

} // simple

#endif
