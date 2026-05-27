# 🔄 **Luồng Chạy Của Project Tetris**

## **Sơ đồ luồng chính**

```
main()
  ↓
Game::init()
  ├─ Board::init() → Khởi tạo bảng chơi 20x15 với border
  ├─ Block::spawn() → Tạo khối random đầu tiên
  └─ lastFallTime = chrono::now() → Bắt đầu timer
  ↓
Game::run() → GAME LOOP
  ├─ while(isRunning)
  │   ├─ Game::update()
  │   │   ├─ handleInput() → Xử lý phím bấm
  │   │   └─ dropBlock() → Khối tự rơi
  │   ├─ Game::render()
  │   │   └─ Board::draw() → Vẽ board ra console
  │   └─ sleep_ms(16) → ~60 FPS
  │
  └─ GAME OVER → Hiển thị điểm cuối
```

---

## **Chi tiết từng bước**

### **1. Khởi tạo (Initialization)**

#### `Game::init()`
- Gọi `Board::init()`: 
  - Khởi tạo grid 20x15
  - Set border (#) ở các cạnh
  - Các ô bên trong là trống (' ')
- Gọi `Block::spawn()`:
  - Chọn type random (0-6)
  - Load shape từ mảng blocks
  - Set position (5, 0) - trên cùng giữa
- Set `isRunning = true`
- Lưu thời gian bắt đầu: `lastFallTime`

```cpp
Board: grid[20][15] = {
  '#','#','#',...'#',
  '#',' ',' ',...'#',
  ...
  '#','#','#',...'#'
}
```

---

### **2. Game Loop (Vòng lặp chính)**

#### **A. Input Handling** (`handleInput()`)
```
if (kbhit()) → Có phím được nhấn?
  ├─ 'A' → Move left: canMove(-1, 0)?
  ├─ 'D' → Move right: canMove(1, 0)?
  ├─ 'W' → Rotate: canRotate()?
  ├─ 'X' → Fast fall: canMove(0, 1)?
  └─ 'Q' → Quit game
```

**Luồng di chuyển:**
1. `Board::removeBlock()` → Xóa khối khỏi grid
2. `Board::canMove()` → Kiểm tra va chạm
3. `Board::placeBlock()` → Đặt khối lại vào grid

#### **B. Drop Block** (`dropBlock()`)
```
elapsed_time = now() - lastFallTime

if (elapsed_time >= fallSpeed) {
  ├─ removeBlock() → Xóa khối hiện tại
  ├─ canMove(0, 1)? → Có thể rơi thêm?
  │   ├─ Có: blockY++ → Tăng y-position
  │   └─ Không: lockBlock() → Khóa khối
  ├─ placeBlock() → Vẽ khối mới
  └─ lastFallTime = now() → Reset timer
}
```

**Tốc độ rơi:**
- Ban đầu: 200ms (fallSpeed = 200)
- Khi score ≥ 1000: 150ms (tăng tốc)

#### **C. Lock Block** (`lockBlock()`)
```
Board::clearLine() → Xóa dòng đầy
  ├─ Kiểm tra từng dòng (i = HEIGHT-2 đến 1)
  ├─ fullLine = true?
  │   ├─ Di chuyển các dòng phía trên xuống
  │   ├─ Xóa dòng trên cùng
  │   ├─ Cộng điểm (100/300/500/800)
  │   └─ Vẽ lại board
  └─ updateFallSpeed() → Tăng tốc nếu cần

Block::spawn() → Tạo khối mới
  ├─ Random type
  ├─ Set position (5, 0)
  └─ Copy shape vào currentBlock

isGameOver()? → Kiểm tra va chạm ngay
  ├─ Nếu không thể spawn: Game Over
  └─ Nếu được: tiếp tục chơi
```

#### **D. Render** (`render()`)
```
Board::draw()
  ├─ system("cls") → Clear console
  ├─ Vẽ border trên: ╔════════════╗
  ├─ Vẽ từng hàng board
  │   ├─ ║ (border trái)
  │   ├─ Từng ô: ■ (có khối) hoặc "  " (trống)
  │   └─ ║ (border phải)
  ├─ Vẽ border dưới: ╚════════════╝
  └─ Hiển thị Score
```

---

### **3. Game Over**

```
isGameOver() = true

  ├─ system("cls")
  ├─ Hiển thị:
  │   ╔════════════════════╗
  │   ║     GAME OVER!     ║
  │   ╚════════════════════╝
  │   Final Score: XXX
  └─ Thoát vòng lặp
```

---

## **Class Architecture**

### **Block (Block.h/cpp)**
```cpp
class Block {
  int type;                    // 0-6 (I, O, T, S, Z, J, L)
  char shape[4][4];            // Hình dạng khối hiện tại
  char blocks[7][4][4];        // 7 loại khối
  
  void spawn();                // Tạo khối mới
  void rotate();               // Xoay 90 độ
}
```

**Các khối:**
- **I**: Thẳng (4 ngang)
- **O**: Vuông 2x2
- **T**: Hình T
- **S**: Hình S
- **Z**: Hình Z
- **J**: Hình J
- **L**: Hình L

### **Board (Board.h/cpp)**
```cpp
class Board {
  char grid[20][15];           // Bảng chơi
  int score;                   // Điểm số
  int fallSpeed;               // Tốc độ rơi (ms)
  
  // Quản lý khối
  void placeBlock(x, y);       // Đặt khối vào grid
  void removeBlock(x, y);      // Xóa khối khỏi grid
  
  // Kiểm tra va chạm
  bool canMove(x, y, dx, dy);  // Có thể di chuyển?
  bool canRotate(x, y);        // Có thể xoay?
  bool isGameOver(x, y);       // Trò chơi kết thúc?
  
  // Vẽ và xóa
  void draw();                 // Vẽ board ra console
  void clearLine();            // Xóa dòng đầy
}
```

### **Game (Game.h/cpp)**
```cpp
class Game {
  Board board;                 // Bảng chơi
  Block currentBlock;          // Khối hiện tại
  int blockX, blockY;          // Vị trí khối
  bool isRunning;              // Game đang chạy?
  
  void init();                 // Khởi tạo
  void run();                  // Game loop
  void update();               // Cập nhật logic
  void handleInput();          // Xử lý input
  void render();               // Vẽ lên màn hình
  
  void spawnNewBlock();        // Tạo khối mới
  void dropBlock();            // Khối rơi
  void lockBlock();            // Khóa khối
}
```

---

### **canMove(x, y, dx, dy)**
Kiểm tra xem khối có thể di chuyển không:

```cpp
for (i=0; i<4; i++)
  for (j=0; j<4; j++)
    if (block.shape[i][j] != ' ') {
      newRow = y + i + dy
      newCol = x + j + dx
      
      // Kiểm tra ranh giới
      if (newRow < 0 || newRow >= HEIGHT) return false
      if (newCol < 0 || newCol >= WIDTH) return false
      
      // Kiểm tra va chạm với khối khác
      if (grid[newRow][newCol] != ' ') return false
    }
return true
```

### **canRotate(x, y)**
Tương tự như canMove nhưng kiểm tra shape quay 90 độ:

```cpp
char temp[4][4]
for (i=0; i<4; i++)
  for (j=0; j<4; j++)
    temp[i][j] = block.shape[3-j][i]  // Quay 90 độ

// Kiểm tra như canMove với temp shape
```

---

## **Scoring System**

| Dòng xóa | Điểm | Ghi chú |
|----------|------|--------|
| 1 dòng   | 100  | -      |
| 2 dòng   | 300  | Combo |
| 3 dòng   | 500  | Combo |
| 4 dòng   | 800  | Combo |

**Tăng tốc độ:**
- Score < 1000: fallSpeed = 200ms
- Score ≥ 1000: fallSpeed = 150ms

---

## **Timing (Cross-Platform)**

```cpp
// Windows
Sleep(ms);
---

## **Input Handling**

```cpp
// Windows
kbhit()  → _kbhit()
getch()  → _getch()

// Terminal mode (Unix)
setupTerminal()    → Disable canonical mode (raw input)
restoreTerminal()  → Restore normal mode
```

## **Key Functions Call Order**

```
main()
 └─ Game::run()
     ├─ Game::init()
     │  ├─ Board::init()
     │  └─ Block::spawn()
     │
     └─ while(isRunning)
        ├─ Game::update()
        │  ├─ Game::handleInput()
        │  │  ├─ Board::removeBlock()
        │  │  ├─ Board::canMove()
        │  │  └─ Board::placeBlock()
        │  │
        │  └─ Game::dropBlock()
        │     ├─ Board::removeBlock()
        │     ├─ Board::canMove()
        │     ├─ Board::placeBlock()
        │     └─ Game::lockBlock()
        │        ├─ Board::clearLine()
        │        ├─ Block::spawn()
        │        └─ Board::isGameOver()
        │
        └─ Game::render()
           └─ Board::draw()
```

---

## **Compile & Run**

```bash
# Compile
g++ -std=c++11 tetris.cpp Block.cpp Board.cpp Game.cpp -o tetris

# Run
tetris.exe            # Windows
```

---

## **Controls Reference**

| Phím | Hành động |
|------|-----------|
| `A`  | Di chuyển trái |
| `D`  | Di chuyển phải |
| `W`  | Xoay khối |
| `X`  | Rơi nhanh |
| `Q`  | Thoát game |

---

**End of Flow Documentation** 📄
