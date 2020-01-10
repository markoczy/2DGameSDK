#include <algorithm>
#include <examples.h>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Started." << endl;

  std::string demo = "chipmunk";
  if(argc > 1) {
    demo = argv[1];
    std::transform(demo.begin(), demo.end(), demo.begin(), ::tolower);
  }

  if(demo == "minimal") {
    minimalDemo();
  } else if(demo == "player") {
    playerDemo();
  } else if(demo == "gta2") {
    playerDemoGTA2();
  } else if(demo == "chopper") {
    chopperDemo();
  } else if(demo == "chipmunk") {
    int entities = 100;
    if(argc > 2) {
      entities = stoi(argv[2]);
      cout << "Spawning " << entities << " entities" << endl;
    }
    chipmunkDemo(entities);
  } else {
    cerr << "No Valid Demo selected, choices are: minimal, player, gta2, chopper" << endl;
  }

  return 0;
}