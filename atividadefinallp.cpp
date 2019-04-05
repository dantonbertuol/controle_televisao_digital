#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Canal {
short int num;
char bloqueado;
short int preco;
char nome[128];
char programa[1024];
} canal_t;

void menu (){
            printf (" ___________________________________________\n");
            printf ("| 0 - Sair                                  |\n");
            printf ("| 1 - Exibir programacao (listar canais)    |\n");
            printf ("| 2 - Adicionar novo canal na lista         |\n");
            printf ("| 3 - Remover canal da lista                |\n");
            printf ("| 4 - Exibir apenas os canais bloqueados    |\n");
            printf ("| 5 - Procurar canal (numero)               |\n");
            printf ("| 6 - Procurar canal (nome)                 |\n");
            printf ("| 7 - Gravar lista no disco (ASCII)         |\n");
            printf ("| 8 - Carregar lista do disco (ASCII)       |\n");
            printf ("| 9 - Gravar lista no disco (binario)       |\n");
            printf ("| 10 - Carregar lista do disco (binario)    |\n");
            printf ("|___________________________________________|\n");
        }

void opcao01 (canal_t* channels, int contador){
    int i;
    if (contador==0){
        printf ("Nenhum canal a ser exibido.\n");
    }
    for (i=0;i<contador;i++){
        printf ("%hd\t%x\t%hd\t%s\t%s\t\n\n",
                channels[i].num,
                channels[i].bloqueado,
                channels[i].preco,
                channels[i].nome,
                channels[i].programa);
    }
}

void opcao02(canal_t* channels, int &contador ){
    printf ("Para Adicionar um canal informe:\n");
    printf ("Numero do Canal: ");
        scanf("%hd",&channels[contador].num);
    printf ("Se o canal esta bloqueado: ");
            scanf("%x",&channels[contador].bloqueado);
    printf ("O valor para desbloquear o Canal: ");
            scanf("%hd",&channels[contador].preco);
    printf ("Nome do Canal: ");
    fflush(stdin);
        gets(channels[contador].nome);
    printf ("Programacao do Canal: ");
        gets(channels[contador].programa);
            contador++;
    }

void opcao03(canal_t* channels, int &contador){
    int excluir,i,j;
    printf ("Digite o numero do canal que deseja excluir: ");
        scanf ("%d",&excluir);
        for (i=0;i<contador;i++){
            if (channels[i].num==excluir && i!=contador-1){
                for (j=0;channels[i].nome[j]!='\0';j++){
                    channels[i].nome[j]=channels[contador-1].nome[j];
                }
                for (j=0;channels[i].programa[j]!='\0';j++){
                    channels[i].programa[j]=channels[contador-1].programa[j];
                }
                channels[i].bloqueado=channels[contador-1].bloqueado;
                channels[i].num=channels[contador-1].num;
                channels[i].preco=channels[contador-1].preco;

               memset(channels[contador-1].nome,NULL,sizeof(channels[contador-1].nome));
               memset(channels[contador-1].programa,NULL,sizeof(channels[contador-1].programa));
               channels[contador-1].bloqueado=NULL;
               channels[contador-1].num=NULL;
               channels[contador-1].preco=NULL;

               contador--;
            }
               if(channels[i].num==excluir && i==contador-1 ){
                   memset(channels[contador-1].nome,NULL,sizeof(channels[contador-1].nome));
                   memset(channels[contador-1].programa,NULL,sizeof(channels[contador-1].programa));
                                  channels[contador-1].bloqueado=NULL;
                                  channels[contador-1].num=NULL;
                                  channels[contador-1].preco=NULL;
                                  contador--;
               }
            }
}



void opcao04 (canal_t* channels,int contador){
    int i;
    printf ("Canais Bloqueados: \n\n");
    for (i=0;i<contador;i++)
        if (channels[i].bloqueado==1){
            printf ("%hd\t%x\t%hd\t%s\t%s\t\n\n",
                    channels[i].num,
                    channels[i].bloqueado,
                    channels[i].preco,
                    channels[i].nome,
                    channels[i].programa);
        }
}


