#include <service>

void Service::start(const std::string&)
{
  extern void begin_experiment();
  begin_experiment();
}

void exit_decision()
{
#ifndef FINAL
  exit(0);
#endif
}