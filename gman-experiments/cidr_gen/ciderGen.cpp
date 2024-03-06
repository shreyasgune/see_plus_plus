#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>

// Function to convert IP address to binary representation
std::string ip_to_binary(const std::string& ip) {
    std::stringstream ss(ip);
    std::string token;
    std::vector<std::string> octets;

    while (std::getline(ss, token, '.')) {
        int octet = std::stoi(token);
        octets.push_back(std::bitset<8>(octet).to_string());
    }

    return octets[0] + octets[1] + octets[2] + octets[3];
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

    return 0;
}
