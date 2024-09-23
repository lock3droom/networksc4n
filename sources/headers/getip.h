#ifndef GETIP_H
#define GETIP_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";

void ip_sniff(const std::string& ipBase, const std::string& output_path, int timeout);
void showMenu();
void cli();

#endif