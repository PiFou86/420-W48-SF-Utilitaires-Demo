#include "Core/SpecificCommandInterpretor.h"

#include "Log/Logger.h"

SpecificCommandInterpretor::SpecificCommandInterpretor(Stream &stream)
    : BasicCommandInterpretor(stream) {
  ;
}

bool SpecificCommandInterpretor::interpret(const String &command,
                                           const String &parameters) {
  bool error = false;

  if (command == "specific") {
    Logger.println(F("specific Hello, world!"));
  } else if (command == "help") {
    Logger.println(F(""));
    Logger.println(F("  specific"));
    Logger.println(F(""));
    BasicCommandInterpretor::interpret(command, parameters);
  } else {
    error = !BasicCommandInterpretor::interpret(command, parameters);
  }

  return !error;
}

bool SpecificCommandInterpretor::getParameter(const String &key) {
  return BasicCommandInterpretor::getParameter(key);
}

bool SpecificCommandInterpretor::setParameter(const String &key,
                                              const String &value) {
  return BasicCommandInterpretor::setParameter(key, value);
}
