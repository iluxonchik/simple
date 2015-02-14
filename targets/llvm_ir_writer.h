// $Id: llvm_ir_writer.h,v 1.2 2014/05/05 19:35:34 david Exp $ -*- c++ -*-
#ifndef __SIMPLE_LLVM_IR_WRITER_H__
#define __SIMPLE_LLVM_IR_WRITER_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>

namespace simple {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class llvm_ir_writer: public basic_ast_visitor {
    cdk::symbol_table<simple::symbol> &_symtab;
    llvm::Module *_module;
    std::map<std::string, llvm::Value*> _named_values;
    llvm::IRBuilder<> _builder;

    llvm::Type *_voidTy;
    llvm::IntegerType *_integerTy;
    llvm::PointerType *_stringTy;

    llvm::Value *_child = nullptr;
    llvm::Function *_function = nullptr;  // current function

  public:
    llvm_ir_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<simple::symbol> &symtab, llvm::Module *module) :
        basic_ast_visitor(compiler), //
        _symtab(symtab), _module(module), _builder(_module->getContext()), //
        _voidTy(llvm::Type::getVoidTy(_module->getContext())), //
        _integerTy(llvm::IntegerType::get(_module->getContext(), 32)), //
        _stringTy(llvm::PointerType::get(llvm::IntegerType::get(_module->getContext(), 8), 0)) {
    }

  public:
    ~llvm_ir_writer() {
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
    void do_while_node(cdk::while_node * const node, int lvl);
    void do_if_node(cdk::if_node * const node, int lvl);
    void do_if_else_node(cdk::if_else_node * const node, int lvl);

  public:
    void do_lvalue_node(simple::lvalue_node * const node, int lvl);
    void do_rvalue_node(simple::rvalue_node * const node, int lvl);

  public:
    void do_program_node(simple::program_node * const node, int lvl);
    void do_evaluation_node(simple::evaluation_node * const node, int lvl);
    void do_print_node(simple::print_node * const node, int lvl);
    void do_read_node(simple::read_node * const node, int lvl);
    void do_assignment_node(simple::assignment_node * const node, int lvl);

  };

} // simple

#endif
