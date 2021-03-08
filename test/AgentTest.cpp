#define BOOST_TEST_MODULE Agent Test
#include <boost/test/unit_test.hpp>

#include <AttestManager.h>

BOOST_AUTO_TEST_SUITE(test_suite_plugin_loader)

BOOST_AUTO_TEST_CASE(plugin_loader_directory) {
  openrdv::AttestPluginLoader Loader;
  auto Result = Loader.loadDirectory(".");
  BOOST_TEST(Result >= 0);
}

BOOST_AUTO_TEST_CASE(plugin_loader_file) {
  openrdv::AttestPluginLoader Loader;
  boost::shared_ptr<openrdv::AttestPlugin> Result =
      Loader.loadFile("./libsample_plugin.so");
  BOOST_TEST(Result != nullptr);
  BOOST_TEST(Result->name() == "SamplePlugin");
  BOOST_TEST(Result->description() ==
             "This is a sample device verification plugin for OpenRDV.");
  BOOST_TEST((int)Result->initialize() ==
             (int)openrdv::AttestStatus::InitializeSuccess);
  BOOST_TEST((int)Result->cleanup() ==
             (int)openrdv::AttestStatus::CleanupSuccess);
  BOOST_TEST(!Result->run().empty());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_suite_attest_manager)

BOOST_AUTO_TEST_CASE(attest_manager_run_tests) {
  openrdv::AttestManager Manager(".");
  openrdv::AttestResultMap Result = Manager.runTests();
  BOOST_TEST(!Result.empty());
}

BOOST_AUTO_TEST_SUITE_END()