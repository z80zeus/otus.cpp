#pragma z80

#include <string> // std::string

namespace z80 {
  template<typename inputActionType>
  class state {
    public:
    virtual ~state() = default;
    virtual void inputAction(const inputActionType& iAction) = 0;
  };
}