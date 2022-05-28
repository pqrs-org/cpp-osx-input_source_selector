#include <boost/ut.hpp>
#include <iostream>
#include <pqrs/osx/input_source_selector/extra/nlohmann_json.hpp>

void run_nlohmann_json_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "nlohmann_json"_test = [] {
    {
      pqrs::osx::input_source_selector::specifier specifier;
      nlohmann::json json = specifier;
      auto specifier2 = json.get<pqrs::osx::input_source_selector::specifier>();

      expect(specifier == specifier2);
    }
    {
      pqrs::osx::input_source_selector::specifier specifier;
      specifier.set_language("^en$");
      specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");
      specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

      nlohmann::json json = specifier;
      auto specifier2 = json.get<pqrs::osx::input_source_selector::specifier>();

      expect(specifier == specifier2);
    }

    // from_json

    {
      std::string language("^en$");
      std::string input_source_id("^com\\.apple\\.keylayout\\.US$");
      std::string input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

      auto json = nlohmann::json::object({
          {"language", language},
          {"input_source_id", input_source_id},
          {"input_mode_id", input_mode_id},
      });
      auto specifier = json.get<pqrs::osx::input_source_selector::specifier>();

      expect(specifier.get_language_string() == language);
      expect(specifier.get_input_source_id_string() == input_source_id);
      expect(specifier.get_input_mode_id_string() == input_mode_id);
    }

    // from_json (empty)

    {
      auto specifier = nlohmann::json::object().get<pqrs::osx::input_source_selector::specifier>();

      expect(specifier.get_language_string() == std::nullopt);
      expect(specifier.get_input_source_id_string() == std::nullopt);
      expect(specifier.get_input_mode_id_string() == std::nullopt);
    }

    // type error

    try {
      auto json = nlohmann::json();
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("json must be object, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // unknown key

    try {
      auto json = nlohmann::json::object({
          {"language", "^en$"},
          {"input_source_id", "^com\\.apple\\.keylayout\\.US$"},
          {"input-mode-id", "^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$"},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("unknown key: `input-mode-id`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type error (language)

    try {
      auto json = nlohmann::json::object({
          {"language", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`language` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // regex error (language)

    try {
      auto json = nlohmann::json::object({
          {"language", "(regex"},
          {"input_source_id", "regex"},
          {"input_mode_id", "regex"},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("The expression contained mismatched ( and ).: `\"language\":\"(regex\"`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type error (input_source_id)

    try {
      auto json = nlohmann::json::object({
          {"input_source_id", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`input_source_id` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // regex error (input_source_id)

    try {
      auto json = nlohmann::json::object({
          {"language", "regex"},
          {"input_source_id", "(regex"},
          {"input_mode_id", "regex"},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("The expression contained mismatched ( and ).: `\"input_source_id\":\"(regex\"`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // type error (input_mode_id)

    try {
      auto json = nlohmann::json::object({
          {"input_mode_id", nlohmann::json()},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("`input_mode_id` must be string, but is `null`") == ex.what());
    } catch (...) {
      expect(false);
    }

    // regex error (input_mode_id)

    try {
      auto json = nlohmann::json::object({
          {"language", "regex"},
          {"input_source_id", "regex"},
          {"input_mode_id", "(regex"},
      });
      json.get<pqrs::osx::input_source_selector::specifier>();
      expect(false);
    } catch (pqrs::json::unmarshal_error& ex) {
      expect(std::string("The expression contained mismatched ( and ).: `\"input_mode_id\":\"(regex\"`") == ex.what());
    } catch (...) {
      expect(false);
    }
  };
}
