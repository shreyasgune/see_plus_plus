# SFML

## Setup
```
sudo apt-get install -y g++ build-essentials libsfml-dev
```
### compile
```
g++ src/*.cpp -Isrc -std=c++17 -o bin/sfmlgame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

### run
```
cd bin

./sfmlgame
```