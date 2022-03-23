//
// Created by Ryder | 33691A on 7/9/2021.
//

#pragma once

#include <map>
#include <string>

namespace grafanalib
{

    /**
     * Used to share common methods between variable data headers.
     * @see variable
     * @see variablegroup
     */
    class VariableDataHandler
    {
    public:
        /**
         * @summary
         * Retrieves a map of all of the getters and their current respective values. Unless you know what you're doing,
         * this should only be used internally.
         * @return An std::map<std::string, double> containing the current getter data
         */
        virtual std::map<std::string, double> get_data() = 0;
    };

}