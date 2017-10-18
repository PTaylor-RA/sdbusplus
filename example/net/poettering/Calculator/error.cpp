#include <net/poettering/Calculator/error.hpp>

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
const char* DivisionByZero::name() const noexcept
{
    return errName;
}
const char* DivisionByZero::description() const noexcept
{
    return errDesc;
}
const char* DivisionByZero::what() const noexcept
{
    return errWhat;
}

} // namespace Error
} // namespace Calculator
} // namespace poettering
} // namespace net
} // namespace sdbusplus

