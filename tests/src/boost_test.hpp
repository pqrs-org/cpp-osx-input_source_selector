#include <boost/ut.hpp>
#include <iostream>
#include <pqrs/osx/input_source_selector/extra/boost.hpp>

void run_boost_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "boost_specifier"_test = [] {
    {
      pqrs::osx::input_source_selector::specifier s;
      s.set_language("^en$");

      expect(std::hash<pqrs::osx::input_source_selector::specifier>{}(s) ==
             pqrs::osx::input_source_selector::hash_value(s));
    }
  };
}
