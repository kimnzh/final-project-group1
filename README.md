# Proyek Akhir Semester - Pemrograman Lanjut 02
# Program Simulasi SIAK Sederhana

Anggota Kelompok 1:

1. Daffa Sayra Firdaus (2306267151)
2. Muhamad Hakim Nizami (2306210001)

Versi Program : 1.0

# Penjelasan Program

Program ini merupakan software sederhana yang menerapkan sistem manajemen mahasiswa. Program ini terinspirasi dari web SIAk-NG yang menjadi pedoman bagi mahasiswa UI dalam menunjang kegiatan akademik di Universitas Indonesia seperti mengatur biaya operasiona pendidikan, melihat status akademik, penentuan jadwal, pengajuan mata kuliah, dan lain-lain. SIAk-NG sendiri bersifat online dan dapat diakses oleh pengguna Mahasiswa yang terhubung ke jaringan Internet sehingga pengguna Mahasiswa dapat menggunakan aplikasi ini dari mana saja dan kapan saja. Program ini mengimplementasikan fungsionalitas yang ada dalam SIAk-NG dalam scope yang lebih sederhana. Dalam program ini, terdapat dua mode, yaitu mode mahasiswa dan mode dosen. Berikut adalah deskripsi dari masing-masing mode:

1. Mode Mahasiswa

- Menunjukkan data diri seperti nama, NPM, angkatan, program studi, nama dosen pembimbing, status akademik, SKS yang lulus, Mutu, IPK, SKS yang diperoleh, status pembayaran biaya operasional pendidikan.
- Menampilkan indeks prestasi keseluruhan dalam bentuk grafik.
- Mengajukan mata kuliah/kelas yang ingin ditempuh dalam satu semester (dengan persetujuan dosen pembimbing).
- Dapat membatalkan mata kuliah yang sebelumnya diajukan, selama belum disetujui oleh dosen pembimbing.
- Dapat melihat riwayat mata kuliah yang sudah diajukan selama perkuliahan.
- Melihat nilai dari mata kuliah yang sudah ditempuh (dinilai oleh dosen pembimbing) (Dapat disort secara ascending ataupun descending).
- Men-search mata kuliah yang dapat dipilih selama satu semester.
- Dapat memilih untuk membayar biaya operasional pendidikan atau UKT, jika membayar, maka status pembayaran dianggap lunas
- Disertai dengan panduan dalam menggunakan program dan opsi-opsi yang bisa dilakukan dalam program.
- Mahasiswa dapat merubah profile dari mahasiswa, seperti nama dan password.

2. Mode Dosen

- Dosen dapat menyetujui mata kuliah yang diajukan oleh mahasiswa berdasarkan pertimbangan batas SKS dan persyaratan nilai/IP
- Dosen dapat menilai mata kuliah yang ditempuh oleh mahasiswa bimbingan selama satu semester
- Memilih untuk meluluskan mahasiswa bimbingan dalam satu semester
- Menghitung data tendencies dari seluruh data nilai mahasiswa yang dibimbing
- Mengonfirmasi status akademik atau keaktifan masing-masing mahasiswa
- Memsetujui matkul yang dipilih oleh mahasiswa
- Menampilkan bagan nilai mahasiswa (tampilan secara chart kasar)

Selain mode mahasiswa dan dosen, terdapat pilihan untuk menambah data mahasiswa dan data dosen baru. Setiap data dari mahasiswa maupun dosen, seperti nilai, mata kuliah yang diambil, dan sebagainya disimpan dalam database berupa directory yang masing-masing merujuk kepada satu orang mahasiswa/dosen. Untuk data pribadi seperti nama, NPM/NIP, program studi, dan lainnya disimpan dalam struct yang datanya diambil (read) dari database yang menyimpan data dari masing-masing mahasiswa atau dosen. Setiap data pada struct memiliki method atau function yang dikhususkan untuk meng-edit nilai yang tersimpan di dalam variabel struct tersebut.

# Kekurangan dalam Program

Program memiliki kelemahan dalam fungsionalitasnya, seperti:

- Sistem database yang masih mengandalkan file handling, sehingga kurang efisien.
- Ada beberapa sistem dalam program yang masih belum terintegrasi antara satu dengan lainnya, seperti pilihan untuk mengubah profile mahasiswa belum diintegrasikan dengan penamaan database, sehingga akan terjadi masalah jika nama mahasiswa diubah.
- Sistem penilaian oleh dosen masih belum berdasarkan kelas yang diampu oleh dosen tertentu, melainkan dinilai oleh dosen pembimbing dari masing-masing mahasiswa. Menjadikan program ini masih belum sempurna untuk diterapkan dalam kehidupan nyata
- Grafik yang menyajikan ipk dari masing-masing mahasiswa masih memberlakukan pembulatan, sehingga visualisasi data masing kurang begitu akurat.
- Sistem log in masih mengharuskan pengguna untuk memasukkan nama secara penuh (bukan berupa username), sehingga menyulitkan pengguna yang memiliki nama yang panjang.
