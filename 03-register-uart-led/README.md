# STM32F0 Bare-Metal UART & LED

Bu proje, STM32F0 Discovery kiti üzerinde kütüphane soyutlamalarını minimize ederek, doğrudan **Register Level (Bare-Metal)** programlama teknikleriyle geliştirilmiştir. 

## 🎯 Projenin Amacı
İşlemciyi `HAL_Delay` gibi fonksiyonlarla bloklamadan, arka planda zamanı takip ederek aynı anda hem LED yakıp söndürmek hem de UART üzerinden terminale (Hercules vb.) veri göndermektir.

## 🛠 Teknik Özellikler
* **Donanım:** STM32F051R8 (ARM Cortex-M0).
* **Zaman Yönetimi:** `HAL_GetTick()` tabanlı non-blocking (bloklamayan) yapı.
* **UART Yapılandırması:** * **Hız:** 9600 Baud
  * **Pin:** PA9 (TX)
* **GPIO Yapılandırması:** * **LED:** PC9 (Mavi LED)
* 
## 💻 Çalışma Mantığı
Kod, UART haberleşmesi sırasında her bir karakterin gönderilip gönderilmediğini **TXE (Transmit Data Register Empty)** bayrağını maskeleyerek kontrol eder. Cümleler, Null Terminator (`\0`) gözetilerek karakter karakter donanıma aktarılır.

## 🔌 Bağlantı Şeması
* STM32 **PA9** -> USB-TTL **RX**
* STM32 **GND** -> USB-TTL **GND**

## 📜 Lisans
Bu proje eğitim amaçlı geliştirilmiştir, özgürce kullanılabilir.
