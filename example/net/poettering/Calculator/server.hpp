#pragma once
#include <tuple>
#include <systemd/sd-bus.h>
#include <sdbusplus/server.hpp>

namespace sdbusplus
{
namespace net
{
namespace poettering
{
namespace server
{

class Calculator
{
    public:
        /* Define all of the basic class operations:
         *     Not allowed:
         *         - Default constructor to avoid nullptrs.
         *         - Copy operations due to internal unique_ptr.
         *         - Move operations due to 'this' being registered as the
         *           'context' with sdbus.
         *     Allowed:
         *         - Destructor.
         */
        Calculator() = delete;
        Calculator(const Calculator&) = delete;
        Calculator& operator=(const Calculator&) = delete;
        Calculator(Calculator&&) = delete;
        Calculator& operator=(Calculator&&) = delete;
        virtual ~Calculator() = default;

        /** @brief Constructor to put object onto bus at a dbus path.
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         */
        Calculator(bus::bus& bus, const char* path);

        enum class State
        {
            Success,
            Error,
        };

        using PropertiesVariant = sdbusplus::message::variant<
                State,
                int64_t>;

        /** @brief Constructor to initialize the object from a map of
         *         properties.
         *
         *  @param[in] bus - Bus to attach to.
         *  @param[in] path - Path to attach at.
         *  @param[in] vals - Map of property name to value for initalization.
         */
        Calculator(bus::bus& bus, const char* path,
                     const std::map<std::string, PropertiesVariant>& vals);


        /** @brief Implementation for Multiply
         *  Multiplies two integers 'x' and 'y' and returns the result.
         *
         *  @param[in] x - The first integer to multiply.
         *  @param[in] y - The second integer to multiply.
         *
         *  @return z[int64_t] - The result of (x*y).
         */
        virtual int64_t multiply(
            int64_t x,
            int64_t y) = 0;

        /** @brief Implementation for Divide
         *  Divides two integers 'x' and 'y' and returns the result.
         *
         *  @param[in] x - The first integer to divide.
         *  @param[in] y - The second integer to divide.
         *
         *  @return z[int64_t] - The result of (x/y).
         */
        virtual int64_t divide(
            int64_t x,
            int64_t y) = 0;

        /** @brief Implementation for Clear
         *  Reset the LastResult property to zero.
         */
        virtual void clear(
            ) = 0;


        /** @brief Send signal 'Cleared'
         *
         *  Signal indicating the LastReset property has been set to zero by the 'Clear' method.
         *
         *  @param[in] unnamed - Value of LastReset prior to Clear.
         */
        void cleared(
            int64_t unnamed);

        /** Get value of LastResult */
        virtual int64_t lastResult() const;
        /** Set value of LastResult */
        virtual int64_t lastResult(int64_t value);
        /** Get value of Status */
        virtual State status() const;
        /** Set value of Status */
        virtual State status(State value);

        /** @brief Sets a property by name.
         *  @param[in] name - A string representation of the property name.
         *  @param[in] val - A variant containing the value to set.
         */
        void setPropertyByName(const std::string& name,
                               const PropertiesVariant& val);

        /** @brief Gets a property by name.
         *  @param[in] name - A string representation of the property name.
         *  @return - A variant containing the value of the property.
         */
        PropertiesVariant getPropertyByName(const std::string& name);

    /** @brief Convert a string to an appropriate enum value.
     *  @param[in] s - The string to convert in the form of
     *                 "net.poettering.Calculator.<value name>"
     *  @return - The enum value.
     */
    static State convertStateFromString(const std::string& s);

    private:

        /** @brief sd-bus callback for Multiply
         */
        static int _callback_Multiply(
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for Divide
         */
        static int _callback_Divide(
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for Clear
         */
        static int _callback_Clear(
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'LastResult' */
        static int _callback_get_LastResult(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'LastResult' */
        static int _callback_set_LastResult(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);

        /** @brief sd-bus callback for get-property 'Status' */
        static int _callback_get_Status(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);
        /** @brief sd-bus callback for set-property 'Status' */
        static int _callback_set_Status(
            sd_bus*, const char*, const char*, const char*,
            sd_bus_message*, void*, sd_bus_error*);


        static constexpr auto _interface = "net.poettering.Calculator";
        static const vtable::vtable_t _vtable[];
        sdbusplus::server::interface::interface
                _net_poettering_Calculator_interface;

        int64_t _lastResult{};
        State _status = State::Success;

};

/* Specialization of sdbusplus::server::bindings::details::convertForMessage
 * for enum-type Calculator::State.
 *
 * This converts from the enum to a constant c-string representing the enum.
 *
 * @param[in] e - Enum value to convert.
 * @return C-string representing the name for the enum value.
 */
std::string convertForMessage(Calculator::State e);

} // namespace server
} // namespace poettering
} // namespace net
} // namespace sdbusplus

