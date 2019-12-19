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

  unsigned char collideEntityProjectile(CollisionEventType type, cpArbiter* arb, Entity* entity, Projectile* projectile) {
    if(!entity->IsCollidable()) return 0;
    projectile->OnCollision(type, arb);
    return entity->OnProjectileCollision(type, projectile, arb);
  }

  unsigned char collideProjectileTile(CollisionEventType type, cpArbiter* arb, Projectile* projectile, Tile*) {
    projectile->OnCollision(type, arb);
    return 0;
  }

  unsigned char collideEntityAny(CollisionEventType type, cpArbiter* arb, Entity* ent, CollisionTarget* other) {
    switch(other->GetType()) {
    case ObjectType::Entity:
      return collideEntities(type, arb, ent, (Entity*)other->GetTarget());
    case ObjectType::Tile:
      return collideEntityTile(type, arb, ent, (Tile*)other->GetTarget());
    case ObjectType::Projectile:
      return collideEntityProjectile(type, arb, ent, (Projectile*)other->GetTarget());
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
    case ObjectType::Projectile:
      return collideProjectileTile(type, arb, (Projectile*)other->GetTarget(), tile);
    default:
      return 0;
    }
  }

  unsigned char collideProjectileAny(CollisionEventType type, cpArbiter* arb, Projectile* projectile, CollisionTarget* other) {
    switch(other->GetType()) {
    case ObjectType::Entity:
      return collideEntityProjectile(type, arb, (Entity*)other->GetTarget(), projectile);
    case ObjectType::Tile:
      return collideProjectileTile(type, arb, projectile, (Tile*)other->GetTarget());
      ;
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

    switch(targetA->GetType()) {
    case ObjectType::Entity:
      return collideEntityAny(type, arb, (Entity*)targetA->GetTarget(), targetB);
    case ObjectType::Tile:
      return collideTileAny(type, arb, (Tile*)targetA->GetTarget(), targetB);
    case ObjectType::Projectile:
      return collideProjectileAny(type, arb, (Projectile*)targetA->GetTarget(), targetB);
    default:
      return 0;
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

  void renderFunc(Game* game, sf::RenderWindow* win, StateManager* mgr) {
    win->setFramerateLimit(game->GetOptions().FramesPerSecond);
    win->setVerticalSyncEnabled(true);
    win->setActive(true);
    while(game->IsRunning()) {
      win->clear(sf::Color(80, 80, 80));
      win->setView(game->GetView());
      mgr->OnRender(win);
      win->display();
    }
    win->close();
  }

  sf::Clock dbgClock;

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

    mAudioController = new AudioController(this);
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
    mRunning = true;
    cpSpaceSetIterations(mPhysicalWorld, 10);
    mWindow = new sf::RenderWindow(sf::VideoMode(mOptions.ScreenDim.x, mOptions.ScreenDim.y), mOptions.Title);

    mDefaultCameraController->SetZoom(mOptions.InitialZoom);
    auto bounds = mDefaultCameraController->GetBounds();
    mDefaultCameraController->SetCenter(sf::Vector2f(bounds.x / 2, bounds.y / 2));

    mWindow->setActive(false);
    mRenderThread = new sf::Thread(std::bind(&renderFunc, this, mWindow, &mStateManager));
    mRenderThread->launch();

    float step = 1.0f / mOptions.FramesPerSecond;

    int sleepMillis = int(1000.0 * (1.0 / mOptions.FramesPerSecond));
    sf::Clock clock;
    while(mRunning) {
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

      // Sync Sim Time
      int time = clock.getElapsedTime().asMilliseconds();
      LOGD("Total Cycle time: " << time);
      if(sleepMillis > time) {
        LOGD("Sleeping " << sleepMillis - time);
        sf::sleep(sf::milliseconds(sleepMillis - time));
      } else {
        LOGW("Overdue " << time - sleepMillis);
      }
    }
  }

  void Game::Stop() {
    LOGI("Stop call");
    mRunning = false;
  }

  cpSpace* Game::GetPhysicalWorld() {
    return mPhysicalWorld;
  }

  // ####### Accessors (get/set) ###############################################

  bool Game::IsRunning() {
    return mRunning;
  }

  sf::RenderWindow* Game::GetWindow() {
    return mWindow;
  }

  sf::View Game::GetView() {
    return mCameraController->GetView();
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

  void Game::AddEvent(ObservableBase* event) {
    return mEventCtrl.AddEvent(event);
  }

  void Game::DestroyEvent(ObservableBase* event) {
    return mEventCtrl.DestroyEvent(event);
  }

  // ###########################################################################
  // Private / Protected Methods
  // ###########################################################################

  void Game::tick() {
    try {
      LOGD("Tick Events");
      mEventCtrl.OnTick();
      LOGD("Tick State Manager");
      mStateManager.OnTick();
      LOGD("Tick Camera");
      mCameraController->OnTick();
      LOGD("Tick Audio");
      mAudioController->OnTick();
      // LOGD("Tick Overlay");
      // if(mOverlayDisplay != nullptr) mOverlayDisplay->OnTick();
      LOGD("Tick End");
      mStateManager.OnTickEnded();
    } catch(std::exception& e) {
      LOGE("Error during tick: " << e.what());
    }
  }

  void Game::render() {
    try {
      LOGD("Set View");
      mWindow->setView(mCameraController->GetView());
      mWindow->clear(sf::Color(80, 80, 80));
      LOGD("Render State");
      mStateManager.OnRender(mWindow);
      LOGD("Render Overlay");
      if(mOverlayDisplay != nullptr) mOverlayDisplay->OnRender(mWindow);
      mWindow->display();
    } catch(std::exception& e) {
      LOGE("Error during render: " << e.what());
    }
  }

} // namespace game