/*
Database KTP Program

- Sebuah program yang bekerja sebagai database penampung data KTP masukkan dari pengguna
- Berisi fitur penambahan, penghapusan, serta pencarian dan penampilan data
____________________________________________________________________________________________

Kevin Nathanael Halim
( 5025211140 )

Penggunaan :
1. Lakukan run pada program Database KTP
2. Masukkan angka sesuai dengan indeks dari perintah yang ingin dijalankan
3 a. Bila ingin menambahkan data, maka isi seluruh bagian sesuai dengan yang diminta untuk pendataan
  b. Bila ingin mencari dan menampilkan data, pilih kategori pencarian yang ingin digunakan dan masukkan
     sesuai kategori yang ingin dicari
  c. Bila ingin menghapus data, pilih NIK atau Nama sebagai pencarian, kemudian masukkan NIK atau
     nama yang ingin dihapus datanya
4. Program pun melakukan operasi yang ingin dijalankan dan menampilkan hasilnya
*/

#include <stdio.h>
#include <string.h>

/*
 * Struct penyimpanan data-data
 * penduduk dalam KTP
 */

typedef struct {
    long long nik;
    char nama[300];
    char tempat[50];
    char tanggal[18];
    char jenis_kelamin[10];
    char gol_darah[5];
    char alamat[300];
    char rt[5];
    char rw[5];
    char keldesa[50];
    char kecamatan[50];
    char agama[10];
    char status[15];
    char pekerjaan[50];
    char kewarnegaraan[3];
} KTP ;

int num = 0;
int del = 0;
int arr[1000];
KTP pend[1000];

void c_new();
void c_delete();
void c_search();
void c_view();
void show(int i);

int
main()
{
	int x = 1;

    do
    {
	    printf("\n\t- [ Database KTP ] -\n");
		printf("( Jumlah Data Tersimpan Saat Ini : %d )\n", num - del);
	    printf("\n-List Perintah-\n");
	    printf("1. Menambahkan\n");
	    printf("2. Mencari dan Menampilkan\n");
        printf("3. Menghapus\n");
		printf("4. Menampilkan Semua\n");
		printf("5. Keluar\n");
	    printf("Masukkan angka indeks dari perintah yang ingin anda lakukan : ");
	    scanf("%d", &x);
	    getchar();
	
	    switch (x)
	    {
		    case 1 :
		    	c_new();
		    	break;
			
		    case 2 :
		    	c_search();
		    	break;

            case 3 :
		    	c_delete();
		    	break;

			case 4 :
			    c_view();
				break;
			
		    case 5 :
		    	printf("\nTerima kasih telah menggunakan Database KTP!\n");
                return 0;

			default :
			    printf("\nMohon masukkan angka yang sesuai...\n");
				break;
	    }

    } while (x != 5);
    
}

/*
 * Menambahkan data KTP baru pada struct
 * dengan penambahan nilai pada array
 */

void
c_new()
{
	int i;
	long long check;
	
	printf("\nMasukkan NIK : ");
	scanf("%lld", &check);
	getchar();

	for (i=0 ; i<num ; i++)
	{
		if (arr[i] == -1)
		{
			continue;
		}
				
		if (check == pend[i].nik)
		{
			printf("\nNIK yang anda masukkan sudah terdaftar, mohon dicek kembali..\n");
			return;
		}
	}

	arr[num] = num;
	pend[num].nik = check;

	printf("Masukkan Nama Lengkap : ");
	gets(pend[num].nama);
	printf("Masukkan Tempat Lahir (contoh : Jakarta) : ");
	gets(pend[num].tempat);
	printf("Masukkan Tanggal Lahir (format : Tanggal Bulan Tahun, contoh : 2 Juni 1992) : ");
	gets(pend[num].tanggal);
	printf("Masukkan Jenis Kelamin (Laki-laki/Perempuan) : ");
	gets(pend[num].jenis_kelamin);
	printf("Masukkan Golongan Darah (A/B/O/AB) : ");
	scanf("%s", pend[num].gol_darah);
	getchar();
	printf("Masukkan Alamat Lengkap : ");
	gets(pend[num].alamat);
	printf("Masukkan RT (contoh : 003) : ");
	scanf("%s", pend[num].rt);
	getchar();
	printf("Masukkan RW (contoh : 004) : ");
	scanf("%s", pend[num].rw);
	getchar();
	printf("Masukkan Nama Kelurahan/Desa : ");
	gets(pend[num].keldesa);
	printf("Masukkan Nama Kecamatan : ");
	gets(pend[num].kecamatan);
	printf("Masukkan Agama : ");
	gets(pend[num].agama);
	printf("Masukkan Status Perkawinan (Sudah Kawin / Belum Kawin) : ");
	gets(pend[num].status);
	printf("Masukkan Pekerjaan : ");
	gets(pend[num].pekerjaan);
	printf("Masukkan Kewarnegaraan (WNI/WNA) : ");
	gets(pend[num].kewarnegaraan);
	
	num++;
	printf("\nPenambahan data berhasil!\n");
}

/*
 * Menghapus data KTP yang sesuai berdasarkan NIK
 * atau nama lengkap dengan mengubah nilai pada array
 */