void opcao05(canal_t* channels, int contador){
    int nrcanal=0,i;
    printf ("Digite o numero do canal que voce deseja ver: ");
        scanf ("%d",&nrcanal);
        printf ("\n");
    for (i=0;i<contador;i++){
        if (channels[i].num==nrcanal)
            printf ("%hd\t%x\t%hd\t%s\t%s\t\n\n",
                    channels[i].num,
                    channels[i].bloqueado,
                    channels[i].preco,
                    channels[i].nome,
                    channels[i].programa);
        }
}

void opcao06(canal_t* channels, int contador){
    int x=0;
    char nome[128];
    memset (nome,0,sizeof(nome));
        fflush(stdin);
        printf ("Digite o nome do canal que deseja encontrar: ");
            gets (nome);
    for (int i=0;i<contador;i++){
        x=0;
            for (int j=0;channels[i].nome[j]!= '\0';j++){
                for (int k=0,l=j;nome[k]!='\0';k++,l++){
                    if (channels[i].nome[l]==nome[k])
                        x=1;
                        else{
                            x=0;
                            break;
                    }
                }
                if (x==1){
                    printf ("%hd\t%x\t%hd\t%s\t%s\t\n\n",
                            channels[i].num,
                            channels[i].bloqueado,
                            channels[i].preco,
                            channels[i].nome,
                            channels[i].programa);
                    break;
                }
            }
    }

}

void opcao07(canal_t* channels, int contador){
    FILE* channel = fopen("C:\\teste\\ListaCanais.txt", "w+");
    for (int i=0;i<contador;i++){
    fwrite(&channels[i],sizeof(canal_t), 1, channel);
    }
    fclose(channel);

}

void opcao08 (canal_t* channels, int &contador){
    contador=0;
    memset(channels,NULL,sizeof(channels));
    FILE* channel = fopen("C:\\teste\\ListaCanais.txt", "r+");
    fseek(channel, 0, SEEK_END);//cursor para o final
    long int tamanho=ftell(channel);//tamanho do arquivo
    fseek(channel,0,SEEK_SET);//cursor para o inicio
    int elementos=tamanho/sizeof(canal_t);//nr de elementos
    fread(channels,sizeof(canal_t),elementos,channel);
    contador=elementos;
    fclose(channel);
}

void opcao09(canal_t* channels, int contador){
    FILE* channel = fopen("C:\\teste\\ListaCanaisBinario.bin", "w+b");
    for (int i=0;i<contador;i++){
    fwrite(&channels[i],sizeof(canal_t), 1, channel);
    }
    fclose(channel);
}

void opcao10(canal_t* channels, int &contador){
    contador=0;
    memset(channels,NULL,sizeof(channels));
    FILE* channel = fopen("C:\\teste\\ListaCanaisBinario.bin", "r+b");
    fseek(channel, 0, SEEK_END);
    long int tamanho=ftell(channel);
    fseek(channel,0,SEEK_SET);
    int elementos=tamanho/sizeof(canal_t);
    fread(channels,sizeof(canal_t),elementos,channel);
    contador=elementos;
    fclose(channel);
}

int main (){
int opcao=1,cont=0;
canal_t canais[100];

//Menu
do {
    menu();
    printf ("Escolha uma opcao do menu acima: ");
            scanf ("%d",&opcao);
            printf ("\n");
            while (opcao<0 || opcao>10){
                printf ("Opcao Invalida, escolha outra: ");
                        scanf("%d",&opcao);
                        printf ("\n");
            };


switch (opcao){

        case 1:
        opcao01(canais,cont);
            break;

        case 2:
        opcao02 (canais,cont);
             break;

        case 3:
        opcao03 (canais,cont);
            break;

        case 4:
        opcao04(canais,cont);
            break;

        case 5:
        opcao05 (canais,cont);
            break;

        case 6:
        opcao06(canais,cont);
            break;

        case 7:
        opcao07(canais,cont);
            break;

        case 8:
        opcao08(canais,cont);
            break;

        case 9:
        opcao09(canais,cont);
            break;

        case 10:
        opcao10(canais,cont);
            break;


}

} while (opcao!=0);



}


