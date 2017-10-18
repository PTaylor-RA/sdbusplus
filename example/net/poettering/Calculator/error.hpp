#pragma once

#include <sdbusplus/exception.hpp>

namespace sdbusplus
{
namespace net
{
namespace poettering
{
namespace Calculator
{
namespace Error
{

struct DivisionByZero final : public sdbusplus::exception_t
{
    static constexpr auto errName = "net.poettering.Calculator.Error.DivisionByZero";
    static constexpr auto errDesc =
            "An attempt to divide by zero was attempted.";
    static constexpr auto errWhat =
            "net.poettering.Calculator.Error.DivisionByZero: An attempt to divide by zero was attempted.";

    const char* name() const noexcept override;
    const char* description() const noexcept override;
    const char* what() const noexcept override;
};

} // namespace Error
} // namespace Calculator
} // namespace poettering
} // namespace net
} // namespace sdbusplus

