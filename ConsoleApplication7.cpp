#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string encodeQuotedPrintable(const string& input) {
    ostringstream encoded;
    int lineLength = 0;

    for (unsigned char c : input) {
        if ((c >= 33 && c <= 60) || (c >= 62 && c <= 126)) {
            encoded << c;
            lineLength++;
        }
        else if (c == ' ') {
            encoded << "=20";
            lineLength += 3;
        }
        else if (c == '=') {
            encoded << "=3D";
            lineLength += 3;
        }
        else {
            encoded << '=' << uppercase << hex << setw(2) << setfill('0') << static_cast<int>(c);
            lineLength += 3;
        }

        if (lineLength >= 73) {
            encoded << "=\n";
            lineLength = 0;
        }
    }

    return encoded.str();
}

string decodeQuotedPrintable(const string& input) {
    ostringstream decoded;
    for (size_t i = 0; i < input.length(); ++i) {
        if (input[i] == '=' && i + 2 < input.length()) {
            if (input[i + 1] == '\n') {
                i++;
                continue;
            }
            istringstream hexStream(input.substr(i + 1, 2));
            int hexValue;
            hexStream >> hex >> hexValue;
            decoded << static_cast<char>(hexValue);
            i += 2;
        }
        else {
            decoded << input[i];
        }
    }
    return decoded.str();
}

int main() {
    string text;
    getline(cin, text);
    string encoded = encodeQuotedPrintable(text);
    string decoded = decodeQuotedPrintable(encoded);

    cout << "Original: " << text << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;

    return 0;
}