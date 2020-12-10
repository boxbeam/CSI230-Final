/**
 * @file json.cpp
 * @author Julien Marcuse
 * @brief Method implementations and internals for JSON parser
 * @assignment CSI-230 Final
 * @date 2020-12-02
 */

#include "json.h"
using namespace std;

json_list parseList(const string& str, int begin);
json_map parseMap(const string& str, int begin);

/**
 * @brief Parses a simple JSON object, or delegates parsing to parseList or parseMap
 * @param str The JSON string to parse
 * @param begin The beginning index to parse from
 * @param end The ending index to parse to
 * @return The parsed JSON value
 */
json_value parse(const string& str, int begin, int end) {
    while (str[begin] == ' ' || str[begin] == '\n') begin++; // Skip leading whitespace
    while (str[end - 1] == ' ' || str[end - 1] == '\n') end--; // Skip trailing whitespace
    int diff = end - begin;
    switch (str[begin]) { // Determine the datatype based on the first character
        default: return json_value(0);
        case '"': return str.substr(begin + 1, diff - 2);
        case '[': return json_value(parseList(str, begin)); // Delegate parsing to parseList function
        case '{': return json_value(parseMap(str, begin)); // Delegate parsing to parseMap function
        case 't': return json_value(true);
        case 'f': return json_value(false);
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            int pos = str.find('.', begin);
            if (pos != -1 && pos < end) return json_value(stod(str.substr(begin, diff)));
            return json_value(stoi(str.substr(begin, diff)));
    }
}

/**
 * @brief Implementation for exported method, just wraps parse
 */
json_value parseJSON(const string& str) {
    return parse(str, 0, str.length());
}

/**
 * @brief Internal: finds the next occurrence of a non-quoted comma within a JSON context, or the end of the JSON context
 * @param str The string to find the index in
 * @param begin The beginning index to search from
 * @return The index of the next place to split
 */
int findNext(const string& str, int begin) {
    int depth = 1;
    bool quote = false;
    for (unsigned int i = begin; i < str.length(); i++) {
        switch (str[i]) {
            case '{': case '[':
                depth++;
                break;
            case '}': case ']':
                depth--;
                if (depth == 0) {
                    return i;
                }
                break;
            case '\\':
                i++;
                break;
            case '"':
                quote = !quote;
                break;
            case ',':
                if (depth == 1 && !quote) return i;
                break;
        }
    }
    return -1;
}

/**
 * @brief Parses a list from a JSON string
 * @param str The JSON string containing the list
 * @param begin The index to begin from
 * @return The parsed JSON list
 */
json_list parseList(const string& str, int begin) {
    json_list list;
    if (str[begin + 1] == ']') return list;
    int last = begin;
    int next;
    while (true) {
        next = findNext(str, last + 1);
        if (next == -1) return list;
        json_value val = parse(str, last + 1, next);
        list.push_back(val);
        last = next;
        if (str[next] == ']') break;
    }
    return list;
}

/**
 * @brief Parses a map from a JSON string
 * @param str The JSON string containing the list
 * @param begin The index to begin from
 * @return The parsed JSON map
 */
json_map parseMap(const string& str, int begin) {
    json_map map;
    if (str[begin + 1] == '}') return map;
    int last = begin;
    int next;
    while (true) {
        next = findNext(str, last + 1);
        if (next == -1) return map;
        int colon = str.find(':', last);
        if (colon == -1 || colon >= next) return map;
        string key = get<string>(parse(str, last + 1, colon));
        map.insert_or_assign(key, parse(str, colon + 1, next));
        last = next;
        if (str[next] == '}') break;
    }
    return map;
}
