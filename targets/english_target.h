// $Id: english_target.h,v 1.1 2014/05/02 22:33:16 david Exp $
#ifndef __SIMPLE_SEMANTICS_ENGLISH_EVALUATOR_H__
#define __SIMPLE_SEMANTICS_ENGLISH_EVALUATOR_H__

#include <cdk/basic_target.h>
#include <cdk/ast/basic_node.h>
#include <cdk/compiler.h>
#include "targets/english_writer.h"

namespace simple {

  class english_target: public cdk::basic_target {
    static english_target _self;

  private:
    inline english_target() :
        cdk::basic_target("english") {
    }

  public:
    bool evaluate(std::shared_ptr<cdk::compiler> compiler) {
      english_writer writer(compiler);
      compiler->ast()->accept(&writer, 0);
      return true;
    }

  };

} // simple

#endif
