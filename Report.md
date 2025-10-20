Fungsi segmentDetection() digunakan untuk menganalisis hasil gambar yang digambar di canvas, dengan tujuan mengidentifikasi area (segmen) yang berisi piksel non-putih. Proses dilakukan dengan pendekatan sliding window—yaitu dengan menggeser jendela berukuran tertentu ke seluruh area gambar dan memeriksa apakah di dalam jendela tersebut terdapat piksel yang “tergambar”.

**Window Size 3×3**
Ukuran jendela: 3×3 piksel

Half size: 1 (artinya jendela meluas 1 piksel ke setiap arah dari pusat)

Tujuan: Deteksi detail kecil atau garis tipis di gambar

Proses:

Setiap posisi (i, j) diproses bersama piksel sekitarnya dalam area 3×3.

Piksel dianggap “tergambar” bila salah satu nilai warna merah, hijau, atau biru < 240 (tidak putih murni).

Jika ditemukan minimal satu piksel tergambar, jendela dianggap non-empty.

Kelebihan:

Sensitif terhadap detail kecil dan tepian.

Baik untuk mendeteksi garis tipis atau coretan kecil.

Kekurangan:

Terlalu sensitif terhadap noise.

Tidak cocok untuk area gambar besar karena membentuk terlalu banyak jendela terpisah.

Output:

Setiap jendela yang terdeteksi dicetak dalam bentuk matriks 3×3 berisi 1 (tergambar) dan 0 (kosong).

Total jumlah jendela non-empty dihitung dan ditampilkan.

**Window Size 5×5**

Ukuran jendela: 5×5 piksel

Half size: 2

Tujuan: Deteksi area yang lebih luas (segmentasi kasar)

Proses:

Sama seperti metode 3×3, tetapi area yang diperiksa lebih besar (25 piksel).

Digunakan untuk mendeteksi pola atau area menggambar yang lebih tebal.

Kelebihan:

Lebih stabil terhadap noise.

Mampu mengidentifikasi blok gambar yang lebih besar sebagai satu segmen.

Kekurangan:

Bisa kehilangan detail kecil (garis tipis bisa diabaikan).

Lebih berat secara komputasi karena melibatkan lebih banyak piksel per jendela.

Output:

Menampilkan setiap matriks 5×5 non-empty.


https://gemini.google.com/share/d8f697de7bf0