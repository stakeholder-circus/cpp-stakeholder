# C++ Docker

## Build and test
- `docker build -t cpp-stakeholder .`
- `docker run --rm cpp-stakeholder --list-values`
- `docker run --rm cpp-stakeholder --output-format json --focus-family code_analyzer --seed 123`

## Rationale
- The builder stage compiles and tests the C++17 binary before packaging it into a small Alpine runtime image.
- Docker is the reproducible Linux gate; host checks still cover local compiler behavior.
