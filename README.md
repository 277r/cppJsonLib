# 277r/json
### a simple c++ library for simple json things, not intended for very big stuff

```cpp
#include "json.cpp"
using namespace json;
using namespace std;

jsonObj data;
// load json string and store in data
data.fromString(R"({"age":3,"hee":"HEE","parents":{"age":4,"age":-22}})");

// change age
data["age"] = "23943"; 
// get 2nd object
cout << data[1];
// get string
cout << data.toString();

// clear entire object
data.setSize(0);

```


### TODO:
- more dynamic size, so we can expand an array while filling it instead of setting the size then filling it
- fix segfaulting issue when going out of reach because of incorrect json
- more/better operators (not needed but very useful)


#### this project was made for fun and i was bored, feel free to use this, this project isn't meant for anyone to actually be used and may not comply with the JSON standard, i'm not responsible for anything

#### this should be usable for simple server side applications (even though something better could be made in c which probably has better performance), but i don't think anyone should use it
