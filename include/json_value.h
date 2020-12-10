/**
 * @file json_value.h
 * @author Julien Marcuse
 * @brief Simple definitions for polymorphic JSON data types
 * @assignment CSI-230 Final
 * @date 2020-12-02
 */

#ifndef JSON_JSON_VALUE_H
#define JSON_JSON_VALUE_H
#include <variant>
#include <string>
#include <map>
#include <vector>
#include <optional>

class json_list;
class json_map;
using json_value = std::variant<std::string, double, int, bool, json_list, json_map>;
struct json_list: public std::vector<json_value> {

    template <typename T>
    T& get(const int index) {
        return std::get<T>(operator[](index));
    }

};
struct json_map: public std::map<std::string, json_value> {

    template <typename T>
    T& get(const std::string& index) {
        return std::get<T>(find(index)->second);
    }

};

#endif //JSON_JSON_VALUE_H
