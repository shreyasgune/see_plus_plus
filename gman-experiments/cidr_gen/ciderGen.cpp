#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <cmath>
#include <cassert>

// Function to convert IP address to binary representation
std::string ip_to_binary(const std::string& ip) {
    std::stringstream ss(ip);
    std::string token;
    std::vector<std::string> octets;

    while (std::getline(ss, token, '.')) {
        int octet = std::stoi(token);
        assert(octet >= 0 && octet <= 255); // Ensure octet is in valid range
        octets.push_back(std::bitset<8>(octet).to_string());
    }

    return octets[0] + octets[1] + octets[2] + octets[3];
}

// Function to convert binary IP address to dotted-decimal notation
std::string binary_to_ip(const std::string& binary_ip) {
    std::string ip;
    for (int i = 0; i < 32; i += 8) {
        std::string octet = binary_ip.substr(i, 8);
        int decimal = std::stoi(octet, nullptr, 2);
        ip += std::to_string(decimal);
        if (i < 24) {
            ip += ".";
        }
    }
    return ip;
}


// Function to calculate total number of hosts
uint64_t calculate_total_hosts(int cidr_prefix) {
    return static_cast<uint64_t>(pow(2, 32 - cidr_prefix));
}


// Function to calculate CIDR prefix length
int calculate_cidr_prefix(const std::string& ip1, const std::string& ip2) {
    int common_bits = 0;
    int octet_idx = 0;
    int cidr_prefix = 0;

    std::string ip1_bin = ip_to_binary(ip1);
    std::string ip2_bin = ip_to_binary(ip2);

    // Loop through each bit and count common bits
    while (octet_idx < 32) {
        if (ip1_bin[octet_idx] == ip2_bin[octet_idx]) {
            common_bits++;
        } else {
            break;
        }
        octet_idx++;
    }

    // Convert common bits to CIDR prefix length
    while (common_bits > 0) {
        cidr_prefix++;
        common_bits--;
    }

    return cidr_prefix;
}

// Function to calculate first and last IP address in the range
std::pair<std::string, std::string> calculate_ip_range(const std::string& ip, int cidr_prefix) {
    // Convert IP address to binary representation
    std::string ip_bin = ip_to_binary(ip);

    // Calculate first IP address
    std::string first_ip = ip_bin.substr(0, cidr_prefix);
    while (first_ip.length() < 32) {
        first_ip += "0";
    }

    // Calculate last IP address
    std::string last_ip = ip_bin.substr(0, cidr_prefix);
    while (last_ip.length() < 32) {
        last_ip += "1";
    }

    // Convert binary IPs to dotted decimal notation
    std::string first_ip_str = binary_to_ip(first_ip);
    std::string last_ip_str = binary_to_ip(last_ip);

    return std::make_pair(first_ip_str, last_ip_str);
}

int main(int argc, char* argv[]) {
    // Check if two IP addresses are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP_ADDRESS_1> <IP_ADDRESS_2>" << std::endl;
        return 1;
    }

    std::string ip1 = argv[1];
    std::string ip2 = argv[2];

    // Calculate CIDR prefix length
    int cidr_prefix = calculate_cidr_prefix(ip1, ip2);

    std::cout << "CIDR Prefix: /" << cidr_prefix << std::endl;

    // Calculate IP range
    auto ip_range = calculate_ip_range(ip1, cidr_prefix);
    std::cout << "First IP: " << ip_range.first << std::endl;
    std::cout << "Last IP: " << ip_range.second << std::endl;

    // Calculate total number of hosts
    uint64_t total_hosts = calculate_total_hosts(cidr_prefix);
    std::cout << "Total Hosts: " << total_hosts << std::endl;

    return 0;
}

// compile: g++ -o cidr_gen ciderGen.cpp

/*
RUN Example
./cidr_gen 134.191.196.161 134.191.196.190

OUTPUT:
CIDR Prefix: /27
First IP: 134.191.196.160
Last IP: 134.191.196.191
Total Hosts: 32
*/