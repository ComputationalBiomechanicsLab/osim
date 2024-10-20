#pragma once

#include <string>
#include <utility>

namespace osim
{
    // Runtime configuration that can be given to `osim::init` to change/monitor
    // its behavior.
    class InitConfiguration final {
    public:
        virtual ~InitConfiguration() noexcept = default;

        // Called when `osim::init` wants to write `content` as a warning message.
        void log_warning(std::string content) { impl_log_warning(std::move(content)); }

        // Called when `osim::init` wants to write `content` as an info message.
        void log_info(std::string content) { impl_log_info(std::move(content)); }

    private:

        // Implementors can override this to provide custom warning message logging behavior.
        //
        // By default, it writes warning messages to `std::cerr`.
        virtual void impl_log_warning(std::string);

        // Implementors can override this to provide custom info message logging behavior.
        //
        // By default, it writes info messages to `std::cerr`.
        virtual void impl_log_info(std::string);
    };

    // Globally initializes the osim (OpenSim + extensions) API with a default `InitConfiguration`.
    //
    // This should be called by the application exactly once before using any `osim::`,
    // `SimTK::`, or `OpenSim::`-prefixed API.
    void init();

    // Globally initializes the osim (OpenSim + extensions) API with the given `InitConfiguration`.
    //
    // This should be called by the application exactly once before using any `osim::`,
    // `SimTK::`, or `OpenSim::`-prefixed API.
    void init(InitConfiguration&);
}
