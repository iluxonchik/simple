// $Id: postfix_writer.cpp,v 1.1 2014/05/02 22:33:16 david Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void simple::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value()); // push an integer
}

void simple::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  // NOTHING TO DO: Simple doesn't have floating point numbers.
}
void simple::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.STR(node->value()); // output string characters

  // Strings in Simple are always written:

  /* make the call */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
  _pf.CALL("prints"); // call the print rotine
  _pf.TRASH(4); // remove the string label
  _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.ADD();
}
void simple::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}
void simple::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MUL();
}
void simple::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.DIV();
}
void simple::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void simple::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void simple::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void simple::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void simple::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void simple::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void simple::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_rvalue_node(simple::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  _pf.LOAD(); //FIXME: depends on type size
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_lvalue_node(simple::lvalue_node * const node, int lvl) {
  const std::string &id = node->value();
  if (_symtab.find(id)) {
    _pf.ADDR(id);
  }
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_program_node(simple::program_node * const node, int lvl) {
  // Note that Simple doesn't have functions. Thus, it doesn't need
  // a function node. However, it must start in the main function.
  // The ProgramNode (representing the whole program) doubles as a
  // main function node.

  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  _pf.ALIGN();
  _pf.GLOBAL("_main", _pf.FUNC());
  _pf.LABEL("_main");
  _pf.ENTER(0);  // Simple doesn't implement local variables

  node->statements()->accept(this, lvl);

  // end the main function
  _pf.INT(0);
  _pf.POP();
  _pf.LEAVE();
  _pf.RET();

  // these are just a few library function imports
  _pf.EXTERN("readi");
  _pf.EXTERN("printi");
  _pf.EXTERN("prints");
  _pf.EXTERN("println");
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_evaluation_node(simple::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl); // determine the value
  _pf.TRASH(4); //FIXME: delete the evaluated value
}

void simple::postfix_writer::do_print_node(simple::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl); // determine the value to print
  _pf.CALL("printi"); //FIXME: call to the print function
  _pf.TRASH(4); // delete the printed value
  _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_read_node(simple::read_node * const node, int lvl) {
  _pf.CALL("readi");
  _pf.PUSH();
  node->argument()->accept(this, lvl);
  _pf.STORE();
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_while_node(simple::while_node * const node, int lvl) {
  int lbl1, lbl2;
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl2 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl1));
  _pf.LABEL(mklbl(lbl2));
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_assignment_node(simple::assignment_node * const node, int lvl) {
  // DAVID: horrible hack!
  // (this is caused by Simple not having explicit variable declarations)
  const std::string &id = node->lvalue()->value();
  if (!_symtab.find(id)) {
    _pf.DATA(); // variables are all global and live in DATA
    _pf.ALIGN(); // make sure we are aligned
    _pf.LABEL(id); // name variable location
    _pf.CONST(0); // initialize it to 0 (zero)
    _pf.TEXT(); // return to the TEXT segment
    _symtab.insert(id, std::make_shared<simple::symbol>(0, id, 0)); // put in the symbol table
  }

  try {
    simple::type_checker checker(_compiler, _symtab);
    node->accept(&checker, 0);
  }
  catch (std::string &problem) {
    std::cerr << "FATAL: " << problem << std::endl;
    return;
  }

  node->rvalue()->accept(this, lvl); // determine the new value
  _pf.DUP();
  node->lvalue()->accept(this, lvl); // where to store the value
  _pf.STORE(); // store the value at address
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_if_node(simple::if_node * const node, int lvl) {
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void simple::postfix_writer::do_if_else_node(simple::if_else_node * const node, int lvl) {
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}
