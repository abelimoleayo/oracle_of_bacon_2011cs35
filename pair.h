#ifndef PAIR_H_
#define PAIR_H_

/**
 * A Pair is an abstract container class for two pieces of data, which it
 * stores publicly.  
 */
template <typename F, typename S>
class Pair {
  public:
    F first;   // The first item in the pair.
    S second;  // The second item in the pair.
   
    Pair() {};
    Pair(F f, S s) {first = f; second = s;};
    bool operator==(Pair &other) {
      if (first == other.first && second == other.second) {
        return true;
      } else {
        return false;
      }
    }
};

#endif
