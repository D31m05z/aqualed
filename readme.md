--------
checkout
--------
git clone https://github.com/d31m05z/aqualed.git
cd aqualed
git submodule update --init

------------
requirements
------------
 - cmake
 TODO: dev packages


--------------
build 3rdparty
--------------

Navigate to 3rdparty folder and call build.sh script.

```
cd 3rdparty
./build.sh
```

-------------
build project
-------------

You should to go to the root project folder and call build.sh script with correct CMAKE_PREFIX_PATH parameter.

```
CMAKE_PREFIX_PATH=$PWD/3rdparty/install ./build.sh
```

