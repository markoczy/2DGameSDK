#include <examples.h>

using namespace std;
using namespace game;

float worldWidth = 50;
float worldHeight = 30;

int velocityIterations = 6;
int positionIterations = 2;

float groundWidth = 50;
float groundHeight = 10;
float groundX = 0;
float groundY = 0;

float boxWidth = 1;
float boxHeight = 1;
float boxX = 20;
float boxY = 20;

float getY(float hWorld, float hObject, float y) {
  return hWorld - (hObject / 2) - y;
}

class PhysicalEntity {
private:
  sf::Vector2f mWorldDimension;
  sf::Vector2f mDimension;

  cpBody* mBody;
  sf::RectangleShape* mSprite;

  sf::Vector2f getPosition() {
    auto pos = cpBodyGetPosition(mBody); //mSpace->GetPosition();
    float x = pos.x;
    float y = mWorldDimension.y - pos.y;
    return sf::Vector2f(x, y);
  };

public:
  PhysicalEntity(cpSpace* space,
                 bool isDynamic,
                 sf::Texture* texture,
                 sf::Vector2f position,
                 sf::Vector2f dimension,
                 sf::Vector2f worldDimension) : mDimension(dimension), mWorldDimension(worldDimension) {
    cpFloat mass = 1;

    if(isDynamic) {
      cpFloat moment = cpMomentForBox(mass, dimension.x, dimension.y);
      mBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    } else {
      mBody = cpSpaceGetStaticBody(space);
    }

    float posX = position.x + dimension.x / 2;
    float posY = worldDimension.y - position.y - dimension.y / 2;
    cpBodySetPosition(mBody, cpv(posX, posY));

    cpShape* shape = cpBoxShapeNew(mBody, dimension.x, dimension.y, 0);
    cpShapeSetFriction(shape, 0.3);
    cpShapeSetElasticity(shape, 0);
    cpSpaceAddShape(space, shape);

    mSprite = new sf::RectangleShape(dimension);
    mSprite->setTexture(texture);
    mSprite->setPosition(getPosition());
    mSprite->setOrigin(dimension.x / 2, dimension.y / 2);
  }

  void Update(sf::Time dt) {}

  void Render(sf::RenderTarget* target) {
    cpVect pos = cpBodyGetPosition(mBody);
    // auto pos = mBody->GetPosition();
    mSprite->setPosition(getPosition());

    auto rotRad = cpvtoangle(cpBodyGetRotation(mBody));
    float rot = -(360 * rotRad) / 6.28;
    mSprite->setRotation(rot);

    target->draw(*mSprite);
  }

  sf::Vector2f GetDimension() {
    throw std::runtime_error("nyi");
  }
};

int chipmunkDemo() {
  sf::Vector2f worldDim(worldWidth, worldHeight);
  vector<PhysicalEntity> entities;

  auto space = cpSpaceNew();
  cpSpaceSetGravity(space, cpv(0, -10));

  sf::Texture boxTexture;
  boxTexture.loadFromFile("res/textures/somebox.png");

  auto box = PhysicalEntity(space, true, &boxTexture, sf::Vector2f(20, 0), sf::Vector2f(1, 1), worldDim);
  entities.push_back(box);

  auto ground = PhysicalEntity(space, false, &boxTexture, sf::Vector2f(0, 25), sf::Vector2f(50, 10), worldDim);
  entities.push_back(ground);

  for(int i = 0; i < 20; i++) {
    auto x = rand() % 50 + 0;
    auto y = rand() % 10 + 0;

    auto ent = PhysicalEntity(space, true, &boxTexture, sf::Vector2f(x, y), sf::Vector2f(1, 1), worldDim);
    entities.push_back(ent);
  }

  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  window.setView(sf::View(sf::FloatRect(0, 0, worldWidth, worldHeight)));

  sf::Clock spawnBox;
  sf::Clock clock;
  clock.restart();

  cpSpaceSetIterations(space, 10);

  // auto timeStep = sf::seconds(1 / 60.0);
  while(window.isOpen()) {
    auto time = clock.getElapsedTime();
    clock.restart();

    // Process events
    sf::Event event;
    while(window.pollEvent(event)) {
      // Close window: exit
      if(event.type == sf::Event::Closed)
        window.close();
    }

    if(spawnBox.getElapsedTime().asMilliseconds() > 100) {
      auto x = rand() % 50 + 0;
      auto y = rand() % 10 + 0;

      auto ent = PhysicalEntity(space, true, &boxTexture, sf::Vector2f(x, y), sf::Vector2f(1, 1), worldDim);
      entities.push_back(ent);
      spawnBox.restart();
    }

    cpSpaceStep(space, time.asSeconds());

    // Clear screen
    window.clear(sf::Color::White);
    for(auto iEnt : entities) {
      iEnt.Render(&window);
    }
    // Update the window
    window.display();

    // auto sleepTime = timeStep - clock.getElapsedTime();
    // if(sleepTime > sf::Time::Zero) {
    //   std::cout << "Sleeping " << sleepTime.asMilliseconds() << std::endl;
    //   std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime.asMilliseconds()));
    // }
  }

  return 0;
}

