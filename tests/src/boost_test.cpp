#include <catch2/catch.hpp>

#include <iostream>
#include <pqrs/osx/input_source_selector/extra/boost.hpp>

TEST_CASE("boost_specifier") {
  {
    pqrs::osx::input_source_selector::specifier s1;
    s1.set_language("^en$");

    pqrs::osx::input_source_selector::specifier s2;

    REQUIRE(boost::hash_value(s1) != boost::hash_value(s2));
  }
}
