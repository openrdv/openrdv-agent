#include <AttestPluginLoader.h>
#include <iostream>

int main(int argc, char **argv) {
  openrdv::AttestPluginLoader Loader;
  Loader.loadDirectory(".");
  return 0;
}
