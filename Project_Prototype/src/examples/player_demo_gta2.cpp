#include <examples.h>

using namespace std;
using namespace game;

// Type of player entity
const int _PLAYER_TYPE = 200;
static const float _OFFSET = 90;
static const int _WALK_ANIM[] = {1, 2, 1, 0, 3, 4, 3, 0};

class Gta2PlayerEntity : public AnimatedKinematicEntity {
public:
  Gta2PlayerEntity(Game* game,
                   std::map<int, sf::Texture*> animationStates,
                   float speed,
                   float rotSpeed,
                   Observable<sf::Keyboard::Key>* up,
                   Observable<sf::Keyboard::Key>* down,
                   Observable<sf::Keyboard::Key>* left,
                   Observable<sf::Keyboard::Key>* right,
                   sf::Vector2f pos = sf::Vector2f()) : AnimatedKinematicEntity(_PLAYER_TYPE, game, animationStates), mSpeed(speed), mRotSpeed(rotSpeed) {
    //
    //
    //
    mUp = new MethodObserver<sf::Keyboard::Key, Gta2PlayerEntity>(this, &Gta2PlayerEntity::MoveForward);
    mDown = new MethodObserver<sf::Keyboard::Key, Gta2PlayerEntity>(this, &Gta2PlayerEntity::MoveBackward);
    mLeft = new MethodObserver<sf::Keyboard::Key, Gta2PlayerEntity>(this, &Gta2PlayerEntity::RotLeft);
    mRight = new MethodObserver<sf::Keyboard::Key, Gta2PlayerEntity>(this, &Gta2PlayerEntity::RotRight);

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

  void MoveForward(sf::Keyboard::Key) {
    mDt += mSpeed * mDir;
  }

  void MoveBackward(sf::Keyboard::Key) {
    mDt -= mSpeed * mDir;
  }

  void RotLeft(sf::Keyboard::Key) {
    mDw -= mRotSpeed;
  }

  void RotRight(sf::Keyboard::Key) {
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
  Observer<sf::Keyboard::Key>* mUp;
  Observer<sf::Keyboard::Key>* mDown;
  Observer<sf::Keyboard::Key>* mLeft;
  Observer<sf::Keyboard::Key>* mRight;
};

int playerDemoGTA2(float zoom) {
  cout << "Start playerDemoGTA2" << endl;

  // Create game
  auto game = new Game();
  game->SetOptions(GameOptions{"My Game", sf::Vector2i(512, 512), zoom, 50});

  // Create Keyboard Events
  auto upPressed = new OnKeyPress(sf::Keyboard::Up);
  auto downPressed = new OnKeyPress(sf::Keyboard::Down);
  auto leftPressed = new OnKeyPress(sf::Keyboard::Left);
  auto rightPressed = new OnKeyPress(sf::Keyboard::Right);

  // Create Game World
  auto world = GameWorldFactory::CreateGameWorld(game, "res/testmap/tilemap.json", "", "res/testmap/tile_");
  game->SetWorld(world);

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
  auto ent = new Gta2PlayerEntity(game, animStates, 1.0, 5.0, upPressed, downPressed, leftPressed, rightPressed, sf::Vector2f(30, 30));

  // Layout entities in scene
  auto scene = new SceneGraph();
  scene->AddEntity(ent); // scene->GetRoot()->AddChild(ent);
  game->SetScene(scene);

  // Send Events to controller
  game->AddEvent(upPressed);
  game->AddEvent(downPressed);
  game->AddEvent(leftPressed);
  game->AddEvent(rightPressed);

  // Run Game
  game->Run();

  return 0;
}