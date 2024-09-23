#include "../headers/getip.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

void ip_sniff(const std::string& ipBase, const std::string& output_path, int timeout)
{
    std::ofstream output_file(output_path);

    if (!output_file) {
        std::cerr << "cannot open file " << output_path << std::endl;
        return;
    }

    for (int i = 1; i < 255; i++) {
        std::string ip = ipBase + std::to_string(i);
        std::string command = "ping -c 1 -W " + std::to_string(timeout) + " " + ip + " > /dev/null";
        int result = system(command.c_str());

        if (result == 0) {
            std::cout << GREEN << "appareil détecté : " << ip << RESET << std::endl;
            output_file << ip << std::endl;
        } else {
            std::cout << RED << "appareil non détecte : " << ip << RESET << std::endl;
        }
    }

    output_file.close();
    std::cout << GREEN << "balayage terminer avec succées, le resultat se trouve dans : " << output_path << RESET << std::endl;
}