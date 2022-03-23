//
// Created by Ryder | 33691A on 7/9/2021.
//

#include <map>
#include <functional>
#include <string>

#pragma once

namespace grafanalib
{

    /**
     * Allows the user to track properties of an object and register them in the GUIManager
     * @tparam T The type of object the Variable will be tracking
     */
    template <typename T>
    class Variable : public VariableDataHandler
    {
    private:
        /**
         * Stores all of the functions the Variable is tracking
         */
        std::map<std::string, std::function<double(T)>> getters;

        /**
         * The name of the Variable as specified by the user. In the SQLite database this name is used to differentiate
         * variables.
         */
        std::string name;

        /**
         * The actual object passed in by the user
         */
        T value;

    public:
        /**
         * @summary
         * Creates a new Variable from an existing object and assigns it a given name.
         *
         * @tparam TF The type of object being tracked
         * @param name The name of the Variable as shown in the GUI and database
         * @param value The object to be tracked
         */
        template <typename TF>
        Variable(std::string name, TF &&value) : value(std::forward<TF>(value)), name(std::move(name)) {}

        /**
         * @summary
         * Adds a getter to retrieve a function from the object type's list of methods. In the database, the format of the
         * column name will be "{name} {getter_var_name}".
         * @param varName A name you want to assign to the getter
         * @param func The function to be tracked
         * @example
         * For tracking the temperature of a motor variable named "Test Motor":
         * @code
         * add_getter("Temperature", &Motor::get_temperature);
         * @endcode
         * In the database, the column name will show up as:
         * @code
         * Test Motor Temperature
         * @endcode
         */
        void add_getter(const std::string &varName, std::function<double(T)> func)
        {
            getters[varName] = func;
        }

        /**
         * @summary
         * Retrieves a map of all of the getters and their current respective values. Unless you know what you're doing,
         * this should only be used internally.
         * @return An std::map<std::string, double> containing the current getter data
         */
        std::map<std::string, double> get_data() override
        {
            std::map<std::string, double> toReturn;

            // Loop over all of the getters and append their current data to the map
            for (const auto &kv : getters)
            {
                toReturn[name + " " + kv.first] = kv.second(value);
            }

            return toReturn;
        }
    };

}