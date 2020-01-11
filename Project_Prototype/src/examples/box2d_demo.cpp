#include <Box2D/Box2D.h>
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

  b2Body* mBody;
  sf::RectangleShape* mSprite;

  sf::Vector2f getPosition() {
    auto pos = mBody->GetPosition();
    float x = pos.x;
    float y = mWorldDimension.y - pos.y;
    return sf::Vector2f(x, y);
  };

public:
  PhysicalEntity(b2World* world,
                 bool isDynamic,
                 sf::Texture* texture,
                 sf::Vector2f position,
                 sf::Vector2f dimension,
                 sf::Vector2f worldDimension) : mDimension(dimension), mWorldDimension(worldDimension) {
    b2BodyDef bodyDef;
    bodyDef.type = isDynamic ? b2_dynamicBody : b2_staticBody;
    float posX = position.x + dimension.x / 2;
    float posY = worldDimension.y - position.y - dimension.y / 2;
    bodyDef.position.Set(posX, posY);
    mBody = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(dimension.x / 2, dimension.y / 2);

    if(isDynamic) {
      b2FixtureDef fixtureDef;
      fixtureDef.shape = &shape;
      fixtureDef.restitution = 0.5f;
      fixtureDef.density = 0.001f;
      fixtureDef.friction = 0.3f;
      mBody->CreateFixture(&fixtureDef);
    } else {
      mBody->CreateFixture(&shape, 0.0f);
    }

    mSprite = new sf::RectangleShape(dimension);
    mSprite->setTexture(texture);
    mSprite->setPosition(getPosition());
    mSprite->setOrigin(dimension.x / 2, dimension.y / 2);
  }

  void Update(sf::Time dt) {}

  void Render(sf::RenderTarget* target) {
    auto pos = mBody->GetPosition();
    float rot = (360 * mBody->GetAngle()) / 6.28;
    mSprite->setPosition(getPosition());
    // cout << "Angle is: " << mBody->GetAngle() << endl;
    mSprite->setRotation(-rot);

    target->draw(*mSprite);
  }

  sf::Vector2f GetDimension() {
    throw std::runtime_error("nyi");
  }
};

std::vector<b2Vec2> getShape(float width, float height) {
  std::vector<b2Vec2> ret(4);
  ret[0] = b2Vec2(0, 0);
  ret[1] = b2Vec2(width, 0);
  ret[2] = b2Vec2(width, height);
  ret[3] = b2Vec2(0, height);
  return ret;
}

int box2dDemo(int count) {
  vector<PhysicalEntity> entities;
  sf::Vector2f worldDim(worldWidth, worldHeight);
  auto world = b2World(b2Vec2(0.0f, -10.0f));

  sf::Texture boxTexture;
  boxTexture.loadFromFile("res/textures/somebox.png");

  // auto box = PhysicalEntity(space, true, &boxTexture, sf::Vector2f(20, 0), sf::Vector2f(1, 1), worldDim);
  // entities.push_back(box);

  auto ground = PhysicalEntity(&world, false, &boxTexture, sf::Vector2f(0, 25), sf::Vector2f(50, 10), worldDim);
  auto left = PhysicalEntity(&world, false, &boxTexture, sf::Vector2f(49, 0), sf::Vector2f(1, 50000), worldDim);
  auto right = PhysicalEntity(&world, false, &boxTexture, sf::Vector2f(0, 0), sf::Vector2f(1, 50000), worldDim);
  entities.push_back(ground);
  entities.push_back(left);
  entities.push_back(right);

  for(int i = 0; i < count; i++) {
    auto x = rand() % 48 + 1;
    auto y = rand() % 5 + 0;

    auto ent = PhysicalEntity(&world, true, &boxTexture, sf::Vector2f(x, y), sf::Vector2f(0.5, 0.5), worldDim);
    entities.push_back(ent);
  }

  sf::RenderWindow window(sf::VideoMode(800, 600), "Box2DTest");
  window.setView(sf::View(sf::FloatRect(0, 0, worldWidth, worldHeight)));

  sf::Clock spawnBox;
  sf::Clock clock;
  sf::Clock bmClock;
  clock.restart();

  // auto timeStep = sf::seconds(1 / 60.0);
  int ticks = 0;

  while(window.isOpen()) {
    auto time = clock.getElapsedTime();
    clock.restart();

    auto bmTime = bmClock.getElapsedTime();
    if(bmTime >= sf::seconds(1)) {
      cout << "FPS: " << ticks << endl;
      ticks = 0;
      bmClock.restart();
    }

    // Process events
    sf::Event event;
    while(window.pollEvent(event)) {
      // Close window: exit
      if(event.type == sf::Event::Closed)
        window.close();
    }

    world.Step(time.asSeconds(), 1, 1);
    ticks++;

    // Clear screen
    window.clear(sf::Color::White);
    for(auto iEnt : entities) {
      iEnt.Render(&window);
    }
    // Update the window
    window.display();
  }

  return 0;
}

