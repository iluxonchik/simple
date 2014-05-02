// $Id: english_writer.h,v 1.1 2014/05/02 22:33:16 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_SEMANTICS_ENGLISH_WRITER_H__
#define __SIMPLE_SEMANTICS_ENGLISH_WRITER_H__

#include <string>
#include <iostream>
#include "targets/basic_ast_visitor.h"

namespace simple {

  /**
   * Print nodes as English language to the output stream.
   */
  class english_writer: public basic_ast_visitor {

  public:
    english_writer(std::shared_ptr<cdk::compiler> compiler) :
        basic_ast_visitor(compiler) {
    }

  public:
    ~english_writer() {
      os().flush();
    }

  private:
    inline void openTag(const std::string &tag, int lvl) {
      //os() << std::string(lvl, ' ') + "<" + tag + ">" << std::endl;
    }
    inline void openTag(const cdk::basic_node *node, int lvl) {
      //openTag(node->name(), lvl);
    }
    inline void closeTag(const std::string &tag, int lvl) {
      //os() << std::string(lvl, ' ') + "</" + tag + ">" << std::endl;
    }
    inline void closeTag(const cdk::basic_node *node, int lvl) {
      //closeTag(node->name(), lvl);
    }

  public:
    void do_nil_node(cdk::nil_node * const node, int lvl) {
    }
    void do_data_node(cdk::data_node * const node, int lvl);
    void do_composite_node(cdk::composite_node * const node, int lvl);
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);
    void do_identifier_node(cdk::identifier_node * const node, int lvl) {
    }

  protected:
    void processUnaryExpression(cdk::unary_expression_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

  protected:
    void processBinaryExpression(cdk::binary_expression_node * const node, int lvl, const std::string &op);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);

  public:
    void do_lvalue_node(simple::lvalue_node * const node, int lvl);
    void do_rvalue_node(simple::rvalue_node * const node, int lvl);

  public:
    void do_program_node(simple::program_node * const node, int lvl);
    void do_evaluation_node(simple::evaluation_node * const node, int lvl);
    void do_print_node(simple::print_node * const node, int lvl);
    void do_read_node(simple::read_node * const node, int lvl);
    void do_while_node(simple::while_node * const node, int lvl);
    void do_assignment_node(simple::assignment_node * const node, int lvl);
    void do_if_node(simple::if_node * const node, int lvl);
    void do_if_else_node(simple::if_else_node * const node, int lvl);

  };

} // simple

#endif
