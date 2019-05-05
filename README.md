# SoalShift_modul4_C10

1. Di soal nomer 1, kita diminta untuk semua nama file dan folder harus terenkripsi. Caesar Cipher adalah model enkripsi akan dipakai. Dengan menambah character lisst diekspansi, tidak hanya alfabet, namun juga di diacak.

```
qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0
```

Fungsi enkripsi yang dapat mengganti character list tersebut berubah sebanyak 17 karakter dan jika melebihi indeks maka kembali lagi ke 0 tetapi ketika menemui " / " maka characternya tetap.

Berikut kode untuk enkrip dan juga untuk dekripsinya:

# Kode enkripsi:

```
void caesar(char inp[], int len, int flag){
    int i, j, indeks;
    if (flag == ENCRYPT){
        for (i = 0; i < len; i++){

            if (inp[i] == '/')
                continue;
            else
            {
                for (j = 0; j < strlen(charlist); j++)
                {
                    if (charlist[j] == inp[i])
                        indeks = j;
                }
                indeks += KEY;
                indeks %= strlen(charlist);
                inp[i] = charlist[indeks];
            }
        }
    }
```

# Kode dekripsi:

```
    else if (flag == DECRYPT){

        for (i = 0; i < len; i++){
            if (inp[i] == '/')
                continue;
            else{

                for (j = 0; j < strlen(charlist); j++){

                    if (charlist[j] == inp[i])
                        indeks = j;
                }
                indeks -= KEY;
                while (indeks < 0)
                    indeks += strlen(charlist);
                inp[i] = charlist[indeks];
            }
        }
    }
}
```
