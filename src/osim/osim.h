#pragma once

#include <string>
#include <utility>

namespace osim
{
    class InitConfiguration final {
    public:
        virtual ~InitConfiguration() noexcept = default;

        void log_warning(std::string content) { impl_log_warning(std::move(content)); }
        void log_info(std::string content) { impl_log_info(std::move(content)); }
    private:
        virtual void impl_log_warning(std::string);  // defaults to writing to `std::cerr`
        virtual void impl_log_info(std::string);     // defaults to writing to `std::cerr`
    };

    void init();
    void init(InitConfiguration&);
}

