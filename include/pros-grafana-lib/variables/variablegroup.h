//
// Created by Ryder | 33691A on 7/9/2021.
//

namespace grafanalib
{

    /**
     * Represents a collection of Variable<T>s to easily add multiple getters at once.
     *
     * A practical example of this can be the use of recording statistics of a chassis. More often than not a chassis
     * consists of four or more motors, making tracking each one an unnecessary hassle. With a VariableGroup, you only need
     * one line to track ALL variables within the group, whether it be something like motor voltage or temperature. More
     * examples of this can be seen in the template repository as well as the documentation below.
     *
     * @tparam T The object type all Variable<T> objects share
     */
    template <typename T>
    class VariableGroup : public VariableDataHandler
    {
    private:
        /**
         * Stores all of the Variable<T> elements of the VariableGroup<T>
         */
        std::vector<Variable<T>> variables;

    public:
        /**
         * @summary
         *      Initializes a VariableGroup given an initial list of variables.
         * @example
         *      @code
         *          VariableGroup<pros::Motor> varGroup({var1, var2, var3, var4});
         *      @endcode
         *      where ``var1, var2, var3, var4`` are all previously initialized Variable<T> objects.
         * @param variables The initial list of variables to be used in the VariableGroup.
         */
        VariableGroup(const std::initializer_list<Variable<T>> &variables) : variables(variables) {}

        /**
         * Adds a getter to retrieve a function from the object type's list of methods. Because this is a VariableGroup<T>,
         * the getter will be added to all Variable<T> objects given in the initial std::initializer_list. In the database,
         * the format of each Variable<T>'s column name will be "{name} {getter_var_name}".
         *
         * For tracking the temperature of all motors within a VariableGroup<pros::Motor>:
         *
         * @code {.cpp}
         * add_getter("Temperature", &Motor::get_temperature);
         * @endcode
         *
         *
         * @param varName A name you want to assign to the getter
         * @param func The function to be tracked
         */
        void add_getter(const std::string &varName, std::function<double(T &&)> func)
        {
            // Add the getter to all Variable<T> children
            for (Variable<T> &variable : variables)
            {
                variable.add_getter(varName, func);
            }
        }

        /**
         * Retrieves a map of all of the getters and their current respective values. Unless you know what you're doing,
         * this should only be used internally.
         * @return An std::map<std::string, double> containing the current getter data
         */
        std::map<std::string, double> get_data() override
        {
            std::map<std::string, double> toReturn;

            // Loop over each Variable<T> and retrieve its data
            for (Variable<T> &variable : variables)
            {
                for (const auto &kv : variable.get_data())
                {
                    toReturn[kv.first] = kv.second;
                }
            }

            return toReturn;
        }
    };

}