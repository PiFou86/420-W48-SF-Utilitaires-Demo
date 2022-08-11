#pragma once

#include "BasicCommandInterpretor.h"

class SpecificCommandInterpretor : public BasicCommandInterpretor {
 protected:
  virtual bool interpret(const String &command,
                         const String &parameters) override;
  virtual bool getParameter(const String &key) override;
  virtual bool setParameter(const String &key, const String &value) override;

 public:
  SpecificCommandInterpretor(Stream &stream);
};