#include "./headers/sniff.h"

using namespace std;

bool ping(const string& ip)
{
    string command = "ping -c 1 -W 1 " + ip + " > /dev/null 2>&1";//UNIX
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
void scan_range(const string& base_ip, int start, int end, ofstream& log_file)
{
    for (int i = start; i <= end; i++) {
        string ip = base_ip + to_string(i);
        cout << "scanning IP: " << ip << "..." << endl;
        if (ping(ip)) {
            cout << "[+] active IP found: " << ip << endl;
            log_file << "[ACTIVE] " << ip << endl;
        } else {
            cout << "[-] no response from: " << ip << endl;
            log_file << "[INACTIVE] " << ip << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void scan_network(const string& base_ip, int range_start, int range_end)
{
    ofstream log_file("active_ips.txt");
    cout << "=======================" << endl;
    cout << "starting network scan..." << endl;
    cout << "IP Range: " << base_ip << range_start << " - " << base_ip << range_end << endl;
    cout << "=======================" << endl;
    log_file << "IP Range scanned: " << base_ip << range_start << " - " << base_ip << range_end << endl;
    scan_range(base_ip, range_start, range_end, log_file);
    log_file.close();
    cout << "=======================" << endl;
    cout << "scan completed. output saved in 'active_ips.txt'." << endl;
    cout << "=======================" << endl;
}

int main()
{
    string base_ip;
    int range_start, range_end;
    get_network_info();
    cout << "enter base IP (e.g., 192.168.1.): ";
    cin >> base_ip;
    cout << "enter range start (e.g., 1): ";
    cin >> range_start;
    cout << "enter range end (e.g., 254): ";
    cin >> range_end;
    scan_network(base_ip, range_start, range_end);
    return 0;
}
