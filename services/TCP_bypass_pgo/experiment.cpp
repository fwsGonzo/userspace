// This file is a part of the IncludeOS unikernel - www.includeos.org
//
// Copyright 2015 Oslo and Akershus University College of Applied Sciences
// and Alfred Bratterud
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <os>
#include <rtc>
#include <net/interfaces>
#include <statman>
#include <profile>
#include <cstdio>
#include <util/units.hpp>

using namespace net::tcp;

#define ENABLE_JUMBO_FRAMES
static const size_t   BUFFER_SIZE = 1024*1024*50;
static const uint16_t PORT_SEND = 1337;
static const uint16_t PORT_RECV = 1338;

static const uint32_t winsize = 8192;
static const uint8_t  wscale  = 5;
static const bool     timestamps = true;
static const bool     SACK = true;
static const std::chrono::milliseconds dack {40};
static buffer_t blob = nullptr;
static uint64_t packets_rx = 0;
static uint64_t packets_tx = 0;
static uint64_t received = 0;
static uint64_t ts = 0;
extern void exit_decision();

static void recv(size_t len)
{
  received += len;
}

static void start_measure()
{
  received    = 0;
  packets_rx  = Statman::get().get_by_name("eth0.ethernet.packets_rx").get_uint64();
  packets_tx  = Statman::get().get_by_name("eth0.ethernet.packets_tx").get_uint64();
  printf("<Settings> BUFSZ=%zukB DACK=%lims WSIZE=%u WS=%u CALC_WIN=%ukB TS=%s SACK=%s\n",
    BUFFER_SIZE / 1024,
    dack.count(), winsize, wscale, (winsize << wscale) / 1024,
    timestamps ? "ON" : "OFF",
    SACK ? "ON" : "OFF");
  ts          = RTC::nanos_now();
}

static void stop_measure()
{
  auto diff   = RTC::nanos_now() - ts;
  packets_rx  = Statman::get().get_by_name("eth0.ethernet.packets_rx").get_uint64() - packets_rx;
  packets_tx  = Statman::get().get_by_name("eth0.ethernet.packets_tx").get_uint64() - packets_tx;
  printf("Packets RX [%lu] TX [%lu]\n", packets_rx, packets_tx);
  double durs   = (double) diff / 1000000000ULL;
  double mbits  = (double(received)/(1024*1024)*8) / durs;

  printf("Duration: %.3fs - Payload: %s - %.2f MBit/s\n",
         durs, util::Byte_r(received).to_string().c_str(), mbits);
  exit_decision();
}

void begin_experiment()
{
  blob = net::tcp::construct_buffer(BUFFER_SIZE, '!');

  extern void create_network_device(int N, const char* ip);
  create_network_device(0, "10.0.0.1/24");
  auto& lxp_inet = net::Interfaces::get(0);
  lxp_inet.network_config({10,0,0,42}, {255,255,255,0}, {10,0,0,1});

  // Get the first IP stack configured from config.json
  auto& inet = net::Interfaces::get(0);
  auto& tcp = inet.tcp();
  tcp.set_DACK(dack); // default
  tcp.set_MSL(std::chrono::seconds(3));

  tcp.set_window_size(winsize, wscale);
  tcp.set_timestamps(timestamps);
  tcp.set_SACK(SACK);

  tcp.listen(PORT_SEND).on_connect([](Connection_ptr conn)
  {
    printf("%s connected. Sending file %zu MB\n",
            conn->remote().to_string().c_str(),
            BUFFER_SIZE / (1024*1024));
    start_measure();

    conn->on_disconnect([] (Connection_ptr self, Connection::Disconnect)
    {
      if(!self->is_closing())
        self->close();
      stop_measure();
    });
    conn->on_write(recv);
    conn->write(blob);
    conn->close();
  });

  tcp.listen(PORT_RECV).on_connect(
    [] (Connection_ptr conn)
  {
    printf("%s connected. Receiving file %zu MB\n",
            conn->remote().to_string().c_str(),
            BUFFER_SIZE / (1024*1024));

    start_measure();

    conn->on_disconnect([] (Connection_ptr self,
                            Connection::Disconnect reason)
    {
      (void) reason;
      if(const auto bytes_sacked = self->bytes_sacked(); bytes_sacked)
        printf("SACK: %zu bytes (%zu kB)\n", bytes_sacked, bytes_sacked/(1024));

      if(!self->is_closing())
        self->close();

      stop_measure();
    });
    conn->on_read(16384,
      [] (buffer_t buf)
      {
        recv(buf->size());
      });
  });
}

#ifdef ENABLE_JUMBO_FRAMES
#include <hw/nic.hpp>
namespace hw {
  uint16_t Nic::MTU_detection_override(int idx, const uint16_t default_MTU)
  {
    if (idx == 0) return 9000;
    return default_MTU;
  }
}
#endif
