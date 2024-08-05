#include "BaseApplication.hpp"

namespace Nexus {
GfxConfiguration config;
BaseApplication g_App(config);
IApplication* g_pApp = &g_App;
}  // namespace Nexus
