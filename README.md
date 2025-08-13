# TCP Echo Client-Server (C Language)

Proyek ini mengimplementasikan komunikasi TCP sederhana antara **client** dan **server** dengan mekanisme *echo*.  
Setiap pesan yang dikirim client akan diterima server dan dikembalikan (echo) ke client.

---

## 📋 Fitur

- Client mengirim pesan ke server melalui koneksi TCP.
- Server menerima pesan dan mengirimkan kembali pesan tersebut.
- Koneksi berjalan secara terus-menerus hingga diputuskan.
- Implementasi menggunakan bahasa C dan socket API POSIX.

---

## ⚙️ Struktur Proyek

- `client.c` → Program client TCP.
- `server.c` → Program server TCP (mendukung `fork()` untuk banyak koneksi).

---

## 🚀 Cara Menjalankan

1. **Kompilasi server:**

```bash
gcc server.c -o server
```

2. **Kompilasi client:**

```bash
gcc client.c -o client
```

3. **Jalankan server di terminal 1:**

```bash
./server
```

4. **Jalankan client di terminal 2:**

```bash
./client
```

5. Ketik pesan di client, server akan mengirimkan kembali pesan tersebut.

---

## 📚 Referensi

* [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
* [TCP Protocol - Wikipedia](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)

---

## 📝 Lisensi

Proyek ini dirilis di bawah lisensi **MIT**.
