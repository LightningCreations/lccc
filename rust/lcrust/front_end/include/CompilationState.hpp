#ifndef LCCC_LCRUST_FRONTEND_UNSTABLE_HPP_2021_01_07_19_50_11
#define LCCC_LCRUST_FRONTEND_UNSTABLE_HPP_2021_01_07_19_50_11

#include <set>
#include <stack>
#include <string>

namespace lccc::lcrust
{
    ///
    /// A type that represents unstable features enabled in a rust crate.
    struct Unstable
    {
    private:
        std::set<std::string> active_features;
        std::stack<std::set<std::string>> stacked_features;

    public:
        ///
        /// Checks if a particular feature is enabled
        bool is_feature_enabled(const std::string &name) const noexcept;
        ///
        /// Enables a named feature.
        void enable_feature(std::string name);

        ///
        /// Pushes the current feature state and resets active feature list
        void push_feature_state();
        ///
        /// Pops the current feature state that is previous pushed, or resets it if
        ///  no feature state is currently stacked.
        void pop_feature_state();
    };

    enum class WarningLevel
    {
        Allow = 0,
        Warn = 1,
        Deny = 2,
        Forbid = 3,
    };

    class Warnings
    {
    private:
    };

} // namespace lccc::lcrust

#endif /*LCCC_LCRUST_FRONTEND_UNSTABLE_HPP_2021_01_07_19_50_11*/