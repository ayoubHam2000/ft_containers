# Fox Test
## Usage

Go in your ft_containers' directory:

```bash
git clone https://github.com/mli42/containers_test.git
```

Put this into your MakeFile 
```
./ft_containers_fox_test/base/foxer_global.cpp
./ft_containers_fox_test/base/memory_tracker.cpp.cpp
./ft_containers_fox_test/base/statistic_tracker.cpp.cpp
./ft_containers_fox_test/MainTest.cpp
```

To make debugging and modifying tests easier, you can call mainTests from your main function. 
This will allow you to run the tests and make any necessary modifications
```C
#include "ft_containers_fox_test/foxer.h"

int main(){
	mainTests();
	return (0);
}
```

The config file
```
./config.h
```
