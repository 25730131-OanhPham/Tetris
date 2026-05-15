# 📖 **Giới thiệu dự án - Game Tetris Console** #

#### Dự án này được thực hiện trong khuôn khổ môn học SS004.F21.CNTT, với mục tiêu xây dựng trò chơi Tetris bằng ngôn ngữ C++. Đây là những trò chơi kinh điển, giúp người chơi rèn luyện phản xạ, tư duy logic và khả năng xử lý tình huống nhanh.

#### Việc triển khai dự án không chỉ dừng lại ở việc tạo ra một trò chơi có thể chạy được, mà còn nhằm:

#### Rèn luyện kỹ năng lập trình hướng đối tượng và quản lý bộ nhớ.

#### Hiểu rõ hơn về cấu trúc dữ liệu (mảng, ma trận, xử lý bàn phím).

#### Thực hành quy trình phát triển phần mềm: từ thiết kế, coding, kiểm thử, đến viết tài liệu.

#### Làm quen với công cụ GitHub để quản lý phiên bản và làm việc nhóm.

#### Dự án được quản lý trên GitHub, sử dụng GitHub Desktop để clone, commit, push/pull code. Mỗi thành viên trong nhóm đều có trách nhiệm rõ ràng, đảm bảo tiến độ và chất lượng sản phẩm cuối kỳ.

# ⚙️ Hướng dẫn cài đặt & chạy #
## 1. Clone repository về máy ##
GitHub Desktop:

Mở GitHub Desktop → File → Clone repository.

Chọn tab URL, nhập link repo (https://github.com/25730162/Tetris).

Chọn thư mục lưu trên máy → Clone.

Git command line:

bash
git clone https://github.com/25730162/Tetris.git
## 2. Mở dự án ##
Mở bằng Visual Studio Code hoặc IDE hỗ trợ C++.

Kiểm tra file tetris.cpp và các file cấu hình trong thư mục .vscode.

## 3. Biên dịch & chạy ##
Nếu dùng g++:

bash
g++ tetris.cpp -o tetris
./tetris
Nếu dùng Visual Studio Code:

Nhấn Run hoặc dùng cấu hình trong .vscode/tasks.json.

# 🎮 Cách chơi #
⬅️➡️ Dùng phím mũi tên để di chuyển khối.

⬇️ Làm khối rơi nhanh hơn.

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
