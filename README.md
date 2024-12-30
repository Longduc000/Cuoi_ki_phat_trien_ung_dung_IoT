# Đề tài: Hệ thống báo cháy thông minh
# Đặt vấn đề: 
Hỏa hoạn là một trong những nguy cơ gây thiệt hại nghiêm trọng về người và tài sản, đặc biệt trong bối cảnh đô thị hóa ngày càng gia tăng. Các hệ thống báo cháy truyền thống còn nhiều hạn chế trong việc phát hiện sớm và gửi cảnh báo kịp thời. Vì vậy, việc nghiên cứu và phát triển hệ thống báo cháy thông minh, ứng dụng công nghệ hiện đại như IoT và AI, là cần thiết để nâng cao hiệu quả phát hiện và giảm thiểu rủi ro do cháy nổ.
# Danh sách linh kiện:
+ 1 esp32
+ 2 module còi buzzer
+ 1 cảm biến khí gas mq2
+ 1 cảm biến lửa
+ 1 quạt 5V 4x4x1cm
+ 1 động cơ servo sg90 180 độ
+ 1 động cơ bơm nước
+ 2 relay 5V
# Sơ đồ khối
![Downloads - File Explorer 12_30_2024 9_29_31 AM](https://github.com/user-attachments/assets/27b91537-25ef-497a-8748-8464e40b3865)
# Gửi cảnh báo và cập nhật thông số
- Khi phát hiện có gửi, thông báo được gửi lên HiveMQ
![gửi tin nhắn lên hivemq](https://github.com/user-attachments/assets/64567edb-0d9f-4926-9693-376cb61f7b3e)

- Thiết lập node-red
![Editing Cuoi_ki_phat_trien_ung_dung_IoT_README md at main · Longduc000_Cuoi_ki_phat_trien_ung_dung_IoT - Cốc Cốc 12_30_2024 9_36_07 AM](https://github.com/user-attachments/assets/cbbd5570-e251-4ef3-87bf-432e18456220)

- Cập nhật thông số cảm biến lên dashboard
+ Khi không phát hiện có lửa
![Node-RED Dashboard - Cốc Cốc 12_30_2024 9_22_33 AM](https://github.com/user-attachments/assets/68fbd429-9969-4985-b40e-656b018b6c7e)

+ Khi phát hiện có lửa
![Node-RED Dashboard - Cốc Cốc 12_30_2024 9_25_16 AM](https://github.com/user-attachments/assets/fa37b216-8b69-44e9-a6f1-069967345ccb)
