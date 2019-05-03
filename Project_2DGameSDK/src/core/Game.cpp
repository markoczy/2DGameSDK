#include <2DGameSDK/core/Game.h>

using namespace std;

namespace game {

  Game::Game(GameOptions options, SceneGraph* scene, GameWorld* world, std::vector<ObservableBase*> events) : mOptions(options), mState(GameState{scene, world}) {
    for(auto iEvent : events) {
      mEventCtrl.AddEvent(iEvent);
    }
  }

  Game::~Game() {
    if(mWindow != nullptr) {
      delete mWindow;
      mWindow = nullptr;
    }
  }

  void Game::Run() {
    LOGI("Game started");
    mWindow = new sf::RenderWindow(sf::VideoMode(mOptions.ScreenDim.x, mOptions.ScreenDim.y), mOptions.Title);
    mView = mWindow->getView();

    int sleepMillis = int(1000.0 * (1.0 / mOptions.FramesPerSecond));
    sf::Clock clock;
    clock.restart();
    while(mWindow->isOpen()) {
      // Handle window events
      sf::Event event;
      while(mWindow->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
          LOGI("close event");
          Stop();
        }
      }

      // Game cycle
      tick();
      render();

      // Sync Sim Time
      int time = clock.getElapsedTime().asMilliseconds();
      if(sleepMillis > time) {
        LOGD("Sleeping " << sleepMillis - time);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMillis - time));
      }
      clock.restart();
    }
  }

  void Game::Stop() {
    mWindow->close();
    std::cout << "stop call" << std::endl;
  }

  void Game::tick() {
    mEventCtrl.Tick();
    mState.World->Tick();
    mState.Scene->Tick();
  }

  void Game::render() {
    mState.World->Render(mWindow);
    mState.Scene->Render(mWindow);
  }

} // namespace game