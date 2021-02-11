#include <AttestPluginLoader.h>
#include <iostream>

int main(int argc, char **argv) {
  openrdv::AttestPluginLoader loader;
  loader.loadDirectory(".");
  return 0;
}
