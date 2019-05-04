#include <2DGameSDK/core/Game.h>

using namespace std;

namespace game {

  // ###########################################################################
  // Constructor / Destructor
  // ###########################################################################

  Game::Game() : mState(GameState{nullptr, nullptr}) {}

  Game::Game(GameOptions options, SceneGraph* scene, GameWorld* world) : mOptions(options), mState(GameState{scene, world}) {}

  Game::~Game() {
    if(mWindow != nullptr) {
      delete mWindow;
      mWindow = nullptr;
    }
  }

  // ###########################################################################
  // Public Methods
  // ###########################################################################

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

  // ####### Accessors (get/set) ###############################################

  GameState Game::GetState() {
    return mState;
  }

  SceneGraph* Game::GetScene() {
    return mState.Scene;
  }

  void Game::SetScene(SceneGraph* scene) {
    mState.Scene = scene;
  }

  GameWorld* Game::GetWorld() {
    return mState.World;
  }

  void Game::SetWorld(GameWorld* world) {
    mState.World = world;
  }

  // ####### Event Controller wrapper ##########################################

  int Game::AddEvent(ObservableBase* event) {
    mEventCtrl.AddEvent(event);
  }

  ObservableBase* Game::GetEvent(int identifier) {
    return mEventCtrl.GetEvent(identifier);
  }

  // ###########################################################################
  // Private / Protected Methods
  // ###########################################################################

  void Game::tick() {
    mEventCtrl.Tick();
    mState.World->Tick();
    mState.Scene->Tick();
  }

  void Game::render() {
    mWindow->clear();
    mState.World->Render(mWindow);
    mState.Scene->Render(mWindow);
    mWindow->display();
  }

} // namespace game