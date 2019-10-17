#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;
static const float _OFFSET = 90;
static const int _WALK_ANIM[] = {1, 2, 1, 0, 3, 4, 3, 0};

class Gta2PlayerEntity : public AnimatedTransformableEntity {
public:
  Gta2PlayerEntity(std::map<int, sf::Texture*> animationStates,
                   float speed,
                   float rotSpeed,
                   Observable<EmptyEventData>* up,
                   Observable<EmptyEventData>* down,
                   Observable<EmptyEventData>* left,
                   Observable<EmptyEventData>* right,
                   sf::Vector2f pos = sf::Vector2f()) : AnimatedTransformableEntity(_PLAYER_TYPE, animationStates), mSpeed(speed), mRotSpeed(rotSpeed) {
    //
    //
    //
    mUp = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::MoveForward);
    mDown = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::MoveBackward);
    mLeft = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::RotLeft);
    mRight = new MethodObserver<EmptyEventData, Gta2PlayerEntity>(this, &Gta2PlayerEntity::RotRight);

    mUp->SubscribeTo(up);
    mDown->SubscribeTo(down);
    mLeft->SubscribeTo(left);
    mRight->SubscribeTo(right);

    SetAnimState(1);
    auto rect = mCurState.getTextureRect();
    mCenter = sf::Vector2f(rect.width / 2, rect.height / 2);

    SetTransform(sf::Transform().translate(pos));
    mDir = sf::Vector2f(0, -1);
  }

  void OnTick() {
    sf::Transform transform;
    if(mDw != 0) {
      transform.rotate(mDw, mCenter);
      mAngle += mDw;
    } else if(mDt.x != 0 || mDt.y != 0) {
      transform.translate(mDt);

      // walk animation
      SetAnimState(_WALK_ANIM[mCurWalk]);
      mCurSkip++;
      if(mCurSkip == 5) {
        mCurWalk++;
        mCurSkip = 0;
      }
      if(mCurWalk >= 8) {
        mCurWalk = 0;
      }
    } else {
      SetAnimState(0);
    }
    Transform(transform);
    mDt = sf::Vector2f();
    mDw = 0.0;
  }

  void MoveForward(EmptyEventData*) {
    mDt += mSpeed * mDir;
  }

  void MoveBackward(EmptyEventData*) {
    mDt -= mSpeed * mDir;
  }

  void RotLeft(EmptyEventData*) {
    mDw -= mRotSpeed;
  }

  void RotRight(EmptyEventData*) {
    mDw += mRotSpeed;
  }

private:
  sf::Vector2f mCenter;
  int mCurWalk = 0;
  int mCurSkip = 0;
  float mSpeed, mRotSpeed;
  // Delta Transform of current tick
  sf::Vector2f mDt = sf::Vector2f();
  // Delta Rotation of current tick
  float mDw = 0;

  float mAngle;
  sf::Vector2f mDir;

  // Needed for cleanup
  Observer<EmptyEventData>* mUp;
  Observer<EmptyEventData>* mDown;
  Observer<EmptyEventData>* mLeft;
  Observer<EmptyEventData>* mRight;
};

int playerDemoGTA2(float zoom) {
  cout << "Start playerDemoGTA2" << endl;

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld("res/testmap/tilemap.json", "", "res/testmap/tile_");

  // Create Player entity and Rotating child entity
  auto idle = AssetManager::GetTexture("res/textures/gunner/gunner_idle.png");
  auto walk0 = AssetManager::GetTexture("res/textures/gunner/gunner_walk0.png");
  auto walk1 = AssetManager::GetTexture("res/textures/gunner/gunner_walk1.png");
  auto walk2 = AssetManager::GetTexture("res/textures/gunner/gunner_walk2.png");
  auto walk3 = AssetManager::GetTexture("res/textures/gunner/gunner_walk3.png");

  map<int, sf::Texture*> animStates;
  animStates[0] = idle;
  animStates[1] = walk0;
  animStates[2] = walk1;
  animStates[3] = walk2;
  animStates[4] = walk3;
  auto ent = new Gta2PlayerEntity(animStates, 1.0, 5.0, upPressed, downPressed, leftPressed, rightPressed, sf::Vector2f(30, 30));

  // Layout entities in scene
  auto scene = new SceneGraph();
  scene->AddEntity(ent); // scene->GetRoot()->AddChild(ent);

  // Create game
  GameOptions options{"My Game", sf::Vector2i(512, 512), zoom, 50};
  auto app = new Game(options, scene, world);

  // Send Events to controller
  app->AddEvent(upPressed);
  app->AddEvent(downPressed);
  app->AddEvent(leftPressed);
  app->AddEvent(rightPressed);

  // Run Game
  app->Run();

  return 0;
}