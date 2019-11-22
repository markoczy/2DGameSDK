#include <2DGameSDK/core/Game.h>

using namespace std;
using namespace game::constants;

namespace game {

  unsigned char collideEntities(CollisionEventType type, cpArbiter* arb, Entity* entA, Entity* entB) {
    if(!entA->IsCollidable() || !entB->IsCollidable()) return 0;
    int retA = entA->OnCollision(type, entB, arb);
    int retB = entB->OnCollision(type, entA, arb);
    return retA | retB;
  }

  unsigned char collideEntityTile(CollisionEventType type, cpArbiter* arb, Entity* entity, Tile* tile) {
    if(!entity->IsCollidable()) return 0;
    return entity->OnWorldCollision(type, tile, arb);
  }

  unsigned char collisionFunc(CollisionEventType type, cpArbiter* arb) {
    cpBody* bodyA;
    cpBody* bodyB;
    cpArbiterGetBodies(arb, &bodyA, &bodyB);

    auto targetA = (CollisionTarget*)cpBodyGetUserData(bodyA);
    auto targetB = (CollisionTarget*)cpBodyGetUserData(bodyB);

    bool aIsEntity = targetA->GetType() == ObjectType::Entity;
    bool bIsEntity = targetB->GetType() == ObjectType::Entity;

    if(aIsEntity) {
      if(bIsEntity) {
        return collideEntities(type, arb, (Entity*)targetA->GetTarget(), (Entity*)targetB->GetTarget());
      } else {
        return collideEntityTile(type, arb, (Entity*)targetA->GetTarget(), (Tile*)targetB->GetTarget());
      }
    } else {
      if(bIsEntity) {
        return collideEntityTile(type, arb, (Entity*)targetB->GetTarget(), (Tile*)targetA->GetTarget());
      }
    }
    return 0;
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

  Game::Game() {
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

    auto world = mStateManager.GetWorld();
    mView = mWindow->getView();
    auto sz = mView.getSize() / mOptions.InitialZoom;
    mView.setSize(sz);
    mView.setCenter(sz.x / 2, world->GetBounds().height - sz.y / 2);
    mWindow->setView(mView);

    float step = 1.0f / mOptions.FramesPerSecond;

    int sleepMillis = int(1000.0 * (1.0 / mOptions.FramesPerSecond));
    sf::Clock clock;
    while(mWindow->isOpen()) {
      clock.restart();
      // Handle window events
      sf::Event event;
      while(mWindow->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
          LOGI("close event");
          Stop();
        }
      }

      // Game cycle
      dbgClock.restart();
      tick();
      LOGD("Tick in: " << dbgClock.getElapsedTime().asMilliseconds());
      // Chipmunk recommends to use fixed time steps
      dbgClock.restart();
      cpSpaceStep(mPhysicalWorld, step);
      LOGD("Phys update in: " << dbgClock.getElapsedTime().asMilliseconds());

      dbgClock.restart();
      render();
      LOGD("Render in: " << dbgClock.getElapsedTime().asMilliseconds());

      // Sync Sim Time
      int time = clock.getElapsedTime().asMilliseconds();
      LOGD("Total Cycle time: " << time);
      if(sleepMillis > time) {
        // LOGD("Sleeping " << sleepMillis - time);
        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMillis - time));
      } else {
        LOGW("Overdue " << time - sleepMillis);
      }
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

  StateManagerBase* Game::GetStateManager() {
    return &mStateManager;
  }

  SceneGraph* Game::GetScene() {
    return mStateManager.GetScene();
  }

  PoseConverter* Game::GetPoseConverter() {
    return mPoseConverter;
  }

  void Game::SetScene(SceneGraph* scene) {
    mStateManager.SetScene(scene);
  }

  GameWorld* Game::GetWorld() {
    return mStateManager.GetWorld();
  }

  void Game::SetOptions(GameOptions options) {
    mOptions = options;
  }

  void Game::SetWorld(GameWorld* world) {
    mStateManager.SetWorld(world);

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
      mStateManager.OnTick();
    } catch(std::exception& e) {
      LOGE("Error during tick: " << e.what());
    }
  }

  void Game::render() {
    try {
      mWindow->clear(sf::Color(80, 80, 80));
      mStateManager.OnRender(mWindow);
      mWindow->display();
    } catch(std::exception& e) {
      LOGE("Error during render: " << e.what());
    }
  }

} // namespace game