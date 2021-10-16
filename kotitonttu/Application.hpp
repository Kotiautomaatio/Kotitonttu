#ifndef KOTITONTTU_APPLICATION_HPP
#define KOTITONTTU_APPLICATION_HPP

namespace kotitonttu {

class Application {

public:

  virtual void run() = 0;
  virtual void parseArguments() = 0;
};
} // namespace kotitonttu

#endif // KOTITONTTU_APPLICATION_HPP
