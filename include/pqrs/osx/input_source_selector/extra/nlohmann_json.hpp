#pragma once

// (C) Copyright Takayama Fumihiko 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)

#include <pqrs/json.hpp>
#include <pqrs/osx/input_source_selector/specifier.hpp>

namespace pqrs {
namespace osx {
namespace input_source_selector {
inline void to_json(nlohmann::json& j, const specifier& s) {
  j = nlohmann::json::object();

  if (auto& v = s.get_language_string()) {
    j["language"] = *v;
  }

  if (auto& v = s.get_input_source_id_string()) {
    j["input_source_id"] = *v;
  }

  if (auto& v = s.get_input_mode_id_string()) {
    j["input_mode_id"] = *v;
  }
}

inline void from_json(const nlohmann::json& j, specifier& s) {
  using namespace std::string_literals;

  json::requires_object(j, "json");

  for (const auto& [key, value] : j.items()) {
    if (key == "language") {
      json::requires_string(value, "`"s + key + "`");

      try {
        s.set_language(value.get<std::string>());
      } catch (std::regex_error& e) {
        throw json::unmarshal_error(e.what() + ": `\""s + key + "\":" + value.dump() + "`"s);
      }

    } else if (key == "input_source_id") {
      json::requires_string(value, "`"s + key + "`");

      try {
        s.set_input_source_id(value.get<std::string>());
      } catch (std::regex_error& e) {
        throw json::unmarshal_error(e.what() + ": `\""s + key + "\":" + value.dump() + "`"s);
      }

    } else if (key == "input_mode_id") {
      json::requires_string(value, "`"s + key + "`");

      try {
        s.set_input_mode_id(value.get<std::string>());
      } catch (std::regex_error& e) {
        throw json::unmarshal_error(e.what() + ": `\""s + key + "\":" + value.dump() + "`"s);
      }

    } else {
      throw json::unmarshal_error("unknown key: `"s + key + "`"s);
    }
  }
}
} // namespace input_source_selector
} // namespace osx
} // namespace pqrs
