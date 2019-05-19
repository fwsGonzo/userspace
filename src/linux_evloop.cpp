#include "epoll_evloop.hpp"

#include "drivers/tap_driver.hpp"
#include <hw/usernet.hpp>
#include <net/inet>
#include <deque>
#include <vector>

struct usernet_with_tap  {
  std::unique_ptr<TAP_driver> tap;
  UserNet& usernet;
  std::deque<net::Packet_ptr> writeq;
  
  void read_packets();
  void write_packets();
  void transmit(net::Packet_ptr);
};
static std::vector<usernet_with_tap> devices;

void usernet_with_tap::read_packets()
{
  int count = 64; // read no more than X packets
  while (count-- > 0)
  {
    //auto packet = this->usernet.get_buffer();
    //int len =
    //  this->tap->read((char*) packet->layer_begin(), packet->capacity());
    auto* buffer = new char[8192];
    int len =
      this->tap->read(buffer, usernet.packet_len());
    
    if (LIKELY(len > 0))
    {
      usernet.receive(buffer, len);
      // queue packet for usernet
      //packet->set_data_end(len);
      //this->usernet.receive(std::move(packet));
    }
    else {
      break;
    }
  }
}
void usernet_with_tap::write_packets()
{
  while (!writeq.empty())
  {
    auto& packet = writeq.front();
    int len = tap->write(packet->layer_begin(), packet->size());
    if (len < 0) break;
    writeq.pop_front();
  }
}
void usernet_with_tap::transmit(net::Packet_ptr packet)
{
  this->writeq.push_back(std::move(packet));
  this->write_packets();
}

// create TAP device and hook up packet receive to UserNet driver
void create_network_device(int N, const char* ip, const uint16_t MTU)
{
  const std::string name = "tap" + std::to_string(N);
  auto tap = std::make_unique<TAP_driver> (name.c_str(), ip);
  // the IncludeOS packet communicator
  const uint16_t MIN_MTU = std::min(tap->MTU(), MTU);
  auto& usernet = UserNet::create(MIN_MTU);
  // store device combo
  devices.push_back({std::move(tap), usernet, std::deque<net::Packet_ptr>{}});
  const size_t idx = devices.size()-1;
  // connect driver to tap device
  usernet.set_transmit_forward(
    [idx] (net::Packet_ptr packet) {
      devices[idx].transmit(std::move(packet));
    });
}

namespace linux
{
  static int epoll_init_if_needed()
  {
    static int epoll_fd = -1;
    if (epoll_fd == -1) {
      if ((epoll_fd = epoll_create(1)) < 0)
      {
        fprintf(stderr, "ERROR when creating epoll fd\n");
        std::abort();
      }
    }
    return epoll_fd;
  }
  void epoll_add_fd(int fd, epoll_event& event)
  {
    const int efd = epoll_init_if_needed();
    // register event to epoll instance
    if (epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event) < 0)
    {
      fprintf(stderr, "ERROR when adding fd to epoll\n");
      std::abort();
    }
  }
  void epoll_del_fd(int fd)
  {
    const int efd = epoll_init_if_needed();
    // unregister event to epoll instance
    if (epoll_ctl(efd, EPOLL_CTL_DEL, fd, nullptr) < 0)
    {
      fprintf(stderr, "ERROR when removing fd from epoll\n");
      std::abort();
    }
  }
  void epoll_wait_events()
  {
    // get timeout from time to next timer in timer system
    // NOTE: when next is 0, it means there is no next timer
    const unsigned long long next = Timers::next().count();
    int timeout = (next == 0) ? -1 : (1 + next / 1000000ull);

    if (timeout < 0 && devices.empty()) {
      printf("epoll_wait_events(): Deadlock reached\n");
      std::abort();
    }

    const int efd = epoll_init_if_needed();
    std::array<epoll_event, 16> events;
    //printf("epoll_wait(%d milliseconds) next=%llu\n", timeout, next);
    int ready = epoll_wait(efd, events.data(), events.size(), timeout);
    if (ready < 0) {
      // ignore interruption from signals
      if (errno == EINTR) return;
      printf("[TAP] ERROR when waiting for epoll event\n");
      std::abort();
    }
    for (int i = 0; i < ready; i++)
    {
      for (auto& dev : devices)
      {
        const int fd = events.at(i).data.fd;
        if (dev.tap->get_fd() == fd)
        {
          if (events.at(i).events & EPOLLIN) {
            dev.read_packets();
          }
          if (events.at(i).events & EPOLLOUT) {
            dev.write_packets();
            if (dev.usernet.transmit_queue_available() > 0) {
              dev.usernet.signal_tqa();
            }
          }
          break;
        } // tap devices
      }
    }
  } // epoll_wait_events()
}
