#include <service>
#include <net/interfaces>
#include <cstdio>
static std::map<net::tcp::Connection_ptr, int> conn_timers;

void Service::start()
{
  extern void create_network_device(int N, const char* ip);
  create_network_device(0, "10.0.0.1/24");

  auto& inet = net::Interfaces::get(0);
  inet.network_config({10,0,0,59}, {255,255,255,0}, {10,0,0,1});
  const uint16_t port = 666;

  auto& server = inet.tcp().listen(port);
  server.on_connect(
  [port] (auto conn)
  {
    const int t = Timers::oneshot(std::chrono::seconds(15),
        [conn] (int) {
          printf("Connection that is not closed yet:\n%s\n",
                  conn->to_string().c_str());
        });
    conn_timers[conn] = t;
    //auto* buffer = new std::vector<uint8_t>;
    auto* buffer = new std::deque<uint8_t>;
    //buffer->reserve(38*1024*1024);
    // retrieve binary
    conn->on_read(9000,
    [conn, buffer] (auto buf)
    {
      buffer->insert(buffer->end(), buf->begin(), buf->end());
    })
    .on_close(
    [conn, buffer] () {
      const int t = conn_timers[conn];
      Timers::stop(t);
      conn_timers.erase(conn);
      //printf("* Blob size: %zu b  at %p\n", buffer->size(), buffer->data());
      printf("%zu\n", buffer->size());
      delete buffer;

      static int counter = 0;
      if (counter++ == 10) exit(0);
    });
  });
}
