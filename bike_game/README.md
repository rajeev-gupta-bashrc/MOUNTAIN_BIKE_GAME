## Mountain Bike Game

A small CMake-based project showcasing a simple, fun bike game and serving as a foundation for CI/CD experiments.

### Prerequisites (Ubuntu)
```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev fonts-dejavu-core
```

### Clone the repository
```bash
git clone git@github.com:rajeev-gupta-bashrc/MOUNTAIN_BIKE_GAME.git
```

### Build
```bash
cd MOUNTAIN_BIKE_GAME
cmake -S ./bike_game -B ./bike_game/build
cmake --build ./bike_game/build -j
```

### Run
```bash
cd ./bike_game/build
./BikeRiderGame
```
```

- Updated wording for clarity and brevity; kept commands intact and corrected the run path to `./bike_game/build`.