#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source_selector/extra/nlohmann_json.hpp>

TEST_CASE("nlohmann_json") {
  {
    pqrs::osx::input_source_selector::specifier specifier;
    nlohmann::json json = specifier;
    pqrs::osx::input_source_selector::specifier specifier2 = json;

    REQUIRE(specifier == specifier2);
  }
  {
    pqrs::osx::input_source_selector::specifier specifier;
    specifier.set_language("^en$");
    specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");
    specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

    nlohmann::json json = specifier;
    pqrs::osx::input_source_selector::specifier specifier2 = json;

    REQUIRE(specifier == specifier2);
  }
}