void
c_delete()
{
	if (num - del == 0)
	{
		printf("\nTidak ada data dalam database saat ini, mohon menambahkan data terlebih dahulu...\n");
		return;
	}

	int n, count = 0;
	long long nik;
	char word[500];
	
	printf("\n1. NIK\n");
	printf("2. Nama Lengkap\n");
	printf("Masukkan angka indeks dari kategori pencarian yang ingin digunakan untuk menghapus : ");
	scanf("%d", &n);
	getchar();
	printf("\n");
	
	switch(n)
	{
		case 1 :
			printf("Masukkan NIK penduduk yang ingin dihapus datanya : ");
			scanf("%lld", &nik);
			getchar();
			
			int i;
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (nik == pend[i].nik)
				{
					count++;
					arr[i] = -1;
					del++;
					break;
				}
			}
			break;
			
		case 2 :
			printf("Masukkan nama lengkap penduduk yang ingin dihapus datanya : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].nama) == 0)
				{
					count++;
					arr[i] = -1;
					del++;
				}
			}
			break;
			
		default :
			printf("Mohon masukkan angka yang sesuai lain kali..\n");
			return;
	}

	if (count == 0)
	{
		printf("\nTidak ditemukan hasil pencarian yang sesuai untuk dihapus..\n");
	}

	else
	{
		printf("\nPenghapusan data berhasil! ( %d data )\n", count);
	}
}

/*
 * Mencari seluruh data yang sesuai dengan permintaan
 * user dengan mengecek melalui isi dari array dan struct
 */

void
c_search()
{
	if (num - del == 0)
	{
		printf("\nTidak ada data dalam database saat ini, mohon menambahkan data terlebih dahulu...\n");
		return;
	}

	int n, count = 0;
	long long nik;
	char word[500];
	
	printf("\n1. NIK\n");
	printf("2. Nama Lengkap\n");
	printf("3. Tempat Lahir\n");
	printf("4. Tanggal Lahir\n");
	printf("5. Jenis Kelamin\n");
	printf("6. Golongan Darah\n");
	printf("7. Alamat Lengkap\n");
	printf("8. Nama Kelurahan/Desa\n");
	printf("9. Nama Kecamatan\n");
	printf("10. Agama\n");
	printf("11. Status\n");
	printf("12. Pekerjaan\n");
	printf("13. Kewarnegaraan\n");
	printf("Masukkan angka indeks dari kategori pencarian yang ingin digunakan : ");
	scanf("%d", &n);
	getchar();
	printf("\n");
	
	switch(n)
	{
		case 1 :
			printf("Masukkan NIK penduduk yang ingin dicari : ");
			scanf("%lld", &nik);
			getchar();
			
			int i;
			
			printf("\n[ Hasil Pencarian ]\n");
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (nik == pend[i].nik)
				{
					count++;
					show(i);
				}
			}
			break;
			
		case 2 :
			printf("Masukkan nama lengkap penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].nama) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
		case 3 :
			printf("Masukkan tempat lahir penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].tempat) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 4 :
			printf("Masukkan tanggal lahir penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].tanggal) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 5 :
			printf("Masukkan jenis kelamin penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].jenis_kelamin) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 6 :
			printf("Masukkan golongan darah penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].gol_darah) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 7 :
			printf("Masukkan alamat lengkap penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].alamat) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 8 :
			printf("Masukkan nama kelurahan/desa penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].keldesa) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 9 :
			printf("Masukkan nama kecamatan penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].kecamatan) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 10 :
			printf("Masukkan agama penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].agama) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 11 :
			printf("Masukkan status perkawinan penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num-1 ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].status) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 12 :
			printf("Masukkan pekerjaan penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].pekerjaan) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
			case 13 :
			printf("Masukkan kewarnegaraan penduduk yang ingin dicari : ");
			gets(word);
			
			for (i=0 ; i<num ; i++)
			{
				if (arr[i] == -1)
				{
					continue;
				}
				
				if (strcmp(word, pend[i].kewarnegaraan) == 0)
				{
					count++;
					show(i);
				}
			}
			break;
			
		    default :
			printf("Mohon masukkan angka yang sesuai lain kali..\n");
			return;
	}

	if (count == 0)
	{
		printf("\nTidak ditemukan hasil pencarian yang sesuai..\n");
	}

	else
	{
		printf("\nSeluruh hasil pencarian yang sesuai telah ditampilkan! ( %d hasil )\n", count);
	}
}

/*
 * Menemukan seluruh data yang ada
 * dan sedang tersimpan melalui array
 */

void
c_view()
{
	if (num - del == 0)
	{
		printf("\nTidak ada data dalam database saat ini, mohon menambahkan data terlebih dahulu...\n");
		return;
	}

	int i;

	for (i=0 ; i<num; i++)
	{
		if (arr[i] == -1)
		{
			continue;
		}

		show(i);
	}

	printf("\nSeluruh data yang tersedia telah ditampilkan! ( %d data )\n", num - del);
}

/*
 * Menampilkan seluruh data KTP pada
 * struct yang sesuai dengan masukkan
 */

void
show(int i)
{
	printf("\nNIK : %lld\n", pend[i].nik);
	printf("Nama Lengkap : %s\n", pend[i].nama);
	printf("Tempat , Tanggal Lahir : %s, %s\n", pend[i].tempat, pend[i].tanggal);
	printf("Jenis Kelamin : %s\n", pend[i].jenis_kelamin);
	printf("Golongan Darah : %s\n", pend[i].gol_darah);
	printf("Alamat Lengkap : %s\n", pend[i].alamat);
	printf("RT/RW : %s/%s\n", pend[i].rt, pend[i].rw);
	printf("Nama Kelurahan/Desa : %s\n", pend[i].keldesa);
	printf("Nama Kecamatan : %s\n", pend[i].kecamatan);
	printf("Agama : %s\n", pend[i].agama);
	printf("Status Perkawinan : %s\n", pend[i].status);
	printf("Pekerjaan : %s\n", pend[i].pekerjaan);
	printf("Kewarnegaraan : %s\n", pend[i].kewarnegaraan);
}