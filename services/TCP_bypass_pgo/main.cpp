#include <service>

void Service::start(const std::string&)
{
  extern void begin_experiment();
  begin_experiment();
}

void exit_decision()
{
#ifndef FINAL
  static int sample_counter = 0;
  if (++sample_counter >= 30) {
    exit(0);
  }
#endif
}