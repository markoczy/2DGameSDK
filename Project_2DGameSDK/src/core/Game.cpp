#include <2DGameSDK/core/Game.h>

using namespace std;
using namespace game::constants;

namespace game {

  unsigned char collisionFunc(CollisionEventType type, cpArbiter* arb) {
    cpBody* bodyA;
    cpBody* bodyB;
    cpArbiterGetBodies(arb, &bodyA, &bodyB);

    auto entA = (Entity*)cpBodyGetUserData(bodyA);
    auto entB = (Entity*)cpBodyGetUserData(bodyB);

    // cout << "Collision Begin: " << entA->GetId() << " and " << entB->GetId() << endl;
    if(!entA->IsCollidable() || !entB->IsCollidable()) return 0;

    int retA = entA->OnCollision(type, entB, arb);
    int retB = entB->OnCollision(type, entA, arb);
    return retA | retB;
  }

  unsigned char collisionBegin(cpArbiter* arb, cpSpace*, cpDataPointer) {
    return collisionFunc(CollisionEventType::Begin, arb);
  }

  unsigned char collisionPreSolve(cpArbiter* arb, cpSpace*, cpDataPointer) {
    return collisionFunc(CollisionEventType::PreSolve, arb);
  }

  void collisionPostSolve(cpArbiter* arb, cpSpace*, cpDataPointer) {
    collisionFunc(CollisionEventType::PostSolve, arb);
  }

  void collisionSeparate(cpArbiter* arb, cpSpace*, cpDataPointer) {
    collisionFunc(CollisionEventType::Separate, arb);
  }

  sf::Clock dbgClock;

  // ###########################################################################
  // Constructor / Destructor
  // ###########################################################################

  Game::Game() : mState(GameState{nullptr, nullptr}) {
    LOGD("Game minimal contructor call");
    mPhysicalWorld = cpSpaceNew();
    auto collisionHandler = cpSpaceAddCollisionHandler(mPhysicalWorld, CollisionType::Default, CollisionType::Default);
    cpSpaceSetCollisionSlop(mPhysicalWorld, 0.01);

    collisionHandler->beginFunc = &collisionBegin;
    collisionHandler->preSolveFunc = &collisionPreSolve;
    collisionHandler->postSolveFunc = &collisionPostSolve;
    collisionHandler->separateFunc = &collisionSeparate;
  }

  Game::~Game() {
    helpers::safeDelete(mWindow);
    helpers::safeDelete(mState.Scene);
    helpers::safeDelete(mState.World);
    helpers::safeDelete(mPoseConverter);
    cpSpaceDestroy(mPhysicalWorld);
  }

  // ###########################################################################
  // Public Methods
  // ###########################################################################

  void Game::Run() {
    LOGI("Game started");
    cpSpaceSetIterations(mPhysicalWorld, 10);
    mWindow = new sf::RenderWindow(sf::VideoMode(mOptions.ScreenDim.x, mOptions.ScreenDim.y), mOptions.Title);
    mWindow->setFramerateLimit(mOptions.FramesPerSecond);
    // mWindow->setVerticalSyncEnabled(true);

    mView = mWindow->getView();
    auto sz = mView.getSize() / mOptions.InitialZoom;
    mView.setSize(sz);
    mView.setCenter(sz.x / 2, mState.World->GetBounds().height - sz.y / 2);
    mWindow->setView(mView);

    float step = 1.0f / mOptions.FramesPerSecond;

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
      // Chipmunk recommends to use fixed time steps
      cpSpaceStep(mPhysicalWorld, step);

      IFLOGD(int tickTime = clock.getElapsedTime().asMilliseconds();)
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

  cpSpace* Game::GetPhysicalWorld() {
    return mPhysicalWorld;
  }

  // ####### Accessors (get/set) ###############################################

  GameOptions Game::GetOptions() {
    return mOptions;
  }

  GameState Game::GetState() {
    return mState;
  }

  SceneGraph* Game::GetScene() {
    return mState.Scene;
  }

  PoseConverter* Game::GetPoseConverter() {
    return mPoseConverter;
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

    helpers::safeDelete(mPoseConverter);
    mPoseConverter = new PoseConverter(world->GetBounds().width, world->GetBounds().height, mOptions.MeterPerPixel);
  }

  // ####### Event Controller wrapper ##########################################

  int Game::AddEvent(ObservableBase* event) {
    return mEventCtrl.AddEvent(event);
  }

  ObservableBase* Game::GetEvent(int identifier) {
    return mEventCtrl.GetEvent(identifier);
  }

  // ###########################################################################
  // Private / Protected Methods
  // ###########################################################################

  void Game::tick() {
    try {
      mEventCtrl.OnTick();
      mState.World->OnTick();
      mState.Scene->OnTick();
    } catch(std::exception& e) {
      LOGE("Error during tick: " << e.what());
    }
  }

  void Game::render() {
    try {
      mWindow->clear(sf::Color(80, 80, 80));
      dbgClock.restart();
      mState.World->OnRender(mWindow);
      LOGD("Render World in: " << dbgClock.getElapsedTime().asMilliseconds());
      dbgClock.restart();
      mState.Scene->OnRender(mWindow, &mOptions);
      LOGD("Render Scene in: " << dbgClock.getElapsedTime().asMilliseconds());
      dbgClock.restart();
      mWindow->display();
      LOGD("Display in: " << dbgClock.getElapsedTime().asMilliseconds());
    } catch(std::exception& e) {
      LOGE("Error during render: " << e.what());
    }
  }

} // namespace game