#include "../headers/getip.h"

void cli()
{
    std::string ipBase;
    int timeout = 1;
    std::string outputPath;
    int choice = 0;
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Chemin actuel : " << cwd << std::endl;
    } else {
        std::cerr << "Erreur lors de la récupération du chemin actuel" << std::endl;
        return;
    }

    while (choice != 2) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Entrer la base IP (par ex. 192.168.1.): ";
                std::cin >> ipBase;

                std::cout << "Entrez le chemin complet pour enregistrer les résultats (laisser vide pour utiliser le répertoire de l'exécutable) : ";
                std::cin.ignore();
                std::getline(std::cin, outputPath);

                if (outputPath.empty()) {
                    outputPath = std::string(cwd) + "/output.txt";
                    std::cout << "Aucun chemin fourni. Le fichier sera sauvegardé dans : " << outputPath << std::endl;
                }

                ip_sniff(ipBase, outputPath, timeout);
                break;
            case 2:
                std::cout << "Quitter le programme." << std::endl;
                break;
            default:
                std::cout << "Option invalide, veuillez réessayer." << std::endl;
        }
    }
}
