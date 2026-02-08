cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment version")

project (input-source-selector-example-app)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-Wall)
add_compile_options(-Werror)
add_compile_options(-O2)
add_compile_options(-fobjc-arc)
add_compile_options(-fmodules)

include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../vendor/vendor/include)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/../include)

add_executable(
  input-source-selector-example-app
  MACOSX_BUNDLE
  src/AppDelegate.mm
  src/AppDelegate.h
  src/main.m
  Resources/MainMenu.xib
  Resources/Assets.xcassets
)

target_link_libraries(
  input-source-selector-example-app
  "-framework Carbon"
  "-framework Cocoa"
)

set_source_files_properties(
  Resources/MainMenu.xib
  Resources/Assets.xcassets
  PROPERTIES
  MACOSX_PACKAGE_LOCATION
  Resources
)

set_target_properties(
  input-source-selector-example-app
  PROPERTIES

  MACOSX_BUNDLE_INFO_PLIST
  ${CMAKE_CURRENT_LIST_DIR}/Resources/Info.plist

  XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER
  "org.pqrs.input-source-selector-example-app"

  XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME
  YES
)
