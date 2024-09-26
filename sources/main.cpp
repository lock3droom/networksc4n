#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;
bool ping(const string& ip)
{
    string command = "ping -c 1 -W 1 " + ip + " > /dev/null 2>&1"; // UNIX
    return system(command.c_str()) == 0;
}
void get_network_info()
{
    cout << "=======================" << endl;
    cout << "gathering network information..." << endl;
    system("ip addr");
    system("ip route");
    cout << "=======================" << endl;
}
void scan_range(const string& base_ip, int start, int end, ofstream& log_file, ofstream& active_ips_file, vector<string>& active_ips)
{
    for (int i = start; i <= end; i++) {
        string ip = base_ip + to_string(i);
        cout << "scanning IP: " << ip << "..." << endl;       
        if (ping(ip)) {
            cout << "\033[32m[+] active IP found: " << ip << "\033[0m" << endl;
            log_file << "[ACTIVE] " << ip << endl;
            active_ips.push_back(ip);
            active_ips_file << ip << endl;
        } else {
            cout << "\033[31m[-] no response from: " << ip << "\033[0m" << endl;
            log_file << "[INACTIVE] " << ip << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void scan_ips_from_file(const string& file_path, const string& output_path)
{
    ifstream ip_file(file_path);
    ofstream log_file(output_path + "/active_ips_from_file.txt");
    ofstream active_ips_file(output_path + "/active_ips_from_file_only.txt");
    vector<string> active_ips;
    string ip;
    if (!ip_file) {
        cerr << "Error: Unable to open file " << file_path << endl;
        return;
    }
    cout << "=======================" << endl;
    cout << "scanning IPs from file: " << file_path << endl;
    cout << "=======================" << endl;
    while (getline(ip_file, ip)) {
        cout << "scanning IP: " << ip << "..." << endl;
        if (ping(ip)) {
            cout << "\033[32m[+] active IP found: " << ip << "\033[0m" << endl;
            log_file << "[ACTIVE] " << ip << endl;
            active_ips.push_back(ip);
            active_ips_file << ip << endl;
        } else {
            cout << "\033[31m[-] no response from: " << ip << "\033[0m" << endl;
            log_file << "[INACTIVE] " << ip << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    log_file.close();
    active_ips_file.close();
    ip_file.close();
    cout << "=======================" << endl;
    cout << "scan completed. output saved in '" << output_path << "'." << endl;
    cout << "=======================" << endl;
    cout << "List of active IPs found:" << endl;
    for (const string& active_ip : active_ips) {
        cout << "\033[32m" << active_ip << "\033[0m" << endl;
    }
}
void scan_network(const string& base_ip, int range_start, int range_end, const string& output_path)
{
    ofstream log_file(output_path + "/active_ips.txt");
    ofstream active_ips_file(output_path + "/active_ips_only.txt");
    vector<string> active_ips;
    cout << "=======================" << endl;
    cout << "starting network scan..." << endl;
    cout << "IP Range: " << base_ip << range_start << " - " << base_ip << range_end << endl;
    cout << "=======================" << endl;
    log_file << "IP Range scanned: " << base_ip << range_start << " - " << base_ip << range_end << endl;
    scan_range(base_ip, range_start, range_end, log_file, active_ips_file, active_ips);
    log_file.close();
    active_ips_file.close();
    cout << "=======================" << endl;
    cout << "scan completed. output saved in '" << output_path << "'." << endl;
    cout << "=======================" << endl;
    cout << "List of active IPs found:" << endl;
    for (const string& ip : active_ips) {
        cout << "\033[32m" << ip << "\033[0m" << endl;
    }
}
void show_menu()
{
    cout << "========== Network Scanner CLI ==========" << endl;
    cout << "1. Scan network IP range" << endl;
    cout << "2. Scan IPs from file" << endl;
    cout << "3. Exit" << endl;
    cout << "=========================================" << endl;
}
void cli()
{
    int choice;
    string base_ip, file_path, output_path;
    int range_start, range_end;
    while (true) {
        show_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                get_network_info();
                cout << "Enter base IP (e.g., 192.168.1.): ";
                cin >> base_ip;
                cout << "Enter range start (e.g., 1): ";
                cin >> range_start;
                cout << "Enter range end (e.g., 254): ";
                cin >> range_end;
                cout << "Enter output file path (on Docker: /usr/src/app/output): ";
                cin >> output_path;
                scan_network(base_ip, range_start, range_end, output_path);
                break;
            case 2:
                cout << "Enter the path of the IP file (e.g., /path/to/ips.txt): ";
                cin >> file_path;
                cout << "Enter output file path (on Docker: /usr/src/app/output): ";
                cin >> output_path;
                scan_ips_from_file(file_path, output_path);
                break;
            case 3:
                cout << "Exiting..." << endl;
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }
}
int main()
{
    cli();
    return 0;
}
