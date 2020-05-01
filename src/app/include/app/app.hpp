#ifndef TIKSRV_APP_APP_HPP
#define TIKSRV_APP_APP_HPP

#include "config/config.hpp"
#include "interop/plugin.hpp"
#include "interop/plugin_loader.hpp"
#include "log/logger.hpp"
#include "net/message.hpp"
#include "net/tcp_client.hpp"
#include "net/tcp_server.hpp"
#include "services/services_manager.hpp"

#include <boost/asio/io_context.hpp>
#include <boost/system/error_code.hpp>

#include <cstdint>
#include <memory>
#include <unordered_map>

namespace ts::app {

class tiksrv_app final : public ts::net::tcp_server_handler,
                         public ts::net::tcp_client_handler {
  public:
    using client_ptr = std::shared_ptr<ts::net::tcp_client>;

    tiksrv_app(const ts::config::config &conf)
        : conf_ {conf},
          io_ {},
          logger_ {"app"},
          server_ {
              io_,
              conf[ts::config::config_key::listen_port].as<std::uint16_t>(),
              conf[ts::config::config_key::liten_backlog].as<std::uint32_t>(),
              *this, *this},
          services_manager_ {conf, io_} {
    }

    void run();

    void on_accept(std::shared_ptr<ts::net::tcp_client> client) final override;
    void on_error(client_ptr                       client,
                  const boost::system::error_code &err) final override;
    void on_close(client_ptr client) final override;
    void on_request(client_ptr client, ts::net::request &&req) final override;

  private:
    void load_plugins();
    void initialize();

  private:
    const ts::config::config &conf_;
    boost::asio::io_context   io_;

    ts::log::logger                logger_;
    ts::net::tcp_server            server_;
    ts::services::services_manager services_manager_;

    std::unordered_map<std::uint32_t, std::shared_ptr<ts::net::tcp_client>>
        clients_;

    std::vector<ts::interop::plugin_wrapper>                       plugins_;
    std::map<std::uint32_t, std::unique_ptr<ts::interop::command>> commands_;
};

} // namespace ts::app

#endif
