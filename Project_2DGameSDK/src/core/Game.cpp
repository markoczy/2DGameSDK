#include <2DGameSDK/core/Game.h>

namespace game {

  Game::Game(GameOptions options) : mOptions(options) {
  }

  Game::~Game() {
    if(mWindow != nullptr) {
      delete mWindow;
      mWindow = nullptr;
    }
  }

  void Game::Run() {
    LOGD("Game started");
    mWindow = new sf::RenderWindow(sf::VideoMode(mOptions.ScreenDim.x, mOptions.ScreenDim.y), mOptions.Title);

    int sleepMillis = int(1000.0 * (1.0 / mOptions.FramesPerSecond));
    sf::Clock clock;

    clock.restart();
    while(mWindow->isOpen()) {
      // Handle window events
      sf::Event event;
      while(mWindow->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
          std::cout << "close event" << std::endl;
          Stop();
        }
      }

      // Game cycle
      tick();
      render();

      // Sync Sim Time
      int time = clock.getElapsedTime().asMilliseconds();
      if(sleepMillis > time) {
        std::cout << "Sleeping " << sleepMillis - time << std::endl;
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
  }

  void Game::render() {
  }

} // namespace game