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

  unsigned char collideEntityAny(CollisionEventType type, cpArbiter* arb, Entity* ent, CollisionTarget* other) {
    switch(other->GetType()) {
    case ObjectType::Entity:
      return collideEntities(type, arb, ent, (Entity*)other->GetTarget());
    case ObjectType::Tile:
      return collideEntityTile(type, arb, ent, (Tile*)other->GetTarget());
    //TODO Projectile
    default:
      return 0;
    }
  }

  unsigned char collideTileAny(CollisionEventType type, cpArbiter* arb, Tile* tile, CollisionTarget* other) {
    switch(other->GetType()) {
    case ObjectType::Entity:
      return collideEntityTile(type, arb, (Entity*)other->GetTarget(), tile);
    case ObjectType::Tile:
      // Colliding tiles is senseless..
      return 0;
    //TODO Projectile
    default:
      return 0;
    }
  }

  unsigned char collisionFunc(CollisionEventType type, cpArbiter* arb) {
    cpBody* bodyA;
    cpBody* bodyB;
    cpArbiterGetBodies(arb, &bodyA, &bodyB);

    auto targetA = (CollisionTarget*)cpBodyGetUserData(bodyA);
    auto targetB = (CollisionTarget*)cpBodyGetUserData(bodyB);

    // switch(targetA->GetType()) {
    // case ObjectType::Entity:
    //   return collideEntityAny(type, arb, (Entity*)targetA->GetTarget(), targetB);
    // case ObjectType::Tile:
    //   return collideTileAny(type, arb, (Tile*)targetA->GetTarget(), targetB);
    // default:
    //   return 0;
    // }

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

  // TODO dep inversion..
  class OverlayDisplay {
  public:
    void OnTick();
    void OnRender(sf::RenderTarget* target);
  };

  // ###########################################################################
  // Constructor / Destructor
  // ###########################################################################

  Game::Game(GameOptions options) : mStateManager(this), mOptions(options) {
    LOGD("Game minimal contructor call");
    mPhysicalWorld = cpSpaceNew();
    auto collisionHandler = cpSpaceAddCollisionHandler(mPhysicalWorld, CollisionType::Default, CollisionType::Default);
    cpSpaceSetCollisionSlop(mPhysicalWorld, 0.01);

    collisionHandler->beginFunc = &collisionBegin;
    collisionHandler->preSolveFunc = &collisionPreSolve;
    collisionHandler->postSolveFunc = &collisionPostSolve;
    collisionHandler->separateFunc = &collisionSeparate;

    mDefaultCameraController = new DefaultCameraController(this);
    mCameraController = mDefaultCameraController;

    mAudioController = new AudioController();
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

    mDefaultCameraController->SetZoom(mOptions.InitialZoom);
    auto bounds = mDefaultCameraController->GetBounds();
    mDefaultCameraController->SetCenter(sf::Vector2f(bounds.x / 2, bounds.y / 2));

    // auto world = mStateManager.GetWorld();
    // mView = mWindow->getView();
    // auto sz = mView.getSize() / mOptions.InitialZoom;
    // mView.setSize(sz);
    // mView.setCenter(sz.x / 2, world->GetBounds().height - sz.y / 2);
    // mWindow->setView(mView);

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

  sf::RenderWindow* Game::GetWindow() {
    return mWindow;
  }

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

  CameraController* Game::GetCameraController() {
    return mCameraController;
  }

  AudioController* Game::GetAudioController() {
    return mAudioController;
  }

  void Game::SetScene(SceneGraph* scene) {
    mStateManager.SetScene(scene);
  }

  GameWorld* Game::GetWorld() {
    return mStateManager.GetWorld();
  }

  OverlayDisplay* Game::GetOverlayDisplay() {
    return mOverlayDisplay;
  }

  void Game::SetOptions(GameOptions options) {
    mOptions = options;
  }

  void Game::SetWorld(GameWorld* world) {
    mStateManager.SetWorld(world);

    helpers::safeDelete(mPoseConverter);
    mPoseConverter = new PoseConverter(world->GetBounds().width, world->GetBounds().height, mOptions.MeterPerPixel);
  }

  void Game::SetCameraController(CameraController* cameraController) {
    if(mCameraController != mDefaultCameraController) {
      helpers::safeDelete(mCameraController);
    }
    mCameraController = cameraController;
  }

  void Game::ResetCameraController() {
    if(mCameraController != mDefaultCameraController) {
      helpers::safeDelete(mCameraController);
      mCameraController = mDefaultCameraController;
    }
  }

  void Game::SetOverlayDisplay(OverlayDisplay* overlay) {
    mOverlayDisplay = overlay;
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
      mCameraController->OnTick();
      mAudioController->OnTick();
      if(mOverlayDisplay != nullptr) mOverlayDisplay->OnTick();
      mStateManager.OnTickEnded();
    } catch(std::exception& e) {
      LOGE("Error during tick: " << e.what());
    }
  }

  void Game::render() {
    try {
      mWindow->setView(mCameraController->GetView());
      mWindow->clear(sf::Color(80, 80, 80));
      mStateManager.OnRender(mWindow);
      if(mOverlayDisplay != nullptr) mOverlayDisplay->OnRender(mWindow);
      mWindow->display();
    } catch(std::exception& e) {
      LOGE("Error during render: " << e.what());
    }
  }

} // namespace game