/**
 * @file json.h
 * @brief A simple, lightweight JSON parser which exports a single method
 * @author Julien Marcuse
 * @assignment CSI-230 Final
 * @date 2020-12-02
 */

#ifndef JSON_JSON_H
#define JSON_JSON_H
#include <variant>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "json_value.h"

/**
 * @brief Parses a JSON value, which can be a string, int, double, bool, json_list, or json_map
 * @param str The JSON string
 * @return The parsed JSON value
 */
json_value parseJSON(const std::string& str);

#endif //JSON_JSON_H
