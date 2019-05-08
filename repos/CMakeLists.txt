set(NET_SOURCES
  ${IOSPATH}/src/net/addr.cpp
  ${IOSPATH}/src/net/buffer_store.cpp
  ${IOSPATH}/src/net/checksum.cpp
  ${IOSPATH}/src/net/configure.cpp
  ${IOSPATH}/src/net/interfaces.cpp
  ${IOSPATH}/src/net/inet.cpp
  ${IOSPATH}/src/net/packet_debug.cpp

  ${IOSPATH}/src/net/ethernet/ethernet.cpp
  ${IOSPATH}/src/net/ip4/arp.cpp
  ${IOSPATH}/src/net/ip4/ip4.cpp
  ${IOSPATH}/src/net/ip4/reassembly.cpp
  ${IOSPATH}/src/net/ip6/addr.cpp
  ${IOSPATH}/src/net/ip6/addr_list.cpp
  ${IOSPATH}/src/net/ip6/extension_header.cpp
  ${IOSPATH}/src/net/ip6/ip6.cpp
  ${IOSPATH}/src/net/ip6/icmp6.cpp
  ${IOSPATH}/src/net/ip6/mld.cpp
  ${IOSPATH}/src/net/ip6/ndp.cpp
  ${IOSPATH}/src/net/ip6/slaac.cpp

  ${IOSPATH}/src/net/tcp/tcp.cpp
  ${IOSPATH}/src/net/tcp/connection.cpp
  ${IOSPATH}/src/net/tcp/connection_states.cpp
  ${IOSPATH}/src/net/tcp/write_queue.cpp
  ${IOSPATH}/src/net/tcp/read_buffer.cpp
  ${IOSPATH}/src/net/tcp/read_request.cpp
  ${IOSPATH}/src/net/tcp/rttm.cpp
  ${IOSPATH}/src/net/tcp/listener.cpp
  ${IOSPATH}/src/net/tcp/stream.cpp
  ${IOSPATH}/src/net/udp/udp.cpp
  ${IOSPATH}/src/net/udp/socket.cpp
  ${IOSPATH}/src/net/ip4/icmp4.cpp

  ${IOSPATH}/src/net/dns/client.cpp
  ${IOSPATH}/src/net/dns/dns.cpp
  ${IOSPATH}/src/net/dns/query.cpp
  ${IOSPATH}/src/net/dns/record.cpp
  ${IOSPATH}/src/net/dns/response.cpp
  ${IOSPATH}/src/net/dhcp/dh4client.cpp
  ${IOSPATH}/src/net/dhcp/dhcpd.cpp

  ${IOSPATH}/src/net/conntrack.cpp
  ${IOSPATH}/src/net/nat/nat.cpp
  ${IOSPATH}/src/net/nat/napt.cpp

  ${IOSPATH}/src/net/http/basic_client.cpp
  ${IOSPATH}/src/net/http/header.cpp
  ${IOSPATH}/src/net/http/header_fields.cpp
  ${IOSPATH}/src/net/http/message.cpp
  ${IOSPATH}/src/net/http/request.cpp
  ${IOSPATH}/src/net/http/response.cpp
  ${IOSPATH}/src/net/http/status_codes.cpp
  ${IOSPATH}/src/net/http/time.cpp
  ${IOSPATH}/src/net/http/version.cpp
  ${IOSPATH}/src/net/http/mime_types.cpp
  ${IOSPATH}/src/net/http/cookie.cpp
  ${IOSPATH}/src/net/http/client_connection.cpp
  ${IOSPATH}/src/net/http/client.cpp
  ${IOSPATH}/src/net/http/server_connection.cpp
  ${IOSPATH}/src/net/http/server.cpp
  ${IOSPATH}/src/net/http/response_writer.cpp

  ${IOSPATH}/src/net/ws/websocket.cpp

  ${IOSPATH}/src/net/openssl/init.cpp
  ${IOSPATH}/src/net/openssl/client.cpp
  ${IOSPATH}/src/net/openssl/server.cpp
  ${IOSPATH}/src/net/openssl/tls_stream.cpp

)
if (ENABLE_S2N)
  set(NET_SOURCES ${NET_SOURCES}
      ${IOSPATH}/src/net/https/openssl_server.cpp
      ${IOSPATH}/src/net/https/s2n_server.cpp
    )
endif()

