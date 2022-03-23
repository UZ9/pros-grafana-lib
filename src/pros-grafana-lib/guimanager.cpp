//
// Created by Ryder | 33691A on 4/20/2021.
//

#include <iostream>
#include "pros-grafana-lib/guimanager.h"
#include "pros-grafana-lib/lib/json.hpp"
#include "pros/rtos.hpp"

namespace grafanalib
{
    void GUIManager::setRefreshRate(int refreshRate) {
        this->refreshRate = refreshRate;
    }

    int GUIManager::getRefreshRate() {
        return refreshRate;
    }

    void GUIManager::startTask()
    {
        pros::Task{[=]
        {
            sendConfiguration();

            while (true)
            {
                sendData();

                pros::delay(getRefreshRate()); // TODO: This needs to be changed to the refresh rate variable
            }
        }};
    }

    void GUIManager::sendConfiguration()
    {
        nlohmann::json configJson;

        // Send initial configuration data
        for (auto &var : variableData)
        {
            for (auto &pair : var->get_data())
            {
                configJson[pair.first] = pair.second;
            }
        }

        std::string jsonString = configJson.dump();

        jsonString += "GUI_DATA_CONF_3434_END";

        // To avoid the buffer size cutting off content, we send it in chunks
        for (std::string::size_type i = 0; i < jsonString.length(); i += 1000)
        {
            std::cout << "GUI_DATA_CONF_8378"
                      << "|" << jsonString.substr(i, 1000) << std::endl;
        }
    }

    void GUIManager::sendData()
    {
        nlohmann::json dataJson;

        // Add all of the chart data to the json
        for (auto &var : variableData)
        {
            for (auto &pair : var->get_data())
            {
                dataJson[pair.first] = pair.second;
            }
        }

        // Print out the JSON to be picked up by the C# parser
        // GUI_DATA_8378 is the DATA_HEADER being sent (more info on the C# side)
        std::cout << "GUI_DATA_8378"
                  << "|" << dataJson << std::endl;
    }

    void GUIManager::stopTask()
    {
        alive = false;
    }

}