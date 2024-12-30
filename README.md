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

# Mô tả tự án
Khi phát hiên nồng độ khói cao hơn ngưỡng quy định, còi cảnh báo sẽ kêu lên, cửa thoát hiểm tự động mở và quạt thông gió được bật để đưa hết khói ra ngoài. Còn khi phát hiện có lửa, động cơ bơm nước được bật để dập tắt ngọn lửa. 

# Sơ đồ khối
![Editing Cuoi_ki_phat_trien_ung_dung_IoT_README md at main · Longduc000_Cuoi_ki_phat_trien_ung_dung_IoT - Cốc Cốc 12_30_2024 9_36_07 AM png 12_30_2024 10_25_18 AM](https://github.com/user-attachments/assets/1e40643a-b1a2-495d-abb1-cd80993b554c)

# Gửi cảnh báo và cập nhật thông số
- Khi phát hiện có lửa, thông báo được gửi lên HiveMQ
![gửi tin nhắn lên hivemq](https://github.com/user-attachments/assets/64567edb-0d9f-4926-9693-376cb61f7b3e)

- Thiết lập node-red
![Editing Cuoi_ki_phat_trien_ung_dung_IoT_README md at main · Longduc000_Cuoi_ki_phat_trien_ung_dung_IoT - Cốc Cốc 12_30_2024 9_36_07 AM](https://github.com/user-attachments/assets/cbbd5570-e251-4ef3-87bf-432e18456220)

- Cập nhật thông số cảm biến lên dashboard
1) Khi không phát hiện có lửa
chỉ số khói là dưới 500ppm và giá trị cảm biến lửa khi không phát hiện lửa luôn là 1
![Node-RED _ Flow 2 - Cốc Cốc 12_30_2024 10_32_46 AM](https://github.com/user-attachments/assets/4ab0815e-8d62-4886-ac19-06a6dc1d8077)

2) Khi phát hiện có lửa
chỉ số khói sẽ vượt 500ppm và giá trị cảm biến lửa khi phát hiện có lửa sẽ luôn là 0
![Captures - File Explorer 12_30_2024 10_34_16 AM](https://github.com/user-attachments/assets/3be7932a-551a-4db4-ab02-5e8ee309ec19)



# Quá trình demo project
Nằm trong folder "video demo" bên trên
