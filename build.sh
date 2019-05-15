g++ -c main.cpp
FILES=(InputManager Renderer Ship Bullet)
OBJS=()
for f in "${FILES[@]}"; do
  g++ -c "$f.cpp"
  OBJS+=("$f.o")
done
g++ main.o "${OBJS[@]}" -o asteroids -lSDL2 -lSDL2_image