set(OS_SOURCES
    ${IOSPATH}/src/version.cpp
    ${IOSPATH}/src/fs/dirent.cpp
    ${IOSPATH}/src/fs/disk.cpp
    ${IOSPATH}/src/fs/fat.cpp
    ${IOSPATH}/src/fs/fat_sync.cpp
    ${IOSPATH}/src/fs/fat_async.cpp
    ${IOSPATH}/src/fs/filesystem.cpp
    ${IOSPATH}/src/fs/mbr.cpp
    ${IOSPATH}/src/fs/path.cpp
    ${IOSPATH}/src/hw/usernet.cpp
    ${IOSPATH}/src/hal/machine.cpp
    ${IOSPATH}/src/kernel/cpuid.cpp
    ${IOSPATH}/src/kernel/events.cpp
    ${IOSPATH}/src/kernel/kernel.cpp
    ${IOSPATH}/src/kernel/os.cpp
    ${IOSPATH}/src/kernel/rng.cpp
    ${IOSPATH}/src/kernel/service_stub.cpp
    ${IOSPATH}/src/kernel/timers.cpp
    ${IOSPATH}/src/util/async.cpp
    ${IOSPATH}/src/util/autoconf.cpp
    ${IOSPATH}/src/util/crc32.cpp
    ${IOSPATH}/src/util/logger.cpp
    ${IOSPATH}/src/util/sha1.cpp
    ${IOSPATH}/src/util/statman.cpp
    ${IOSPATH}/src/util/path_to_regex.cpp
    ${IOSPATH}/src/util/percent_encoding.cpp
    ${IOSPATH}/src/util/uri.cpp
  )
if (CLANG_VERSION_MAJOR VERSION_GREATER 8)
  # remove this on clang < 9.0
  list(APPEND OS_SOURCES ${IOSPATH}/src/util/pmr_default.cpp)
endif()

set(MANA_SOURCES
    mana/src/server.cpp
    mana/src/request.cpp
    mana/src/response.cpp
    mana/src/attributes/cookie_jar.cpp
    mana/src/middleware/butler.cpp
    mana/src/middleware/cookie_parser.cpp
    mana/src/middleware/director.cpp
    mana/src/middleware/parsley.cpp
    mana/src/components/dashboard/dashboard.cpp
  )

set(LIU_SOURCES
    ${IOSPATH}/lib/LiveUpdate/src/elfscan.cpp
    ${IOSPATH}/lib/LiveUpdate/src/hotswap.cpp
    ${IOSPATH}/lib/LiveUpdate/src/partition.cpp
    ${IOSPATH}/lib/LiveUpdate/src/resume.cpp
    ${IOSPATH}/lib/LiveUpdate/src/rollback.cpp
    ${IOSPATH}/lib/LiveUpdate/src/serialize_tcp.cpp
    ${IOSPATH}/lib/LiveUpdate/src/storage.cpp
    ${IOSPATH}/lib/LiveUpdate/src/update.cpp
    ${IOSPATH}/src/util/statman_liu.cpp
  )

set(MICROLB_SOURCES
    microlb/src/autoconf.cpp
    microlb/src/balancer.cpp
    microlb/src/defaults.cpp
    microlb/src/openssl.cpp
  )
if (ENABLE_S2N)
  set(MICROLB_SOURCES ${MICROLB_SOURCES}
      microlb/src/s2n.cpp
    )
endif()

add_library(includeos STATIC ${NET_SOURCES} ${OS_SOURCES} ${MOD_SOURCES})
set_target_properties(includeos PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(includeos PUBLIC
    ${USPCPATH}/repos
    mana/include
  )
set_source_files_properties("${IOSPATH}/src/version.cpp" PROPERTIES COMPILE_DEFINITIONS OS_VERSION="4")

add_library(http_parser STATIC "http-parser/http_parser.c")
set_target_properties(http_parser PROPERTIES LINKER_LANGUAGE C)

add_library(liveupdate STATIC ${LIU_SOURCES})
set_target_properties(liveupdate PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(liveupdate PUBLIC
    ${IOSPATH}/lib/LiveUpdate/include
  )

add_library(microlb STATIC ${MICROLB_SOURCES})
set_target_properties(microlb PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(microlb PUBLIC
    microlb/include
    ${IOSPATH}/lib/LiveUpdate/include
    rapidjson/include
  )

#install(TARGETS includeos   DESTINATION includeos/linux)
#install(TARGETS http_parser DESTINATION includeos/linux)
#install(TARGETS liveupdate microlb DESTINATION includeos/linux)
