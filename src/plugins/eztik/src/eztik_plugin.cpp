#include "eztik/eztik_plugin.hpp"

#include <functional>
#include <memory>

namespace eztik {

void eztik_plugin::initialize(ts::services::services_manager &svcs) noexcept {
}

void eztik_plugin::export_commands(export_func export_cb) const noexcept {
}

} // namespace eztik