int chipmunkDemoOld() {
  // cpVect is a 2D vector and cpv() is a shortcut for initializing them.
  cpVect gravity = cpv(0, -100);

  // Create an empty space.
  cpSpace* space = cpSpaceNew();
  cpSpaceSetGravity(space, gravity);

  // Add a static line segment shape for the ground.
  // We'll make it slightly tilted so the ball will roll off.
  // We attach it to a static body to tell Chipmunk it shouldn't be movable.
  cpShape* ground = cpSegmentShapeNew(cpSpaceGetStaticBody(space), cpv(0, 5), cpv(50, 5), 0);
  cpShapeSetFriction(ground, 1);
  cpSpaceAddShape(space, ground);

  // Now let's make a ball that falls onto the line and rolls off.
  // First we need to make a cpBody to hold the physical properties of the object.
  // These include the mass, position, velocity, angle, etc. of the object.
  // Then we attach collision shapes to the cpBody to give it a size and shape.

  cpFloat radius = 1;
  cpFloat mass = 1;

  // The moment of inertia is like mass for rotation
  // Use the cpMomentFor*() functions to help you approximate it.
  cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

  // The cpSpaceAdd*() functions return the thing that you are adding.
  // It's convenient to create and add an object in one line.
  cpBody* ballBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
  cpBodySetPosition(ballBody, cpv(20, 45));

  // Now we create the collision shape for the ball.
  // You can create multiple collision shapes that point to the same body.
  // They will all be attached to the body and move around to follow it.
  cpShape* ballShape = cpSpaceAddShape(space, cpCircleShapeNew(ballBody, radius, cpvzero));
  cpShapeSetFriction(ballShape, 0.7);

  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  window.setView(sf::View(sf::FloatRect(0, 0, worldWidth, worldHeight)));
  sf::Clock clock;
  clock.restart();

  sf::CircleShape ballVisual = sf::CircleShape(radius);
  ballVisual.setFillColor(sf::Color::Green);

  sf::RectangleShape groundVisual = sf::RectangleShape(sf::Vector2f(50, 5));

  // Now that it's all set up, we simulate all the objects in the space by
  // stepping forward through time in small increments called steps.
  // It is *highly* recommended to use a fixed size time step.
  auto timeStep = sf::seconds(1 / 60.0);
  // cpFloat timeStep = 1.0 / 60.0;

  while(window.isOpen()) {
    // Process events
    sf::Event event;
    while(window.pollEvent(event)) {
      // Close window: exit
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // Clear screen
    window.clear(sf::Color::White);

    cpVect pos = cpBodyGetPosition(ballBody);
    cpVect vel = cpBodyGetVelocity(ballBody);

    auto rot = cpBodyGetRotation(ballBody);

    printf(
        "Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
        time, pos.x, pos.y, vel.x, vel.y);

    cpSpaceStep(space, timeStep.asSeconds());

    ballVisual.setPosition(pos.x, getY(worldHeight, 10, pos.y));
    window.draw(ballVisual);
    // Update the window
    window.display();

    auto sleepTime = timeStep - clock.getElapsedTime();
    if(sleepTime > sf::Time::Zero) {
      std::cout << "Sleeping " << sleepTime.asMilliseconds() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime.asMilliseconds()));
    }
    clock.restart();
  }

  // Clean up our objects and exit!
  cpShapeFree(ballShape);
  cpBodyFree(ballBody);
  cpShapeFree(ground);
  cpSpaceFree(space);

  return 0;
}