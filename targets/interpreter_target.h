// $Id: interpreter_target.h,v 1.1 2014/05/02 22:33:16 david Exp $
#ifndef __SIMPLE_interpreter_target_H__
#define __SIMPLE_interpreter_target_H__

#include <cdk/basic_target.h>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include <cdk/compiler.h>
#include "targets/symbol.h"
#include "targets/interpreter.h"

namespace simple {

  class interpreter_target: public cdk::basic_target {
    static interpreter_target _self;

  private:
    inline interpreter_target() :
        cdk::basic_target("@@INTERPRET@@") {
    }

  public:
    bool evaluate(std::shared_ptr<cdk::compiler> compiler) {
      // this symbol table will be used to check identifiers
      cdk::symbol_table<simple::symbol> symtab;

      // - the interpreter will use the syntactic tree to directly run the program
      //   an exception will be thrown if identifiers are used before declaration
      // - the interpreter always uses the standard output
      interpreter interpreter(compiler, symtab);
      compiler->ast()->accept(&interpreter, 0);

      return true;
    }

  };

} // simple

#endif
