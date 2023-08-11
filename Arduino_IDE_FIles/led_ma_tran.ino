#include "LedControl.h"// thêm thư viện
LedControl matrix = LedControl(2, 4, 3, 1);
// Chân 12 nối với chân DataIn
// Chân 11 nối với chân CLK
// Chân 10 nối với chân LOAD
// Sử dụng 1 IC MAX7219
void setup() {
    matrix.shutdown(0, false); // Bật hiển thị
    matrix.setIntensity(0, 15); // Đặt độ sáng lớn nhất
    matrix.clearDisplay(0); // Tắt tất cả led
}
    // Thiết lập mã cho các ký tự
byte A[56] = {
    0x00,0x3F,0x7F,0xA4,0xA4,0x7F,0x3F,0x00, // A
    0x00,0xFF,0xFF,0x98,0x94,0x92,0x61,0x00, // R
    0x00,0xFF,0xFF,0x81,0x81,0x7E,0x3C,0x00, // D
    0x00,0xFE,0xFF,0x01,0x01,0xFF,0xFE,0x00, // U
    0x00,0x81,0x81,0xFF,0xFF,0x81,0x81,0x00, // I
    0x00,0xFF,0xC0,0x30,0x0C,0x03,0xFF,0x00, // N
    0x00,0x7E,0xFF,0x81,0x81,0xFF,0x7E,0x00 // O          
};
// Chương trình con chạy chuỗi ký tự
void scroll() {
        matrix.clearDisplay(0);
        int pos = 8;
        for (int j = pos; j > -56; j--) { // Vòng lặp thay đổi vị trí
            for (int i = 0; i < 56; i++) { // Vòng lăp để hiển thị ký tự
                matrix.setRow(0, i + j, A[i]);
            }
            delay(100);
        }
    }
    
// Chương trình con hiển thị từng ký tự
void show() {
    matrix.clearDisplay(0);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i]); //Hiển thị từng hàng để được ký tự A
    delay(200);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i + 8]);
    delay(200);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i + 16]);
    delay(200);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i + 24]);
    delay(200);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i + 32]);
    delay(200);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i + 40]);
    delay(200);
    for (int i = 0; i < 8; i++) matrix.setRow(0, i, A[i + 48]);
    delay(200);
}
void loop() {
    scroll();
    show();
    delay(100);
}