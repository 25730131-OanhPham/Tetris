# 🎮 **Game Tetris Console - Project Documentation**

## 📖 **Giới thiệu dự án**

Dự án này là implement **Tetris - trò chơi kinh điển** bằng **C++** với **kiến trúc OOP** (Object-Oriented Programming). Mục tiêu của dự án là:

✅ Xây dựng game Tetris hoàn chỉnh chạy trên console  
✅ Áp dụng **OOP principles** với 3 class chính: `Block`, `Board`, `Game`   
✅ Quản lý **scoring system** với điểm tăng theo số dòng xóa  
✅ Rèn luyện kỹ năng **lập trình hướng đối tượng** và **quản lý bộ nhớ**

---

## 🏗️ **Kiến trúc Project**

### **Class Diagram**

```
┌─────────────────────────────────────────────────────┐
│                    Game                             │
│  - Board board                                      │
│  - Block currentBlock                               │
│  - int blockX, blockY                               │
│  - void run(), update(), handleInput(), render()    │
└─────────────────────────────────────────────────────┘
        │                              │
        └──────────────┬───────────────┘
                       │
        ┌──────────────┴──────────────┐
        ▼                             ▼
┌──────────────────┐         ┌──────────────────┐
│      Block       │         │      Board       │
│  - int type      │         │  - char grid[][] │
│  - char shape[][]│         │  - int score     │
│  - spawn()       │         │  - placeBlock()  │
│  - rotate()      │         │  - canMove()     │
│                  │         │  - draw()        │
└──────────────────┘         │  - clearLine()   │
                             └──────────────────┘
```

### **File Structure**

```
Tetris/
├── Block.h, Block.cpp          # Class quản lý khối Tetris
├── Board.h, Board.cpp          # Class quản lý bảng chơi
├── Game.h, Game.cpp            # Class quản lý game loop
├── tetris.cpp                  # Entry point (main function)
├── README.md                   # Tài liệu dự án (file này)
├── FLOW.md                     # Chi tiết luồng chạy
└── .vscode/tasks.json          # Cấu hình compile (VSCode)
```

---

## 📋 **Chi tiết các Class**

### **1. Block Class** (Block.h/cpp)

**Chức năng:** Quản lý các khối Tetris

```cpp
class Block {
private:
    int type;              // 0-6 (I, O, T, S, Z, J, L)
    char shape[4][4];      // Hình dạng hiện tại
    char blocks[7][4][4];  // 7 loại khối Tetris

public:
    Block();               // Constructor
    void spawn();          // Tạo khối random
    void rotate();         // Xoay khối 90 độ
}
```

**7 Loại khối:**

```
I-Block       O-Block       T-Block       S-Block
  ■             ■ ■           ■           ■ ■
  ■             ■ ■         ■ ■ ■       ■ ■
  ■                           
  ■                         Z-Block       J-Block       L-Block
                          ■ ■             ■             ■
                            ■ ■         ■ ■ ■       ■ ■ ■
                                          ■               ■
```

### **2. Board Class** (Board.h/cpp)

**Chức năng:** Quản lý bảng chơi, va chạm, vẽ UI

```cpp
class Board {
private:
    static const int HEIGHT = 20;
    static const int WIDTH = 15;
    char grid[HEIGHT][WIDTH];  // Grid chính
    int score;                 // Điểm số
    int fallSpeed;             // Tốc độ rơi (ms)

public:
    // Quản lý khối
    void placeBlock(int x, int y, const Block& block);
    void removeBlock(int x, int y, const Block& block);
    
    // Collision detection
    bool canMove(int x, int y, const Block& block, int dx, int dy);
    bool canRotate(int x, int y, const Block& block);
    bool isGameOver(int x, int y, const Block& block);
    
    // Game logic
    void clearLine();          // Xóa dòng đầy
    void draw() const;         // Vẽ board
    void updateFallSpeed();    // Tăng tốc độ
}
```

**Kích thước Board:** 15 cột × 20 hàng  
**Border:** `#` ở cạnh (không vẽ trực tiếp mà check trong canMove)  
**Display:** `■` cho khối, `  ` cho ô trống

### **3. Game Class** (Game.h/cpp)

**Chức năng:** Game loop chính, xử lý input, điều phối logic

```cpp
class Game {
private:
    Board board;           // Bảng chơi
    Block currentBlock;    // Khối hiện tại
    int blockX, blockY;    // Vị trí khối
    bool isRunning;        // Trạng thái game

public:
    void init();           // Khởi tạo
    void run();            // Game loop (~60 FPS)
    void update();         // Cập nhật logic
    void handleInput();    // Xử lý phím bấm
    void render();         // Vẽ lên console
    
    void spawnNewBlock();  // Tạo khối mới
    void dropBlock();      // Khối rơi tự động
    void lockBlock();      // Khóa khối
}
```

---

## ⚙️ **Hướng dẫn Cài đặt & Chạy**

### **Yêu cầu:**
- **Compiler:** g++ với support C++11 trở lên
- **OS:** Windows (chính), macOS/Linux (test)

### **Bước 1: Clone repository**

```bash
git clone https://github.com/25730162/Tetris.git
cd Tetris
```

### **Bước 2: Compile**

```bash
# Cách 1: g++ từ terminal
g++ -std=c++11 tetris.cpp Block.cpp Board.cpp Game.cpp -o tetris

# Cách 2: VS Code
Nhấn Ctrl+Shift+B (hoặc F5 → Run)
```

### **Bước 3: Chạy game**

```bash
# macOS/Linux
./tetris

# Windows
tetris.exe
```

---

## 🎮 **Cách chơi**

