#include <2DGameSDK/core/Game.h>

using namespace std;

namespace game {

  sf::Clock dbgClock;

  // ###########################################################################
  // Constructor / Destructor
  // ###########################################################################

  Game::Game() : mState(GameState{nullptr, nullptr}) {}

  Game::Game(GameOptions options, SceneGraph* scene, GameWorld* world) : mOptions(options), mState(GameState{scene, world}) {
    LOGD("Game contructor call");
  }

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
    mWindow->setFramerateLimit(mOptions.FramesPerSecond);
    // mWindow->setVerticalSyncEnabled(true);
    mView = mWindow->getView();
    if(mOptions.InitialZoom != 1.0) {
      auto viewport = mView.getViewport();
      viewport.width *= mOptions.InitialZoom;
      viewport.height *= mOptions.InitialZoom;
      mView.setViewport(viewport);
      mWindow->setView(mView);
    }

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
      int tickTime = clock.getElapsedTime().asMilliseconds();
      render();

      // Sync Sim Time
      int time = clock.getElapsedTime().asMilliseconds();
      if(sleepMillis > time) {
        // LOGD("Sleeping " << sleepMillis - time);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMillis - time));
      } else {
        LOGW("Overdue " << time - sleepMillis);
      }
      LOGD("Tick time:" << tickTime << ", Render Time: " << time - tickTime);
      clock.restart();
    }
  }

  void Game::Stop() {
    LOGI("Stop call");
    mWindow->close();
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

  void Game::SetOptions(GameOptions options) {
    mOptions = options;
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
    dbgClock.restart();
    mState.World->Render(mWindow);
    LOGD("Render World in: " << dbgClock.getElapsedTime().asMilliseconds());
    dbgClock.restart();
    mState.Scene->Render(mWindow);
    LOGD("Render Scene in: " << dbgClock.getElapsedTime().asMilliseconds());
    dbgClock.restart();
    mWindow->display();
    LOGD("Display in: " << dbgClock.getElapsedTime().asMilliseconds());
  }

} // namespace game