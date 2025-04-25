# Path of Pain
- Các thư viện SDL đã sử dụng: SDL_image.h, SDL_mixer.h, SDL_ttf.h.
- Code tham khảo:
    + Toàn bộ file graphics.h: https://github.com/chauttm/gameProject
- Nhạc game:
    + Nhạc menu chính: Hollow Knight Original Soundtrack 26 - "Hollow Knight" theme & music by Christopher Larkin.
    + Nhạc trong game: Hollow Knight Original Soundtrack 23 - "White Palace" theme & music by Christopher Larkin.
- Giới thiệu game:
    Game thuộc thể loại Platformer (VD: Mario,...), được lấy cảm hứng dựa trên tựa game nổi tiếng "Hollow knight" của Team Cherry.
    Mục tiêu của game là có thể đưa nhân vật đi đến cuối của bản đồ.
- Bên trong game:
    + Game được chia nhỏ thành nhiều header để dễ quản lí:
        + graphics.h để quản lí các hàm về đồ họa, âm thanh, text.
        + defs.h để quản lí các hằng só.
        + menu.h để quản lí main menu và pause menu.
        + map.h để quản lí map.
        + sprites.h để quản lí animation.
        + game.h để quản lí về cơ chế game.
    + Các tính năng game:
        + Người chơi có thể di chuyển trái phải bằng A D và nhảy bằng W, khi muốn pause game thì ta sẽ ấn nút ESC.
        + Có các animation riêng cho từng trạng thái (chạy, nhảy, rơi,...).
        + Có nhạc nền và hiệu ứng âm thanh của nhân vật.
        + Trò chơi sẽ kết thúc khi nhân vật di chuyển đến cuối map.
