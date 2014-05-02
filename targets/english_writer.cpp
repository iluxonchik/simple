// $Id: english_writer.cpp,v 1.1 2014/05/02 22:33:16 david Exp $ -*- c++ -*-
#include <string>
#include <stack>
#include "targets/english_writer.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void simple::english_writer::do_data_node(cdk::data_node * const node, int lvl) {
  std::string listsep = "";
  if (node->size() > 1)
    listsep = ", ";
  os() << "this is some data with " << node->size() << " bytes, containing the following: ";
  for (size_t i = 0; i < node->size() - 1; i++) {
    os() << ((unsigned char*)node->bucket())[i] << listsep;
  }
  if (node->size() > 1) {
    os() << " and ";
    os() << ((unsigned char*)node->bucket())[node->size() - 1];
  }
}

void simple::english_writer::do_composite_node(cdk::composite_node * const node, int lvl) {
  std::string listsep = "";
  if (node->size() > 1)
    listsep = ", ";
  os() << "this is a composition containing " << node->size() << " elements, namely the following: ";
  for (size_t i = 0; i < node->size() - 1; i++) {
    node->at(i)->accept(this, lvl + 2);
    os() << listsep;
  }
  if (node->size() > 1) {
    os() << " and ";
    node->at(node->size() - 1)->accept(this, lvl + 2);
  }
}

//---------------------------------------------------------------------------

void simple::english_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  //os() << "what follows is a sequence containing " << node->size() << " elements. ";
  //os() << "let's call it sequence " << seqcounter << ". ";
  //seqstack.push(seqcounter++);
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl + 2);
  }
  //os() << "thus, we reach the end of sequence " << seqstack.top() << ". ";
  //seqstack.pop();
}

//---------------------------------------------------------------------------

void simple::english_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  //os() << "integer number with value " << node->value();
  os() << node->value();
}

void simple::english_writer::do_double_node(cdk::double_node * const node, int lvl) {
  os() << "double precision floating point number with value " << node->value();
}

void simple::english_writer::do_string_node(cdk::string_node * const node, int lvl) {
  //os() << "string with value " << node->value();
  os() << "i have to say: \"" << node->value() << "\". ";
}

//---------------------------------------------------------------------------

inline void simple::english_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void simple::english_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

inline void simple::english_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl,
                                                             const std::string &op) {
  node->left()->accept(this, lvl + 2);
  os() << " " << op << " ";
  node->right()->accept(this, lvl + 2);
}

void simple::english_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "plus");
}
void simple::english_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "minus");
}
void simple::english_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "multiplied by");
}
void simple::english_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "divided by");
}
void simple::english_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  os() << "the rest of the division of ";
  processBinaryExpression(node, lvl, "by");
}
void simple::english_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "is less than");
}
void simple::english_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "is less than or equal to");
}
void simple::english_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "is greater than or equal to");
}
void simple::english_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "is greater than");
}
void simple::english_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "is different from");
}
void simple::english_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl, "is equal to");
}

//---------------------------------------------------------------------------

void simple::english_writer::do_rvalue_node(simple::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
}

//---------------------------------------------------------------------------

void simple::english_writer::do_lvalue_node(simple::lvalue_node * const node, int lvl) {
  os() << "\"" << node->value() << "\"";
}

//---------------------------------------------------------------------------

void simple::english_writer::do_program_node(simple::program_node * const node, int lvl) {
  os() << "hello, i am a program. ";
  node->statements()->accept(this, lvl + 4);
  os() << "we have reached the end of our journey. i hope you enjoyed it as much as i did.";
}

//---------------------------------------------------------------------------

void simple::english_writer::do_evaluation_node(simple::evaluation_node * const node, int lvl) {
  os() << "do ";
  node->argument()->accept(this, lvl + 2);
  os() << ". ";
}

void simple::english_writer::do_print_node(simple::print_node * const node, int lvl) {
  os() << "this is ";
  node->argument()->accept(this, lvl + 2);
  os() << ". ";
}

//---------------------------------------------------------------------------

void simple::english_writer::do_read_node(simple::read_node * const node, int lvl) {
  os() << "please give me a value to put in ";
  node->argument()->accept(this, lvl + 2);
  os() << ". ";
}

void simple::english_writer::do_assignment_node(simple::assignment_node * const node, int lvl) {
  os() << "set ";
  node->lvalue()->accept(this, lvl + 2);
  os() << " to ";
  node->rvalue()->accept(this, lvl + 4);
  os() << ". ";
}

//---------------------------------------------------------------------------

void simple::english_writer::do_while_node(simple::while_node * const node, int lvl) {
  os() << "while ";
  node->condition()->accept(this, lvl + 4);
  os() << " do as follows. ";
  node->block()->accept(this, lvl + 4);
  os() << "alas, the cycle we started by testing whether ";
  node->condition()->accept(this, lvl + 4);
  os() << " ends. "; // multiple ways...
}

//---------------------------------------------------------------------------

void simple::english_writer::do_if_node(simple::if_node * const node, int lvl) {
  os() << "if ";
  node->condition()->accept(this, lvl + 4);
  os() << " then do as follows. ";
  node->block()->accept(this, lvl + 4);
  os() << "and that's it: the actions we described since testing whether "; // multiple ways...
  node->condition()->accept(this, lvl + 4);
  os() << " end. "; // multiple ways...
}

void simple::english_writer::do_if_else_node(simple::if_else_node * const node, int lvl) {
  os() << "if ";
  node->condition()->accept(this, lvl + 4);
  os() << " then do as follows. ";
  node->thenblock()->accept(this, lvl + 4);
  os() << "that's all, if things go as planned. otherwise, do as follows. ";
  node->elseblock()->accept(this, lvl + 4);
  os() << "and that's it: the actions we described since testing whether "; // multiple ways...
  node->condition()->accept(this, lvl + 4);
  os() << " end. "; // multiple ways...
}
