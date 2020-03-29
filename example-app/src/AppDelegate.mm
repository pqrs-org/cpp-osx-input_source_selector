#import "AppDelegate.h"
#include <pqrs/dispatcher.hpp>
#include <pqrs/osx/input_source_selector.hpp>

@interface AppDelegate ()

@property(weak) IBOutlet NSWindow *window;
@property std::shared_ptr<pqrs::osx::input_source_selector::selector> input_source_selector;

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
  pqrs::dispatcher::extra::initialize_shared_dispatcher();

  self.input_source_selector = std::make_shared<pqrs::osx::input_source_selector::selector>(
      pqrs::dispatcher::extra::get_shared_dispatcher());
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
  self.input_source_selector = nullptr;

  pqrs::dispatcher::extra::terminate_shared_dispatcher();
}

- (IBAction)selectInputSourceEn:(id)sender {
  auto specifiers = std::make_shared<std::vector<pqrs::osx::input_source_selector::specifier>>();

  {
    pqrs::osx::input_source_selector::specifier s;
    s.set_language("^en$");
    specifiers->push_back(s);
  }

  self.input_source_selector->async_select(specifiers);
}

- (IBAction)selectInputSourceJa:(id)sender {
  auto specifiers = std::make_shared<std::vector<pqrs::osx::input_source_selector::specifier>>();

  {
    pqrs::osx::input_source_selector::specifier s;
    s.set_language("^ja$");
    specifiers->push_back(s);
  }

  self.input_source_selector->async_select(specifiers);
}

@end
