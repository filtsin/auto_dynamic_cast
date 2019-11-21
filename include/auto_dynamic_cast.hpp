#pragma once

#include <type_traits>
#include <tuple>

// Would not hurt add specialization for smart_pointers
// with support of dynamic_pointer_cast
template <typename T>
class choose {
public:
  explicit choose(T o) : obj(o) {}

  template <typename ...Types>
  std::tuple<Types...> match() const {
    std::tuple<Types...> result;
    match_private<0, sizeof...(Types), Types...>(result);
    return result;
  }

private:

  template <int Index, int Count, typename ...Types>
  typename std::enable_if<Index < Count, void>::type
  match_private(std::tuple<Types...> &tuple) const {
    using tuple_t = typename std::tuple_element<Index, std::tuple<Types...>>::type;

    auto *cast = dynamic_cast<tuple_t>(obj);
    if (cast != nullptr) {
      std::get<Index>(tuple) = cast;
    } else {
      match_private<Index + 1, Count, Types...>(tuple);
    }
  }

  template <int Index, int Count, typename ...Types>
  typename std::enable_if<Index == Count, void>::type
  match_private(std::tuple<Types...> &tuple) const
  {}

  T obj;
};

template <typename ...Types, typename T>
auto auto_dynamic_cast(T obj) {
  return choose<T>(obj).template match<Types...>();
}