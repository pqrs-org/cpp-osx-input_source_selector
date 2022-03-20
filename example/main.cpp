#include <csignal>
#include <iostream>
#include <pqrs/osx/input_source_selector.hpp>

namespace {
auto global_wait = pqrs::make_thread_wait();
}

int main(void) {
  std::signal(SIGINT, [](int) {
    global_wait->notify();
  });

  auto time_source = std::make_shared<pqrs::dispatcher::hardware_time_source>();
  auto dispatcher = std::make_shared<pqrs::dispatcher::dispatcher>(time_source);

  auto selector = std::make_shared<pqrs::osx::input_source_selector::selector>(dispatcher);

  auto specifiers = std::make_shared<std::vector<pqrs::osx::input_source_selector::specifier>>();

  {
    pqrs::osx::input_source_selector::specifier s;
    s.set_language("^ja$");
    specifiers->push_back(s);
  }

  selector->async_select(specifiers);

  std::thread thread([&selector] {
    global_wait->wait_notice();

    selector = nullptr;

    CFRunLoopStop(CFRunLoopGetMain());
  });

  // ============================================================

  CFRunLoopRun();

  // ============================================================

  thread.join();

  dispatcher->terminate();
  dispatcher = nullptr;

  std::cout << "finished" << std::endl;

  return 0;
}
