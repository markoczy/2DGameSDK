#include <algorithm>
#include <examples.h>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Started." << endl;

  std::string demo = "proto1";
  if(argc > 1) {
    demo = argv[1];
    std::transform(demo.begin(), demo.end(), demo.begin(), ::tolower);
  }

  if(demo == "proto1") {
    return prototype1();
  } else if(demo == "minimal") {
    return minimalDemo();
  } else if(demo == "player") {
    return playerDemo();
  } else if(demo == "gta2") {
    return playerDemoGTA2();
  } else if(demo == "chopper") {
    return chopperDemo();
  } else if(demo == "physics") {
    return physicsDemo();
  } else {
    cerr << "No Valid Demo selected, choices are: minimal, player, gta2, chopper" << endl;
    return 1;
  }
}