#include <cstdio>

#include "BaseApplication.hpp"

namespace Nexus {
extern IApplication *g_pApp;
}  // namespace Nexus

int main() {
    int ret;

    if ((ret = Nexus::g_pApp->Initialize()) != 0) {
        printf("App Initialize failed, will exit now.");
        return ret;
    }

    while (!Nexus::g_pApp->IsQuit()) {
        Nexus::g_pApp->Tick();
    }

    Nexus::g_pApp->Finalize();

    return 0;
}
