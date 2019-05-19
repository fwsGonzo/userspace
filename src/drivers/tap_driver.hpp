#pragma once
#include <delegate>
#include <string>
#include <vector>
#include <sys/epoll.h>

struct TAP_driver
{
  typedef delegate<void(const void*, int)> on_read_func;
  TAP_driver(const char* dev, const char* ip);
  ~TAP_driver();

  uint16_t MTU() const noexcept { return this->mtu; }

  int get_fd() const { return tun_fd; }
  int read (char *buf, int len);
  int write(const void* buf, int len);

  int bridge_add_if(const std::string& bridge);
private:
  int set_if_up();
  int set_if_route(const char* cidr);
  int set_if_address(const char* ip);
  int alloc_tun();

  int tun_fd;
  uint16_t mtu;
  std::string m_dev;
  epoll_event m_epoll;
};
