#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source_selector/extra/boost.hpp>

TEST_CASE("boost_specifier") {
  {
    pqrs::osx::input_source_selector::specifier s;
    s.set_language("^en$");

    REQUIRE(std::hash<pqrs::osx::input_source_selector::specifier>{}(s) ==
            pqrs::osx::input_source_selector::hash_value(s));
  }
}
