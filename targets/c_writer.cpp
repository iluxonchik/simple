// $Id: c_writer.cpp,v 1.2 2014/05/04 22:40:57 david Exp $ -*- c++ -*-
#include <string>
#include "targets/c_writer.h"
#include "ast/all.h"  /* automatically generated */

//---------------------------------------------------------------------------

void simple::c_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl);
}

//---------------------------------------------------------------------------

void simple::c_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  os() << node->value();
}

void simple::c_writer::do_double_node(cdk::double_node * const node, int lvl) {
  os() << node->value();
}

void simple::c_writer::do_string_node(cdk::string_node * const node, int lvl) {
  os() << std::string(lvl + 2, ' ') << "printf(\"%s\\n\", \"" << node->value() << "\");\n";
}

//---------------------------------------------------------------------------

void simple::c_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  os() << " - ";
  node->argument()->accept(this, lvl);
}

//---------------------------------------------------------------------------

inline void simple::c_writer::do_binary_expression_node(cdk::binary_expression_node * const node, int lvl, const char *op) {
  node->left()->accept(this, lvl);
  os() << " " << op << " ";
  node->right()->accept(this, lvl);
}

void simple::c_writer::do_add_node(cdk::add_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "+");
}
void simple::c_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "-");
}
void simple::c_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "*");
}
void simple::c_writer::do_div_node(cdk::div_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "/");
}
void simple::c_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "%");
}
void simple::c_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "<");
}
void simple::c_writer::do_le_node(cdk::le_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "<=");
}
void simple::c_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, ">=");
}
void simple::c_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, ">");
}
void simple::c_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "!=");
}
void simple::c_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  do_binary_expression_node(node, lvl, "==");
}

//---------------------------------------------------------------------------

void simple::c_writer::do_rvalue_node(simple::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
}

//---------------------------------------------------------------------------

void simple::c_writer::do_lvalue_node(simple::lvalue_node * const node, int lvl) {
  const std::string &id = node->value();
  if (_symtab.find(id))
    os() << id;
  else
    throw 42; // life, the universe, and everything
}

//---------------------------------------------------------------------------

void simple::c_writer::do_program_node(simple::program_node * const node, int lvl) {
  // Note that Simple doesn't have functions. Thus, it doesn't need
  // a function node. However, it must start in the main function.
  // The ProgramNode (representing the whole program) doubles as a
  // main function node.

  // open the main function
  os() << "#include <stdio.h>\n" << "int main() {\n";

  node->statements()->accept(this, lvl);

  // close the outer function
  os() << "  return 0;\n}\n";
}

void simple::c_writer::do_evaluation_node(simple::evaluation_node * const node, int lvl) {
  os() << std::string(lvl + 2, ' ');
  node->argument()->accept(this, lvl);
  os() << ";\n";
}

void simple::c_writer::do_print_node(simple::print_node * const node, int lvl) {
  os() << std::string(lvl + 2, ' ') << "printf(\"%d\\n\", ";
  node->argument()->accept(this, lvl);
  os() << ");\n";
}

//---------------------------------------------------------------------------

void simple::c_writer::do_read_node(simple::read_node * const node, int lvl) {
  // DAVID: horrible hack!
  const char *id = node->argument()->value().c_str();
  if (_symtab.find(id))
    os() << std::string(lvl + 2, ' ') << "scanf(\"%d\", &" << id << ");\n";
}

void simple::c_writer::do_assignment_node(simple::assignment_node * const node, int lvl) {
  // DAVID: horrible hack!
  std::string id = node->lvalue()->value();
  if (_symtab.insert(id, std::make_shared<simple::symbol>(new basic_type(4, basic_type::TYPE_INT), id, 0))) {
    os() << std::string(lvl + 2, ' ');
    os() << "int " << id << ";\n";
  }
  os() << std::string(lvl + 2, ' ');
  node->lvalue()->accept(this, lvl);
  os() << " = ";
  node->rvalue()->accept(this, lvl);
  os() << ";\n";
}

//---------------------------------------------------------------------------

void simple::c_writer::do_while_node(simple::while_node * const node, int lvl) {
  os() << std::string(lvl + 2, ' ') << "while(";
  node->condition()->accept(this, lvl);
  os() << ") {\n";
  node->block()->accept(this, lvl + 2);
  os() << std::string(lvl + 2, ' ') << "}\n";
}

//---------------------------------------------------------------------------

void simple::c_writer::do_if_node(simple::if_node * const node, int lvl) {
  os() << std::string(lvl + 2, ' ') << "if (";
  node->condition()->accept(this, lvl);
  os() << ") {\n";
  node->block()->accept(this, lvl + 2);
  os() << std::string(lvl + 2, ' ') << "}\n";
}

void simple::c_writer::do_if_else_node(simple::if_else_node * const node, int lvl) {
  os() << std::string(lvl + 2, ' ') << "if (";
  node->condition()->accept(this, lvl);
  os() << ") {\n";
  node->thenblock()->accept(this, lvl + 2);
  os() << std::string(lvl + 2, ' ') << "} else {\n";
  node->elseblock()->accept(this, lvl + 2);
  os() << std::string(lvl + 2, ' ') << "}\n";
}
