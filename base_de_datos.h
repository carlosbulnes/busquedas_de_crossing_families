#include <curl/curl.h>
#include <dirent.h>


void descarga_base_datos(char *url, char *outfilename){
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl){   
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

void verifica_base_datos(int n, char *order_type){

	FILE *temp;

	if((temp = fopen(order_type, "r")) == NULL){
		printf("La base de datos no existe, descargando...\n");
		DIR *dir;
   		struct dirent *dent;
   		dir = opendir("order_types");

   		if(dir == NULL)
   			system("mkdir order_types");  

		char url[100] = "http://www.ist.tugraz.at/aichholzer/research/rp/triangulations/ordertypes/data/";
		switch(n){
			case 3: strcpy(order_type, "order_types/otypes03.b08"); strcat(url, "otypes03.b08"); break;
			case 4: strcpy(order_type, "order_types/otypes04.b08"); strcat(url, "otypes04.b08"); break;
			case 5: strcpy(order_type, "order_types/otypes05.b08"); strcat(url, "otypes05.b08"); break;
			case 6: strcpy(order_type, "order_types/otypes06.b08"); strcat(url, "otypes06.b08"); break;
			case 7: strcpy(order_type, "order_types/otypes07.b08"); strcat(url, "otypes07.b08"); break;
			case 8: strcpy(order_type, "order_types/otypes08.b08"); strcat(url, "otypes08.b08"); break;
			case 9: strcpy(order_type, "order_types/otypes09.b16"); strcat(url, "otypes09.b16"); break;
			case 10: strcpy(order_type, "order_types/otypes10.b16"); strcat(url, "otypes10.b16"); break;
		}
		descarga_base_datos(url, order_type);
	}else{
		fclose(temp);
	}
}