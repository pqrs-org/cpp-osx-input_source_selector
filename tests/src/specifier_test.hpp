#include <boost/ut.hpp>
#include <pqrs/osx/input_source_selector.hpp>

void run_specifier_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "specifier"_test = [] {
    // empty

    {
      pqrs::osx::input_source_selector::specifier specifier;

      expect(specifier.get_language_string() == std::nullopt);
      expect(specifier.get_input_source_id_string() == std::nullopt);
      expect(specifier.get_input_mode_id_string() == std::nullopt);

      {
        pqrs::osx::input_source::properties properties;
        expect(specifier.test(properties));

        properties.set_first_language("en");
        expect(specifier.test(properties));

        properties.set_input_source_id("com.apple.keylayout.US");
        expect(specifier.test(properties));

        properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
        expect(specifier.test(properties));
      }
    }

    // language

    {
      pqrs::osx::input_source_selector::specifier specifier;
      specifier.set_language("^en$");

      expect(specifier.get_language_string() == "^en$");
      expect(specifier.get_input_source_id_string() == std::nullopt);
      expect(specifier.get_input_mode_id_string() == std::nullopt);

      pqrs::osx::input_source::properties properties;
      expect(!specifier.test(properties));

      properties.set_first_language("en");
      expect(specifier.test(properties));

      properties.set_input_source_id("com.apple.keylayout.US");
      expect(specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
      expect(specifier.test(properties));

      properties.set_first_language("en2");
      expect(!specifier.test(properties));
    }

    // input_source_id

    {
      pqrs::osx::input_source_selector::specifier specifier;
      specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");

      expect(specifier.get_language_string() == std::nullopt);
      expect(specifier.get_input_source_id_string() == "^com\\.apple\\.keylayout\\.US$");
      expect(specifier.get_input_mode_id_string() == std::nullopt);

      pqrs::osx::input_source::properties properties;
      expect(!specifier.test(properties));

      properties.set_input_source_id("com.apple.keylayout.US");
      expect(specifier.test(properties));

      properties.set_first_language("en");
      expect(specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
      expect(specifier.test(properties));

      properties.set_input_source_id("com/apple/keylayout/US");
      expect(!specifier.test(properties));
    }

    // input_mode_id

    {
      pqrs::osx::input_source_selector::specifier specifier;
      specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

      expect(specifier.get_language_string() == std::nullopt);
      expect(specifier.get_input_source_id_string() == std::nullopt);
      expect(specifier.get_input_mode_id_string() == "^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

      pqrs::osx::input_source::properties properties;
      expect(!specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
      expect(specifier.test(properties));

      properties.set_first_language("en");
      expect(specifier.test(properties));

      properties.set_input_source_id("com.apple.keylayout.US");
      expect(specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.Japanese.FullWidthRoman");
      expect(!specifier.test(properties));
    }

    // combination

    {
      pqrs::osx::input_source_selector::specifier specifier;
      specifier.set_language("^en$");
      specifier.set_input_source_id("^com\\.apple\\.keylayout\\.US$");
      specifier.set_input_mode_id("^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

      expect(specifier.get_language_string() == "^en$");
      expect(specifier.get_input_source_id_string() == "^com\\.apple\\.keylayout\\.US$");
      expect(specifier.get_input_mode_id_string() == "^com\\.apple\\.inputmethod\\.SCIM\\.ITABC$");

      pqrs::osx::input_source::properties properties;
      expect(!specifier.test(properties));

      properties.set_first_language("en");
      expect(!specifier.test(properties));

      properties.set_input_source_id("com.apple.keylayout.US");
      expect(!specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.SCIM.ITABC");
      expect(specifier.test(properties));

      properties.set_input_mode_id("com.apple.inputmethod.Japanese.FullWidthRoman");
      expect(!specifier.test(properties));
    }
  };

  "specifier hash"_test = [] {
    {
      pqrs::osx::input_source_selector::specifier s1;
      s1.set_language("^en$");

      pqrs::osx::input_source_selector::specifier s2;

      expect(std::hash<pqrs::osx::input_source_selector::specifier>{}(s1) !=
             std::hash<pqrs::osx::input_source_selector::specifier>{}(s2));
    }
  };
}
