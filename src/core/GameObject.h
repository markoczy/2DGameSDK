#include <string>

namespace game {

  class SingleTextureVisual {
    virtual void Render();
  };

  // Represents any game object
  class GameObject {
  public:
    GameObject(const std::string& type);
    virtual void Tick() = 0;
    virtual void Render() = 0;

  protected:
    std::string mType;
  };

} // namespace game