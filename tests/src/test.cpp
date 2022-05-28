#include "boost_test.hpp"
#include "nlohmann_json_test.hpp"
#include "selector_test.hpp"
#include "specifier_test.hpp"

int main(void) {
  run_boost_test();
  run_nlohmann_json_test();
  run_selector_test();
  run_specifier_test();
  return 0;
}
