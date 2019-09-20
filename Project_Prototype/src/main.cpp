#include <algorithm>
#include <examples.h>

using namespace std;

int main(int argc, char* argv[]) {
  cout << "Started." << endl;

  std::string demo = "box2d";
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
  } else if(demo == "box2d") {
    box2dDemo();
  } else {
    cerr << "No Valid Demo selected, choices are: minimal, player, gta2, chopper" << endl;
  }

  return 0;
}