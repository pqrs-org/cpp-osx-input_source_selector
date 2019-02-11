#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source_selector/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json") {
  {
    pqrs::osx::input_source_selector::specifier specifier;
    nlohmann::json json = specifier;
    auto specifier2 = json.get<pqrs::osx::input_source_selector::specifier>();

    REQUIRE(specifier == specifier2);
  }
  {
    pqrs::osx::input_source_selector::specifier specifier;
    specifier.set_language("^en$");
    specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");
    specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

    nlohmann::json json = specifier;
    auto specifier2 = json.get<pqrs::osx::input_source_selector::specifier>();

    REQUIRE(specifier == specifier2);
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

    REQUIRE(specifier.get_language_string() == language);
    REQUIRE(specifier.get_input_source_id_string() == input_source_id);
    REQUIRE(specifier.get_input_mode_id_string() == input_mode_id);
  }

  // from_json (empty)

  {
    auto specifier = nlohmann::json::object().get<pqrs::osx::input_source_selector::specifier>();

    REQUIRE(specifier.get_language_string() == std::nullopt);
    REQUIRE(specifier.get_input_source_id_string() == std::nullopt);
    REQUIRE(specifier.get_input_mode_id_string() == std::nullopt);
  }

  // type error

  {
    auto json = nlohmann::json();

    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        "json must be object, but is `null`");
  }

  // unknown key

  {
    auto json = nlohmann::json::object({
        {"language", "^en$"},
        {"input_source_id", "^com\\.apple\\.keylayout\\.US$"},
        {"input-mode-id", "^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$"},
    });

    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        "unknown key: `input-mode-id`");
  }

  // type error (language)

  {
    auto json = nlohmann::json::object({
        {"language", nlohmann::json()},
    });

    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        "`language` must be string, but is `null`");
  }

  // type error (input_source_id)

  {
    auto json = nlohmann::json::object({
        {"input_source_id", nlohmann::json()},
    });

    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        "`input_source_id` must be string, but is `null`");
  }

  // type error (input_mode_id)

  {
    auto json = nlohmann::json::object({
        {"input_mode_id", nlohmann::json()},
    });

    REQUIRE_THROWS_AS(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        pqrs::json::unmarshal_error);
    REQUIRE_THROWS_WITH(
        json.get<pqrs::osx::input_source_selector::specifier>(),
        "`input_mode_id` must be string, but is `null`");
  }
}
