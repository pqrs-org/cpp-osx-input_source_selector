#include <boost/ut.hpp>
#include <pqrs/osx/input_source_selector.hpp>

void run_selector_test(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "selector"_test = [] {
    auto time_source = std::make_shared<pqrs::dispatcher::hardware_time_source>();
    auto dispatcher = std::make_shared<pqrs::dispatcher::dispatcher>(time_source);

    auto selector = std::make_shared<pqrs::osx::input_source_selector::selector>(dispatcher);

    std::thread th([&selector] {
      selector = nullptr;

      CFRunLoopStop(CFRunLoopGetMain());
    });

    CFRunLoopRun();

    th.join();

    dispatcher->terminate();
    dispatcher = nullptr;
  };
}