int box2dDemoNewer() {
  sf::Vector2f worldDim(worldWidth, worldHeight);
  auto world = b2World(b2Vec2(0.0f, -10.0f));
  vector<PhysicalEntity> entities;

  sf::Texture boxTexture;
  boxTexture.loadFromFile("res/textures/somebox.png");

  auto box = PhysicalEntity(&world, true, &boxTexture, sf::Vector2f(20, 0), sf::Vector2f(1, 1), worldDim);
  entities.push_back(box);

  auto ground = PhysicalEntity(&world, false, &boxTexture, sf::Vector2f(0, 25), sf::Vector2f(50, 10), worldDim);
  entities.push_back(ground);

  for(int i = 0; i < 20; i++) {
    auto x = rand() % 50 + 0;
    auto y = rand() % 10 + 0;

    auto ent = PhysicalEntity(&world, true, &boxTexture, sf::Vector2f(x, y), sf::Vector2f(1, 1), worldDim);
    entities.push_back(ent);
  }

  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  window.setView(sf::View(sf::FloatRect(0, 0, worldWidth, worldHeight)));

  sf::Clock spawnBox;
  sf::Clock clock;
  clock.restart();
  while(window.isOpen()) {
    auto time = clock.getElapsedTime();
    clock.restart();
    world.Step(time.asSeconds(), velocityIterations, positionIterations);

    if(spawnBox.getElapsedTime().asMilliseconds() > 100) {
      auto x = rand() % 50 + 0;
      auto y = rand() % 10 + 0;

      auto ent = PhysicalEntity(&world, true, &boxTexture, sf::Vector2f(x, y), sf::Vector2f(1, 1), worldDim);
      entities.push_back(ent);
      spawnBox.restart();
    }

    // Process events
    sf::Event event;
    while(window.pollEvent(event)) {
      // Close window: exit
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // Clear screen
    window.clear(sf::Color::White);
    for(auto iEnt : entities) {
      iEnt.Render(&window);
    }
    // Update the window
    window.display();
  }

  return 0;
}

int box2dDemoOld() {
  // Define the gravity vector.
  b2Vec2 gravity(0.0f, -10.0f);

  // Construct a world object, which will hold and simulate the rigid bodies.
  b2World world(gravity);

  // Define the ground body.
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(groundX, groundY);

  // Call the body factory which allocates memory for the ground body
  // from a pool and creates the ground box shape (also from a pool).
  // The body is also added to the world.
  b2Body* groundBody = world.CreateBody(&groundBodyDef);

  // Define the ground box shape.
  b2PolygonShape groundBox;

  // The extents are the half-widths of the box.
  groundBox.SetAsBox(groundWidth / 2, groundHeight / 2);
  // Add the ground fixture to the ground body.
  groundBody->CreateFixture(&groundBox, 0.0f);

  // auto ground = sf::Sprite();
  sf::RectangleShape ground;
  ground.setFillColor(sf::Color::Green);
  ground.setSize(sf::Vector2f(groundWidth, groundHeight));
  // ground.setPosition(groundX, groundY);

  // Define the dynamic body. We set its position and call the body factory.
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(boxX, boxY);
  b2Body* boxBody = world.CreateBody(&bodyDef);

  // Define another box shape for our dynamic body.
  b2PolygonShape dynamicBox;
  auto boxShape = getShape(boxWidth, boxHeight);
  dynamicBox.SetAsBox(boxWidth / 2, boxHeight / 2);
  // Define the dynamic body fixture.
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  // fixtureDef.restitution = 1;
  // Set the box density to be non-zero, so it will be dynamic.
  fixtureDef.density = 1.0f;
  // Override the default friction.
  fixtureDef.friction = 0.3f;
  // Add the shape to the body.
  boxBody->CreateFixture(&fixtureDef);

  sf::RectangleShape box;
  box.setFillColor(sf::Color::Blue);
  box.setSize(sf::Vector2f(boxWidth, boxHeight));

  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
  window.setView(sf::View(sf::FloatRect(0, 0, worldWidth, worldHeight)));

  sf::Clock clock;
  clock.restart();

  sf::CircleShape groundZero = sf::CircleShape(0.5);
  groundZero.setFillColor(sf::Color::Magenta);
  sf::CircleShape boxZero = sf::CircleShape(0.5);
  boxZero.setFillColor(sf::Color::Magenta);

  // Start the game loop
  while(window.isOpen()) {
    auto time = clock.getElapsedTime();
    clock.restart();
    world.Step(time.asSeconds(), velocityIterations, positionIterations);

    // Process events
    sf::Event event;
    while(window.pollEvent(event)) {
      // Close window: exit
      if(event.type == sf::Event::Closed)
        window.close();
    }

    auto groundPos = groundBody->GetPosition();
    ground.setPosition(groundPos.x, getY(worldHeight, groundHeight, groundPos.y));
    groundZero.setPosition(groundPos.x, getY(worldHeight, groundHeight, groundPos.y));

    auto boxPos = boxBody->GetPosition();
    auto boxAngle = boxBody->GetAngle();
    box.setPosition(boxPos.x, getY(worldHeight, boxHeight, boxPos.y));
    boxZero.setPosition(boxPos.x, getY(worldHeight, boxHeight, boxPos.y));

    // Clear screen
    window.clear(sf::Color::White);
    // Draw the sprite
    window.draw(ground);
    window.draw(groundZero);
    window.draw(box);
    window.draw(boxZero);
    // Update the window
    window.display();

    printf("%4.2f %4.2f\n", groundPos.x, groundPos.y);
    printf("%4.2f %4.2f %4.2f\n", boxPos.x, boxPos.y, boxAngle);
  }

  return 0;
}