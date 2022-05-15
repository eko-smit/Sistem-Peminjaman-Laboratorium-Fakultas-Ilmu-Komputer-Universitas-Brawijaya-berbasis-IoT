# Sistem-Peminjaman-Laboratorium-Fakultas-Ilmu-Komputer-Universitas-Brawijaya-berbasis-IoT
Peminjaman laboratorium / ruang adalah kegiatan yang dilakukan oleh manusia untuk menggunakan sebuah ruangan / laboratorium pada jadwal tertentu dan membutuhkan pendataan secara administratif. Sistem yang dipergunakan pada peminjaman laboratorium menggunakan Kode QR yang disediakan oleh aplikasi. Penggunaan Kode QR dilakukan saat peminjam ingin memasuki laboratorium, sesuai jadwal yang ditentukan dan dikonfirmasi dengan ESP-32Cam yang mengatur kendali penguncian solenoid pada pintu laboratorium. Sebelum mengatur kendali penguncian Solenoid, ESP-32Cam menghubungi Firebase untuk mencocokkan Kode QR peminjam yang berisi nama, nim dan detail tanggal peminjaman yang sudah dienkripsi. Aplikasi peminjaman sudah dilengkapi dengan menampilkan jadwal yang tersedia pada tiap laboratorium, dikembangkan menggunakan Kodular. Sehingga aplikasi ini mudah sekali untuk berinteraksi dengan Firebase. Firebase sendiri berfungsi sebagai database yang dipergunakan sebagai penyimpanan data untuk sistem yang telah dibuat. Sistem yang dibuat mampu bekerja sesuai fungsinya, yaitu membantu peminjaman dan berkomunikasi antar fitur yang berhubungan dengan sistem peminjaman laboratorium berbasis IoT.

#Konfigurasi PIN Camera OV2640 -> ESP32CAM
D0          GPIO 5
D1          GPIO 18
D2          GPIO 19
D3          GPIO 21
D4          GPIO 36
D5	        GPIO 39
D6        	GPIO 34
D7	        GPIO 35
XCLK      	GPIO 0
PCLK	      GPIO 22
VSYNC	      GPIO 25
HREF      	GPIO 23
SDA       	GPIO 26
SCL       	GPIO 27
Power Pin	  GPIO 32

#Konfigurasi PIN FTDI232RL -> ESP32CAM
VCC	  5V
Tx	  U0R
Rx	  U0T
GND	  GND

#Konfigurasi PIN Buzzer -> ESP32CAM
Data	  IO2
GND 	  GND

#Konfigurasi PIN Relay -> ESP32CAM
VCC	  3V3
IN1	  IO12
GND	  GND

Preview Aplikasi
![Apps(1)](https://user-images.githubusercontent.com/105602352/168486726-acb8fb5a-8178-4e60-b8c7-61d64e5174ff.jpg)\
![Apps(2)](https://user-images.githubusercontent.com/105602352/168486722-e47858ba-66e9-471d-b385-d037dfe7ef28.jpg)
