# Multiple dynamic_cast

Instead of this

```c++
auto *first = dynamic_cast<derived1*>(base);
if (first) {
  first->do_smth();
} else {
  auto *second = dynamic_cast<derived2*>(base);
  if (second) {
    second->do_smth();
  } else {
    ...
  }
}
```

you could write this

```c++

auto [first, second] = auto_dynamic_cast<derived1*, derived2*>(base);

if (first) {
  first->do_smth();
} else if (second) {
  second->do_smth();
}
```

if the required type was found auto_dynamic_cast stops casting next.

For test just include

```c++
#include <auto_dynamic_cast.hpp>
```
