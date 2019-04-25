#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include "ObservableBase.h"
#include "event/observer/Observer.h"
#include "gamesdk_dll.h"
#include <iostream>
#include <vector>

namespace game {

  template <class TData>
  class GAMESDK_DLL Observable : public ObservableBase {
  public:
    // void Emit(TData* data);
    void Subscribe(Observer<TData>* subscriber);
    virtual void Update();

  protected:
    virtual TData triggered(bool* trigger) = 0;

  private:
    std::vector<Observer<TData>*> mObservers;
  };

} // namespace game

#endif