| Phím | Hành động |
|------|-----------|
| `A` | Di chuyển khối sang trái |
| `D` | Di chuyển khối sang phải |
| `W` | Xoay khối 90 độ |
| `X` | Khối rơi nhanh |
| `Q` | Thoát game |

### **Mục tiêu:**
- Xếp các khối để tạo thành dòng ngang đầy đủ
- Dòng đầy sẽ tự động xóa → Cộng điểm
- Game kết thúc khi khối mới không thể spawn được

### **Scoring:**
- 1 dòng: 100 điểm
- 2 dòng: 300 điểm
- 3 dòng: 500 điểm
- 4 dòng: 800 điểm (Tetris!)

---

## 🔄 **Luồng Chạy Game**

```
Khởi tạo (Game::init)
  ├─ Board::init() → Tạo bảng 20×15
  └─ Block::spawn() → Tạo khối đầu tiên
    ↓
Game Loop (Game::run)
  ├─ Game::handleInput() → Xử lý phím (A/D/W/X/Q)
  ├─ Game::dropBlock() → Khối rơi tự động
  ├─ Board::clearLine() → Xóa dòng đầy
  ├─ Game::render() → Vẽ board ra console
  └─ Repeat (~60 FPS)
    ↓
Game Over
  ├─ Khối không thể spawn
  ├─ Hiển thị Final Score
  └─ Thoát game
```

**Chi tiết:** Xem file `FLOW.md` để biết thêm.

---

## 💻 **Cross-Platform Support**

Code hỗ trợ chạy trên nhiều hệ điều hành:

```cpp
#ifdef _WIN32
    // Windows: Sleep(), _kbhit(), _getch()
#else
    // macOS/Linux: usleep(), select(), getchar()
    // Terminal mode: termios
#endif
```

**Deployment Windows:** Chỉ cần g++ compiler trên Windows  
**Test macOS:** Code tự động detect OS và dùng system call phù hợp

---

## 🛠️ **Tech Stack**

| Công nghệ | Mục đích |
|-----------|---------|
| **C++11** | Ngôn ngữ lập trình |
| **OOP** | Kiến trúc (Block, Board, Game) |
| **std::chrono** | Timer chính xác |
| **Console API** | Vẽ UI (cls, system calls) |
| **Cross-platform** | Windows/macOS/Linux |

---

## 📊 **Project Structure Diagram**

```
Game::run()
  │
  ├─→ Game::update()
  │    ├─→ handleInput()
  │    │    ├─ Board::removeBlock()
  │    │    ├─ Board::canMove()
  │    │    └─ Board::placeBlock()
  │    │
  │    └─→ dropBlock()
  │         ├─ Board::removeBlock()
  │         ├─ Board::canMove()
  │         ├─ Board::placeBlock()
  │         └─ lockBlock()
  │              ├─ Board::clearLine()
  │              ├─ Block::spawn()
  │              └─ Board::isGameOver()
  │
  └─→ Game::render()
       └─ Board::draw()
```

---

## 🎯 **Learning Outcomes**

✅ **OOP Design:** Tách logic thành 3 class độc lập  
✅ **Collision Detection:** Kiểm tra va chạm chính xác  
✅ **Game Loop:** ~60 FPS render với ~200ms block fall  
✅ **Cross-platform:** Conditional compilation dựa trên OS  
✅ **Console UI:** Vẽ trực tiếp lên terminal  
✅ **Memory Management:** Quản lý array, objects, pointers  
✅ **Git Workflow:** Version control, branching, push

---

## 📝 **Development Notes**

- **Board size:** 15×20 (WIDTH × HEIGHT)
- **Block types:** 7 (I, O, T, S, Z, J, L) + rotation
- **Input:** Non-blocking (kbhit + getch pattern)
- **Timing:** std::chrono::steady_clock (high precision)
- **Scoring:** Bội số của 100 (100, 300, 500, 800)
- **Speed:** 200ms default, 150ms khi score ≥ 1000

---

## 👨‍💼 **Author & Submission**

- **Project:** SS004.F21.CNTT - Game Tetris Console
- **GitHub:** https://github.com/25730162/Tetris
- **Language:** C++ (C++11 standard)
- **Status:** ✅ Complete (OOP refactored)

---

## 📖 **Documentation Files**

- **README.md** - Giới thiệu & hướng dẫn (file này)
- **FLOW.md** - Chi tiết luồng chạy & function calls
- **.vscode/tasks.json** - Cấu hình compile

---

**Happy Tetris! 🎮**

⬆️ Xoay khối để thay đổi hình dạng.

🏆 Xếp đầy một hàng để ghi điểm.

❌ Trò chơi kết thúc khi khối chạm đỉnh bảng.

# 👥 Phân công nhóm #
 **Vương & Tuấn**  
  - Phụ trách làm hợp đồng và viết báo cáo (2 người phối hợp).
  - Vương: Viết và hoàn thiện phần README, tài liệu hướng dẫn.

 **Quý**  
  - Viết hàm `removeline` để xử lý xóa hàng.  
  - Cài đặt tốc độ rơi của khối.

**Khôi**  
  - Viết hàm `block` để quản lý khối.  
  - Cài đặt chức năng xoay khối.

# 📌 Ý nghĩa dự án
Dự án không chỉ tạo ra một trò chơi giải trí mà còn giúp nhóm:

Củng cố kiến thức lập trình C++.

Hiểu rõ hơn về quy trình phát triển phần mềm.

Rèn luyện kỹ năng làm việc nhóm, sử dụng GitHub để quản lý code.

Tạo sản phẩm có thể chạy và trải nghiệm trực tiếp, phục vụ báo cáo cuối kỳ.
