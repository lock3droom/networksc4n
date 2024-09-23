#include "../headers/getip.h";

void cli()
{
    std::string ipBase;
    int timeout = 1;
    std::string outputPath;
    int choice = 0;

    while (choice != 2) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "entrer la base IP (par ex. 192.168.1.): ";
                std::cin >> ipBase;
                std::cout << "entrez le path pour save l'output (par ex. /home/user/output.txt): ";
                std::cin >> outputPath;
                ipSniff(ipBase, outputPath, timeout);
                break;
            case 2:
                std::cout << "leave" << std::endl;
                break;
            default:
                std::cout << "option invalid" << std::endl;
        }
    }
}