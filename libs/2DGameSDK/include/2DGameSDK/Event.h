
#include <SFML/Window.hpp>

namespace game {

  class Event {
  public:
    virtual ~Event();
    virtual bool Triggered();
    Event* And(Event* aEvent);
    Event* Or(Event* aEvent);
  };

  class AndEvent : public Event {
  public:
    AndEvent(Event* aEvent1, Event* aEvent2);
    virtual ~AndEvent();
    bool Triggered();

  private:
    Event* mEvent1;
    Event* mEvent2;
  };

  class OrEvent : public Event {
  public:
    OrEvent(Event* aEvent1, Event* aEvent2);
    virtual ~OrEvent();
    bool Triggered();

  private:
    Event* mEvent1;
    Event* mEvent2;
  };

  class KeyEvent : public Event {
  public:
    KeyEvent(sf::Keyboard::Key aKey);
    virtual ~KeyEvent() = default;
    virtual bool Triggered();

  private:
    sf::Keyboard::Key mKey;
  };

} // namespace game