//
// Created by Ryder | 33691A on 4/20/2021.
//

#pragma once

#include "pros-grafana-lib/variables/variabledatahandler.h"
#include <vector>

namespace grafanalib
{
    /**
     * @brief The main manager for the PROS-Grafana-LIB project.
     *
     * The GUIManager is in charge of sending all of the tracked data from the brain to the computer.
     *
     */
    class GUIManager
    {
    private:
        std::vector<VariableDataHandler *> variableData;

    public:
        /**
         * @brief Set the Refresh Rate (ms) of the GUI sending data to the computer.
         * 
         * 	A few disclaimers:
	     * - A rate too fast will cause data to be dropped
	     * - Wireless is significantly limited in its speed, requiring a refresh rate of > 100ms. 
         */
        void setRefreshRate(int refreshRate);

        /**
         * @return The refresh rate of the GUI in milliseconds. 
         */
        int getRefreshRate();

        /**
         * Start the task sending data to the WestCore C# GUI named pipe
         */
        void startTask();

        /**
         * Signal the GUI to stop all debugging prints to the console.
         */
        void stopTask();

        /**
         * Adds a new DataHandler to be registered into the GUI.
         * @param dataHandler Either a Variable<T> or VariableGroup<T> object
         */
        void registerDataHandler(VariableDataHandler *dataHandler)
        {
            variableData.push_back(dataHandler);
        }

    private:
        bool alive;

        /**
         * The increment in which data is sent to the computer
         */
        int refreshRate = 20;

        /**
         * Private task that utilizes all of the currently registered tasks and sends them to the WestCore C# GUI named pipe
         */
        void sendData();

        /**
         * @brief The main segment of the GUIManager. 
         * 
         * @param pParams The refreshrate for the task.
         */
        void guiTask(void* pParams);

        /**
         * Sends the needed configuration files for initially setting up charts
         *
         * Data such as y-min, y-max, and title are all sent through this method at the beginning of startTask().
         */
        void sendConfiguration();
    };

}
