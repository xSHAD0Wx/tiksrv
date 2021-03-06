#ifndef TIKSRV_LOG_CORE_HPP
#define TIKSRV_LOG_CORE_HPP

#include "spdlog/sinks/dist_sink.h"
#include "spdlog/sinks/sink.h"

#include <memory>
#include <vector>

namespace ts::log {

enum class log_level : int {
    trace    = SPDLOG_LEVEL_TRACE,
    debug    = SPDLOG_LEVEL_DEBUG,
    info     = SPDLOG_LEVEL_INFO,
    warn     = SPDLOG_LEVEL_WARN,
    err      = SPDLOG_LEVEL_ERROR,
    critical = SPDLOG_LEVEL_CRITICAL,
    off      = SPDLOG_LEVEL_OFF,
};

void add_sink(spdlog::sink_ptr sink);

template <typename T, typename... TArgs>
inline void add_sink(log_level level, TArgs... args) {
    auto ptr = std::make_shared<T>(args...);
    ptr->set_level(static_cast<spdlog::level::level_enum>(level));
    add_sink(std::move(ptr));
}

auto main_sink() -> std::shared_ptr<spdlog::sinks::dist_sink_st> &;

auto global_level() -> log_level;
void global_level(log_level level);

} // namespace ts::log

#endif
