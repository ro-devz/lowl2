//============================================================================
// Name        : Final-Project.cpp
// Author      : Romane Devezeaux de Lavergne
// Version     :
// Copyright   : Your copyright notice
// Description : Final Project
//============================================================================

#include "Simulation.hpp"

// int main() {
//     Simulation simulation;
//     simulation.run();
//     return 0;
// }

#include "SimulationServer.hpp"
#include "SimulationClient.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        Simulation simulation;
        simulation.run();
        return 0;
    }
    
    else if (argc != 2 && argc != 3) {
        std::cout << "Usage: " << argv[0] << " [server|client localhost]" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    
    if (mode == "server") {
        SimulationServer server;
        if (!server.start()) {
            std::cout << "Failed to start server" << std::endl;
            return 1;
        }
        server.run();
    }
    else if (mode == "client") {
        SimulationClient client;
        std::string address;
        address = argv[2];
        
        if (!client.connect(address)) {
            std::cout << "Failed to connect to server" << std::endl;
            return 1;
        }
        client.run();
    }
    else {
        std::cout << "Invalid mode. Use 'server' or 'client'" << std::endl;
        return 1;
    }
    
    return 0;
}