#include "Password.h"

std::string base64_encode(const std::string& in) {
    const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;

    int val = 0, valb = -6;

    for (char c : in) {
        val = (val << 8) + c;
        valb += 8;

        while (valb >= 0) {
            out.push_back(b[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6)
        out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4)
        out.push_back('=');

    return out;
}

void savePassword(const std::string& newPassword) {
    std::fstream textfile;
    textfile.open(std::filesystem::path("./password.txt"), std::ios::out | std::ios::trunc);

    textfile << base64_encode(newPassword) << std::endl;

    textfile.close();
}

bool checkPassword(const std::string& toCheck) {
    std::fstream textfile;
    textfile.open(std::filesystem::path("./password.txt"), std::ios::in);

    std::string password;

    std::getline(textfile, password);
    textfile.close();
    if (password == base64_encode(toCheck))
        return true;
    else return false;
}