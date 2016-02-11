// $Id: interpreter.h,v 1.2 2014/05/05 19:35:34 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_SEMANTICS_INTERPRETER_H__
#define __SIMPLE_SEMANTICS_INTERPRETER_H__

#include <string>
#include <iostream>
#include <vector>
#include <cdk/symbol_table.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace simple {

  //!
  //! Runs the program by interpreting the syntactic tree directly
  //!
  class interpreter: public basic_ast_visitor {

    // this is a rare anonymous class in C++
    class {
      std::vector<long> _stack;
    public:
      void push(long i) {
        _stack.push_back(i);
      }
      long pop() {
        long i = _stack.back();
        _stack.pop_back();
        return i;
      }
    } _stack;

    cdk::symbol_table<simple::symbol> &_symtab;

  public:
    interpreter(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<simple::symbol> &symtab) :
        basic_ast_visitor(compiler), _symtab(symtab) {
    }

  public:
    ~interpreter() {
      os().flush();
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);

  public:
    void do_neg_node(cdk::neg_node * const node, int lvl);

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
    void do_assignment_node(simple::assignment_node * const node, int lvl);

  public:
    void do_while_node(simple::while_node * const node, int lvl);
    void do_if_node(simple::if_node * const node, int lvl);
    void do_if_else_node(simple::if_else_node * const node, int lvl);

  };

} // simple

#endif
