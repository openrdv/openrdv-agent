#include <AttestManager.h>
#include <AttestPluginLoader.h>
#include <iostream>

int main(int argc, char **argv) {
  openrdv::AttestManager Manager(".");
  Manager.runTests();
  return 0;
}
