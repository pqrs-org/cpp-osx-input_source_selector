#include <catch2/catch.hpp>

#include <pqrs/osx/input_source_selector.hpp>

TEST_CASE("specifier") {
  // empty

  {
    pqrs::osx::input_source_selector::specifier specifier;

    REQUIRE(specifier.get_language_string() == std::nullopt);
    REQUIRE(specifier.get_input_source_id_string() == std::nullopt);
    REQUIRE(specifier.get_input_mode_id_string() == std::nullopt);

    {
      pqrs::osx::input_source::properties properties;
      REQUIRE(specifier.test(properties));

      properties.set_first_language("en");
      REQUIRE(specifier.test(properties));

      properties.set_input_source_id("com.apple.keylayout.US");
      REQUIRE(specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
      REQUIRE(specifier.test(properties));
    }
  }

  // language

  {
    pqrs::osx::input_source_selector::specifier specifier;
    specifier.set_language("^en$");

    REQUIRE(specifier.get_language_string() == "^en$");
    REQUIRE(specifier.get_input_source_id_string() == std::nullopt);
    REQUIRE(specifier.get_input_mode_id_string() == std::nullopt);

    pqrs::osx::input_source::properties properties;
    REQUIRE(!specifier.test(properties));

    properties.set_first_language("en");
    REQUIRE(specifier.test(properties));

    properties.set_input_source_id("com.apple.keylayout.US");
    REQUIRE(specifier.test(properties));

    properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
    REQUIRE(specifier.test(properties));

    properties.set_first_language("en2");
    REQUIRE(!specifier.test(properties));
  }

  // input_source_id

  {
    pqrs::osx::input_source_selector::specifier specifier;
    specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");

    REQUIRE(specifier.get_language_string() == std::nullopt);
    REQUIRE(specifier.get_input_source_id_string() == "^com\\.apple\\.keylayout\\.US$");
    REQUIRE(specifier.get_input_mode_id_string() == std::nullopt);

    pqrs::osx::input_source::properties properties;
    REQUIRE(!specifier.test(properties));

    properties.set_input_source_id("com.apple.keylayout.US");
    REQUIRE(specifier.test(properties));

    properties.set_first_language("en");
    REQUIRE(specifier.test(properties));

    properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
    REQUIRE(specifier.test(properties));

    properties.set_input_source_id("com/apple/keylayout/US");
    REQUIRE(!specifier.test(properties));
  }

  // input_mode_id

  {
    pqrs::osx::input_source_selector::specifier specifier;
    specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

    REQUIRE(specifier.get_language_string() == std::nullopt);
    REQUIRE(specifier.get_input_source_id_string() == std::nullopt);
    REQUIRE(specifier.get_input_mode_id_string() == "^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

    pqrs::osx::input_source::properties properties;
    REQUIRE(!specifier.test(properties));

    properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
    REQUIRE(specifier.test(properties));

    properties.set_first_language("en");
    REQUIRE(specifier.test(properties));

    properties.set_input_source_id("com.apple.keylayout.US");
    REQUIRE(specifier.test(properties));

    properties.set_input_mode_id("com.apple.inputmethod.Japanese.FullWidthRoman");
    REQUIRE(!specifier.test(properties));
  }

  // combination

  {
    pqrs::osx::input_source_selector::specifier specifier;
    specifier.set_language("^en$");
    specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");
    specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

    REQUIRE(specifier.get_language_string() == "^en$");
    REQUIRE(specifier.get_input_source_id_string() == "^com\\.apple\\.keylayout\\.US$");
    REQUIRE(specifier.get_input_mode_id_string() == "^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

    pqrs::osx::input_source::properties properties;
    REQUIRE(!specifier.test(properties));

    properties.set_first_language("en");
    REQUIRE(!specifier.test(properties));

    properties.set_input_source_id("com.apple.keylayout.US");
    REQUIRE(!specifier.test(properties));

    properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
    REQUIRE(specifier.test(properties));

    properties.set_input_mode_id("com.apple.inputmethod.Japanese.FullWidthRoman");
    REQUIRE(!specifier.test(properties));
  }
}
