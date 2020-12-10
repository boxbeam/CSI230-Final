# C++ JSON parser

## How to use


To use the C++ JSON parser, first include "json.h". This will all include json_value.

Now, usage of the library is incredibly simple. Just call parseJSON, passing a string, and a json_value will be returned.

json_value is an alias for variant<string, int, double, bool, json_list, json_map>. json_list is a wrapper for a vector<json_value>, and similarly, json_map is a wrapper for a map<string, json_value>.

These wrapper types both have a `get` function, used like: `map.get<int>("hello")` and `list.get<int>(0)` to get a value of a specific type from a specific index easily.

Happy parsing!
