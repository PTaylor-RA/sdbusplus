#include <algorithm>
#include <sdbusplus/server.hpp>
#include <sdbusplus/exception.hpp>
#include <net/poettering/Calculator/server.hpp>


#include <net/poettering/Calculator/error.hpp>


namespace sdbusplus
{
namespace net
{
namespace poettering
{
namespace server
{

Calculator::Calculator(bus::bus& bus, const char* path)
        : _net_poettering_Calculator_interface(
                bus, path, _interface, _vtable, this)
{
}

Calculator::Calculator(bus::bus& bus, const char* path,
                           const std::map<std::string, PropertiesVariant>& vals)
        : Calculator(bus, path)
{
    for (const auto& v : vals)
    {
        setPropertyByName(v.first, v.second);
    }
}


int Calculator::_callback_Multiply(
        sd_bus_message* msg, void* context, sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(msg);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        int64_t x{};
    int64_t y{};

        m.read(x, y);

        auto o = static_cast<Calculator*>(context);
        auto r =         o->multiply(x, y);

        auto reply = m.new_method_return();
        reply.append(convertForMessage(std::move(r)));

        reply.method_return();
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Calculator
{
static const auto _param_Multiply =
        utility::tuple_to_array(message::types::type_id<
                int64_t, int64_t>());
static const auto _return_Multiply =
        utility::tuple_to_array(message::types::type_id<
                int64_t>());
}
}

int Calculator::_callback_Divide(
        sd_bus_message* msg, void* context, sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(msg);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        int64_t x{};
    int64_t y{};

        m.read(x, y);

        auto o = static_cast<Calculator*>(context);
        auto r =         o->divide(x, y);

        auto reply = m.new_method_return();
        reply.append(convertForMessage(std::move(r)));

        reply.method_return();
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }
    catch(sdbusplus::net::poettering::Calculator::Error::DivisionByZero& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Calculator
{
static const auto _param_Divide =
        utility::tuple_to_array(message::types::type_id<
                int64_t, int64_t>());
static const auto _return_Divide =
        utility::tuple_to_array(message::types::type_id<
                int64_t>());
}
}

int Calculator::_callback_Clear(
        sd_bus_message* msg, void* context, sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(msg);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif


        auto o = static_cast<Calculator*>(context);
        o->clear();

        auto reply = m.new_method_return();
        // No data to append on reply.

        reply.method_return();
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Calculator
{
static const auto _param_Clear =
        utility::tuple_to_array(std::make_tuple('\0'));
static const auto _return_Clear =
        utility::tuple_to_array(std::make_tuple('\0'));
}
}


void Calculator::cleared(
            int64_t unnamed)
{
    using sdbusplus::server::binding::details::convertForMessage;

    auto& i = _net_poettering_Calculator_interface;
    auto m = i.new_signal("Cleared");

    m.append(convertForMessage(unnamed));
    m.signal_send();
}

namespace details
{
namespace Calculator
{
static const auto _signal_Cleared =
        utility::tuple_to_array(message::types::type_id<
                int64_t>());
}
}

auto Calculator::lastResult() const ->
        int64_t
{
    return _lastResult;
}

int Calculator::_callback_get_LastResult(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(reply);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Calculator*>(context);
        m.append(convertForMessage(o->lastResult()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Calculator::lastResult(int64_t value) ->
        int64_t
{
    if (_lastResult != value)
    {
        _lastResult = value;
        _net_poettering_Calculator_interface.property_changed("LastResult");
    }

    return _lastResult;
}

int Calculator::_callback_set_LastResult(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    try
    {
        auto m = message::message(value);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Calculator*>(context);

        int64_t v{};
        m.read(v);
        o->lastResult(v);
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Calculator
{
static const auto _property_LastResult =
    utility::tuple_to_array(message::types::type_id<
            int64_t>());
}
}
auto Calculator::status() const ->
        State
{
    return _status;
}

int Calculator::_callback_get_Status(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* reply, void* context,
        sd_bus_error* error)
{
    using sdbusplus::server::binding::details::convertForMessage;

    try
    {
        auto m = message::message(reply);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Calculator*>(context);
        m.append(convertForMessage(o->status()));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

auto Calculator::status(State value) ->
        State
{
    if (_status != value)
    {
        _status = value;
        _net_poettering_Calculator_interface.property_changed("Status");
    }

    return _status;
}

int Calculator::_callback_set_Status(
        sd_bus* bus, const char* path, const char* interface,
        const char* property, sd_bus_message* value, void* context,
        sd_bus_error* error)
{
    try
    {
        auto m = message::message(value);
#if 0
        {
            auto tbus = m.get_bus();
            sdbusplus::server::transaction::Transaction t(tbus, m);
            sdbusplus::server::transaction::set_id
                (std::hash<sdbusplus::server::transaction::Transaction>{}(t));
        }
#endif

        auto o = static_cast<Calculator*>(context);

        std::string v{};
        m.read(v);
        o->status(convertStateFromString(v));
    }
    catch(sdbusplus::internal_exception_t& e)
    {
        sd_bus_error_set_const(error, e.name(), e.description());
        return -EINVAL;
    }

    return true;
}

namespace details
{
namespace Calculator
{
static const auto _property_Status =
    utility::tuple_to_array(message::types::type_id<
            std::string>());
}
}

void Calculator::setPropertyByName(const std::string& name,
                                     const PropertiesVariant& val)
{
    if (name == "LastResult")
    {
        auto& v = message::variant_ns::get<int64_t>(val);
        lastResult(v);
        return;
    }
    if (name == "Status")
    {
        auto& v = message::variant_ns::get<State>(val);
        status(v);
        return;
    }
}

auto Calculator::getPropertyByName(const std::string& name) ->
        PropertiesVariant
{
    if (name == "LastResult")
    {
        return lastResult();
    }
    if (name == "Status")
    {
        return status();
    }

    return PropertiesVariant();
}


namespace
{
/** String to enum mapping for Calculator::State */
static const std::tuple<const char*, Calculator::State> mappingCalculatorState[] =
        {
            std::make_tuple( "net.poettering.Calculator.State.Success",                 Calculator::State::Success ),
            std::make_tuple( "net.poettering.Calculator.State.Error",                 Calculator::State::Error ),
        };

} // anonymous namespace

auto Calculator::convertStateFromString(const std::string& s) ->
        State
{
    auto i = std::find_if(
            std::begin(mappingCalculatorState),
            std::end(mappingCalculatorState),
            [&s](auto& e){ return 0 == strcmp(s.c_str(), std::get<0>(e)); } );
    if (std::end(mappingCalculatorState) == i)
    {
        throw sdbusplus::exception::InvalidEnumString();
    }
    else
    {
        return std::get<1>(*i);
    }
}

std::string convertForMessage(Calculator::State v)
{
    auto i = std::find_if(
            std::begin(mappingCalculatorState),
            std::end(mappingCalculatorState),
            [v](auto& e){ return v == std::get<1>(e); });
    return std::get<0>(*i);
}

const vtable::vtable_t Calculator::_vtable[] = {
    vtable::start(),

    vtable::method("Multiply",
                   details::Calculator::_param_Multiply
                        .data(),
                   details::Calculator::_return_Multiply
                        .data(),
                   _callback_Multiply),

    vtable::method("Divide",
                   details::Calculator::_param_Divide
                        .data(),
                   details::Calculator::_return_Divide
                        .data(),
                   _callback_Divide),

    vtable::method("Clear",
                   details::Calculator::_param_Clear
                        .data(),
                   details::Calculator::_return_Clear
                        .data(),
                   _callback_Clear),

    vtable::signal("Cleared",
                   details::Calculator::_signal_Cleared
                        .data()),
    vtable::property("LastResult",
                     details::Calculator::_property_LastResult
                        .data(),
                     _callback_get_LastResult,
                     _callback_set_LastResult,
                     vtable::property_::emits_change),
    vtable::property("Status",
                     details::Calculator::_property_Status
                        .data(),
                     _callback_get_Status,
                     _callback_set_Status,
                     vtable::property_::emits_change),
    vtable::end()
};

} // namespace server
} // namespace poettering
} // namespace net
} // namespace sdbusplus

