/**
 * @file json_driver.cpp
 * @brief A driver to handle command line arguments and use the JSON parser to extract fields
 * @author Julien Marcuse
 * @assignment CSI-230 Final
 * @date 2020-12-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "json.h"

using namespace std;

/**
 * @brief A simple method to split a string at every occurrence of a character
 * @param str The string to split
 * @param c The character to split on
 * @return A vector containing the split parts of the string
 */
vector<string> split(string str, char c) {
    int last = 0;
    vector<string> vec;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c) {
            vec.push_back(str.substr(last, i - last));
            last = i + 1;
        }
    }
    vec.push_back(str.substr(last, str.length() - last));
    return vec;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Must specify file to read and JSON path to extract" << endl;
        return 1;
    }
    ifstream in(argv[1]);
    if (!in.is_open()) {
			cout << "File could not be opened." << endl;
			return 10;
    }
    string line;
    stringstream combine;
    while (!in.eof()) {
        getline(in, line);
        combine << line;
    }
    string json = combine.str();
    in.close();
    json_value parsed = parseJSON(json);
    vector<string> parts = split(argv[2], '.');
    json_map map;
    json_list list;
    for (string part : parts) {
        switch (parsed.index()) {
            default:
                cout << "Passed maximum depth, cannot proceed" << endl;
                return 2;
            case 4:
                int i;
                try {
                    i = stoi(part);
                } catch (invalid_argument) {
                    cout << "Tried to index list with non-integer value" << endl;
                    return 3;
                }
                list = get<json_list>(parsed);
                if (i < 0 || i >= list.size()) {
                    cout << "Invalid index " << i << endl;
                    return 4;
                }
                parsed = list[i];
                break;
            case 5:
                map = get<json_map>(parsed);
                if (map.find(part) == map.end()) {
                    cout << "Invalid key " << part << endl;
                    return 5;
                }
                parsed = map.find(part)->second;
                break;
        }
    }
    switch (parsed.index()) {
        case 0:
            cout << get<string>(parsed) << endl;
            break;
        case 1:
            cout << get<double>(parsed) << endl;
            break;
        case 2:
            cout << get<int>(parsed) << endl;
            break;
        case 3:
            cout << (get<bool>(parsed) ? "true" : "false") << endl;
            break;
        case 4:
            cout << "[JSON List]" << endl;
            break;
        case 5:
            cout << "[JSON Map]" << endl;
            break;
    }
}
