//created by me (https://github.com/Agung-Krisna) and tatanofera (https://github.com/tatanofera)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ADMINISTRASI 50.00
#define BMP_R 10.00
#define BMP_S 20.00
#define BIAYA_METER_1 50.00
#define BIAYA_METER_N 10.00
#define DENDA_100_KEATAS 20.00
#define DENDA_LBH10_KRNG100 10.00

int check(char consumer_class, int date);
int calculate_water(double last_month_usage, double this_month_usage, char consumer_class, int date);
char cetak_struk(char invoiceA[100], char invoiceB[100], char invoiceC[100], char invoiceD[100]);

int main(void){
    char consumer_class;
    int date;
    printf ("||Program Pembayaran Air PT. Tirta Jaya||\n\n");
    printf ("Halo Operator\n");
    time_t now;
    time (&now);
    printf ("Hari ini adalah hari %s", ctime(&now));//non broken-down time information.
    printf ("Tolong masukkan tanggal hari ini sesuai dengan waktu sistem anda: ");
    scanf ("%d", &date);
    if (date <= 0 || date >= 32){
        printf ("Tolong cek input anda lagi\n");
        return EXIT_FAILURE;
    }
    printf ("Masukkan kelas konsumen:\n");
    printf ("(R) Rumah tangga\n");
    printf ("(S) Usaha\n");
    scanf (" %c", &consumer_class);
    switch (consumer_class){
        case 'r':
        case 'R':
            check(consumer_class, date);
            break;
        case 'S':
        case 's':
            check(consumer_class, date);
            break;
        default:
            printf ("Tolong cek input anda lagi\n");
    }
    return 0;
}
int check(char consumer_class, int date){
    double last_month_usage;
    double this_month_usage;
    char choice;

    printf ("Masukkan biaya penggunaan air bulan lalu:\n");
    scanf ("%lf", &last_month_usage);
    if ((float)last_month_usage <= 0){
        printf ("Tolong cek input anda lagi\n");
        return EXIT_FAILURE;
    }
    else{
        printf ("Masukkan biaya penggunaan air bulan ini:\n");
        scanf ("%lf", &this_month_usage);
    }
    if (this_month_usage <= last_month_usage){
        printf ("Tolong cek input anda lagi, penggunaan bulan lalu\nakan selalu lebih kecil daripada penggunaan bulan ini\n");
        return EXIT_FAILURE;
    }
    if ((float)this_month_usage <= 0){
        printf ("Tolong cek input anda lagi\n");
        return EXIT_FAILURE;
    }

    printf ("Apakah data ini benar:\n");
    printf ("Penggunaan air bulan lalu = %.3f\n", last_month_usage);
    printf ("Penggunaan air bulan ini = %.3f\n", this_month_usage);
    printf ("Y(benar)/n(salah)\n");
    scanf (" %c", &choice);
    switch (choice){
        case 'Y':
        case 'y':
            calculate_water(last_month_usage, this_month_usage, consumer_class, date);
            break;
        case 'N':
        case 'n':
            printf ("Silahkan masukkan data kembali\n\n");
            check(consumer_class, date);
            break;
        default:
            printf ("Tolong cek input anda lagi\n");
        }
    return 0;
}

int calculate_water(double last_month_usage, double this_month_usage, char consumer_class, int date){
    double costs;
    double fines;
    double total;
    int converter;
    int converter_fines;
    double water_usage;
    double another_water_usage;
    char pilihan;
    int start = 50;
    char invoiceA[100];
    char invoiceB[100];
    char invoiceC[100];
    char invoiceD[100];
    water_usage = this_month_usage - last_month_usage;

    if (water_usage <= 10){
        costs = 50;
    }
    else if (water_usage > 10){
        costs = 50;
        for (start = 10; start < water_usage; start ++){
            costs += 10;
        }
    }
    if (date > 15){
        if (water_usage <= 10){
            fines = 0;
        }
        else if (water_usage > 10 && water_usage <= 100){
            fines = DENDA_LBH10_KRNG100;
        }
        else {
            fines = DENDA_100_KEATAS;
        }
    }
    else {
        fines = 0;
    }
    if (consumer_class == 'r' || consumer_class == 'R'){
        total = ADMINISTRASI + BMP_R + fines + costs;
    }
    else{
        total = ADMINISTRASI + BMP_S + fines + costs;
    }
    converter = (int)total;
    converter_fines = (int)fines;
	
    if (fines - converter_fines == 0){
    	
    	sprintf (invoiceA, "Denda bulan ini adalah: Rp.%d\n", converter_fines);//memasukkan tulisan ke invoiceA
        printf ("Denda bulan ini adalah: Rp.%d\n", converter_fines);//print ke layar
    }
    else {
    	sprintf (invoiceB, "Denda bulan ini adalah: Rp.%.3f\n", fines);
        printf ("Denda bulan ini adalah: Rp.%.3f\n", fines);
    }
    if (total - converter == 0){
    	sprintf (invoiceC, "Harga bayar air saat ini adalah: Rp.%d\n", converter);
        printf ("Harga bayar air saat ini adalah: Rp.%d\n", converter);
    }
    else {
    	sprintf (invoiceD, "Harga bayar air saat ini adalah: Rp.%.3f\n", total);
        printf ("Harga bayar air saat ini adalah: Rp. %.3f\n", total);
    }
    
    printf("\nApakah Anda ingin mencetak struk?\n");
	printf ("Y(benar)/n(salah)\n");
	scanf(" %c", &pilihan);
	switch (pilihan){
        case 'Y':
        case 'y':
        	printf("Struk pembayaran telah dicetak di struk.txt\n");
            cetak_struk(invoiceA, invoiceB, invoiceC, invoiceD);
            break;
        case 'N':
        case 'n':
        	printf("Struk tidak dicetak\n");
            break;
        default:
            printf ("Tolong cek input anda lagi\n");
	}
    
    return 0;
}


//NEW FUNCTION ADDED TO "PRINT" THE RESULT, LITERALLY.
char cetak_struk(char invoiceA[100], char invoiceB[100], char invoiceC[100], char invoiceD[100]){
	FILE *fp;
	fp = fopen("struk.txt", "w");
	fputs (invoiceA, fp);
    fputs (invoiceB, fp);
    fputs ("\n", fp);
    fputs (invoiceC, fp);
    fputs (invoiceD, fp);
    fputs ("\n", fp);
    fclose(fp);
}
