// $Id: xml_target.h,v 1.1 2014/05/02 22:33:16 david Exp $
#ifndef __SIMPLE_SEMANTICS_XML_EVALUATOR_H__
#define __SIMPLE_SEMANTICS_XML_EVALUATOR_H__

#include <cdk/basic_target.h>
#include <cdk/compiler.h>
#include "targets/xml_writer.h"

namespace simple {

  class xml_target: public cdk::basic_target {
    static xml_target _self;

  private:
    inline xml_target() :
        cdk::basic_target("xml") {
    }

  public:
    bool evaluate(std::shared_ptr<cdk::compiler> compiler) {
      xml_writer writer(compiler);
      compiler->ast()->accept(&writer, 0);
      return true;
    }

  };

} // simple

#endif
