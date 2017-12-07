#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

enum Opcao{
	CADASTRAR=1,
	MODIFICAR,
	EXCLUIR,
	PESQUISAR,
	LISTAR,
	SAIR
};

enum Erro{
	SUCESSO,
	ERR_ARQUIVO_NAO_ABERTO,
	ERR_ESCOLHA_NAO_VALIDA
};

struct pokemon{
		int codigo;
		char nome[15];
		char tipo[10];
		float altura;
		float peso;
		char sexo[5];
};

enum Erro cadastrar(){
	system("cls");
	struct pokemon temp;
	
	FILE*arquivo;
	arquivo=fopen("cadastro_pokedex.db","ab+");
	
	if(arquivo==NULL){
		printf("Falha ao abrir o documento, tente novamente.");
		sleep(3);
		return ERR_ARQUIVO_NAO_ABERTO;
	}
	
	printf("\nDigite o código do pokemon: ");
	fflush(stdin);
	scanf("%i",&temp.codigo);
	printf("Digite o nome do pokemon: ");
	fflush(stdin);
	scanf("%s",&temp.nome);
	printf("Digite o tipo do pokemon: ");
	fflush(stdin);
	scanf("%s",&temp.tipo);
	printf("Digite a altura(em Metros) do pokemon: ");
	fflush(stdin);
	scanf("%f",&temp.altura);
	printf("Digite a peso(em Quilograma) do pokemon: ");
	fflush(stdin);
	scanf("%f",&temp.peso);
	printf("Digite o sexo(macho ou fêmea) do pokemon: ");
	fflush(stdin);
	scanf("%s",&temp.sexo);
	
	fwrite(&temp, sizeof(struct pokemon), 1, arquivo);
	printf("\n\t\tCADASTRADO COM SUCESSO");
	fclose(arquivo);	
	getch();
	return SUCESSO;
}

enum Erro pesquisar(const int *escolha){
	system("cls");
	
	int tam = 0,i;
	int comp_codigo;
	char comp_nome[15];
	char comp_tipo[10];
	
	FILE*arquivo;
	arquivo=fopen("cadastro_pokedex.db","rb");
	
	if(arquivo==NULL){
		printf("Falha ao abrir o documento, tente novamente.");
		sleep(3);
		return ERR_ARQUIVO_NAO_ABERTO;
	}
		
	fseek(arquivo,0,SEEK_END);
	tam = ftell(arquivo);
	tam = tam / sizeof(struct pokemon);
	fseek(arquivo,0,SEEK_SET);
	
	struct pokemon aux[tam]; 
	
	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct pokemon),1,arquivo);
	}
	
	if(*escolha==1){
		printf("\nDigite o código do pokemon que deseja pesquisar: ");
		scanf("%i",&comp_codigo);
		for(i=0;i<tam;i++){
			if(aux[i].codigo==comp_codigo){
				printf("\ncódigo: %i\n",aux[i].codigo);
				printf("Nome:   %s\n",aux[i].nome);
				printf("Tipo:   %s\n",aux[i].tipo);
				printf("Altura: %.1f\n",aux[i].altura);
				printf("Peso:   %.1f\n",aux[i].peso);
				printf("Sexo:   %s\n",aux[i].sexo);
			}
		}
	}else if(*escolha==2){
		printf("\nDigite o nome do pokemon que deseja pesquisar: ");
		scanf("%s",&comp_nome);
		for(i=0;i<tam;i++){
			if(strcmp(aux[i].nome,comp_nome) == 0){
				printf("\ncódigo: %i\n",aux[i].codigo);
				printf("Nome:   %s\n",aux[i].nome);
				printf("Tipo:   %s\n",aux[i].tipo);
				printf("Altura: %.1f\n",aux[i].altura);
				printf("Peso:   %.1f\n",aux[i].peso);
				printf("Sexo:   %s\n",aux[i].sexo);
			}
		}	
	}else if(*escolha==3){
		printf("\nDigite o tipo do pokemon que deseja pesquisar: ");
		scanf("%s",&comp_tipo);
		for(i=0;i<tam;i++){
			if(strcmp(aux[i].tipo,comp_tipo) == 0){
				printf("\nCódigo: %i\n",aux[i].codigo);
				printf("Nome:   %s\n",aux[i].nome);
				printf("Tipo:   %s\n",aux[i].tipo);
				printf("Altura: %.1f M\n",aux[i].altura);
				printf("Peso:   %.1f Kg\n",aux[i].peso);
				printf("Sexo:   %s\n",aux[i].sexo);
			}
		}	
	}else{
		printf("\nEscolha não válida");
			getch();
		return ERR_ESCOLHA_NAO_VALIDA;
	}
		
	fclose(arquivo);
	getch();
	return SUCESSO;
}

enum Erro modificar(const int *comp_codigo){
	system("cls");
	int tam,i,membro;
	
	FILE*arquivo;
	arquivo=fopen("cadastro_pokedex.db","rb");
	
	if(arquivo==NULL){
		printf("Falha ao abrir o documento, tente novamente.");
		getch();
		return ERR_ARQUIVO_NAO_ABERTO;
	}	
	
	fseek(arquivo,0,SEEK_END);
	tam = ftell(arquivo);
	tam = tam / sizeof(struct pokemon);
	fseek(arquivo,0,SEEK_SET);

	struct pokemon aux[tam];
	
	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct pokemon),1,arquivo);
	}
	
	for(i=0;i<tam;i++){
		if(aux[i].codigo==*comp_codigo){
			printf("\nDigite o código correspondente a característica que deseja alterar:\n");
			printf("1-Nome\n");
			printf("2-Tipo\n");
			printf("3-Altura\n");
			printf("4-Peso\n");
			printf("5-Sexo\n");
			printf("\nDigite o código correspondente a opção desejada: ");
			scanf("%d", &membro);
			switch (membro){
	    		case 1:
	    	  		printf("\nDigite o nome do pokemon: ");
					fflush(stdin);
					scanf("%s",&aux[i].nome);
	       			break;
	 	    	case 2:
					printf("\nDigite o tipo do pokemon: ");
					fflush(stdin);
					scanf("%s",&aux[i].tipo);
	    			break;
	      		case 3:
					printf("\nDigite a altura(em Metros) do pokemon: ");
					fflush(stdin);
					scanf("%f",&aux[i].altura);
	    			break; 
	    		case 4:
					printf("\nDigite a peso(em Quilograma) do pokemon: ");
					fflush(stdin);
					scanf("%f",&aux[i].peso);
	    			break;
	    		case 5:
	    			printf("\nDigite o sexo(macho ou fêmea) do pokemon: ");
					fflush(stdin);
					scanf("%s",&aux[i].sexo);
	    			break;
	  			default:
					printf("\nEscolha não válida");
					getch();
					return ERR_ESCOLHA_NAO_VALIDA;
			}						
		}
	}
	
	for(i=0;i<tam;i++){
		if(aux[i].codigo==*comp_codigo){
			freopen("cadastro_pokedex.db","wb",arquivo);
			
			for(i=0;i<tam;i++){
				fwrite(&aux[i], sizeof(struct pokemon), 1, arquivo);
			}
			
			fclose(arquivo);
			printf("\n\tITEM MODIFICADO COM SUCESSO");
			getch();
			return SUCESSO;
		}
	}
	
	getch();
	fclose(arquivo);
	return SUCESSO;
}

enum Erro excluir(const int *escolha){
	system("cls");
	int tam,i,j=0;
	int comp_codigo;
	char comp_nome[15];
	
	FILE*arquivo;
	arquivo=fopen("cadastro_pokedex.db","rb");
	
	if(arquivo==NULL){
		printf("Falha ao abrir o documento, tente novamente.");
		getch();
		return ERR_ARQUIVO_NAO_ABERTO;
	}	
	
	fseek(arquivo,0,SEEK_END);
	tam = ftell(arquivo);
	tam = tam / sizeof(struct pokemon);
	fseek(arquivo,0,SEEK_SET);

	struct pokemon aux[tam];
	struct pokemon final[tam];	
	
	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct pokemon),1,arquivo);
	}
	
	if(*escolha==1){
		printf("\nDigite o código do pokemon que deseja excluir: ");
		scanf("%i",&comp_codigo);
		for(i=0;i<tam;i++){
			if(aux[i].codigo==comp_codigo){
			}else{
				final[j]=aux[i];
				j++;
			}
		}
		
		for(i=0;i<tam;i++){
			if(aux[i].codigo==comp_codigo){
				freopen("cadastro_pokedex.db","wb",arquivo);
				for(i=0;i<tam-1;i++){
					fwrite(&final[i], sizeof(struct pokemon), 1, arquivo);
				}
				
				fclose(arquivo);
				printf("\n\tITEM REMOVIDO COM SUCESSO");
				getch();
				return SUCESSO;
			}
		}
				
	}else if(*escolha==2){
		printf("\nDigite o nome do pokemon que deseja excluir: ");	
		scanf("%s",&comp_nome);
		for(i=0;i<tam;i++){
			if(strcmp(aux[i].nome,comp_nome) == 0){
			}else{
				final[j]=aux[i];
				j++;
			}
			}

		for(i=0;i<tam;i++){
			if(strcmp(aux[i].nome,comp_nome) == 0){
				freopen("cadastro_pokedex.db","wb",arquivo);
				for(i=0;i<tam-1;i++){
					fwrite(&final[i], sizeof(struct pokemon), 1, arquivo);
				}
				
				fclose(arquivo);
				printf("\n\tITEM REMOVIDO COM SUCESSO");
				getch();
				return SUCESSO;
			}
		}
	
	}else{
		printf("Escolha não válida");
		getch();
		return ERR_ESCOLHA_NAO_VALIDA;
	}
	
	getch();
	fclose(arquivo);
	return SUCESSO;
}

enum Erro listar(){
	system("cls");
	
	FILE*arquivo;
	arquivo=fopen("cadastro_pokedex.db","rb");
	
	if(arquivo==NULL){
		printf("Falha ao abrir o documento, tente novamente.");
		sleep(3);
		return ERR_ARQUIVO_NAO_ABERTO;
	}
	
	int tam = 0,i;
	int comp_codigo;
	char comp_nome[15];
	
	fseek(arquivo,0,SEEK_END);
	tam = ftell(arquivo);
	tam = tam / sizeof(struct pokemon);
	fseek(arquivo,0,SEEK_SET);
	
	struct pokemon aux[tam]; 

	for(i=0;i<tam;i++){
		fread(&aux[i],sizeof(struct pokemon),1,arquivo);
	}

	for(i=0;i<tam;i++){
	printf("\ncódigo: %i\n",aux[i].codigo);
	printf("Nome:   %s\n",aux[i].nome);
	printf("Tipo:   %s\n",aux[i].tipo);
	printf("Altura: %.1f M\n",aux[i].altura);
	printf("Peso:   %.1f Kg\n",aux[i].peso);
	printf("Sexo:   %s\n",aux[i].sexo);
	}	
	
	fclose(arquivo);
	getch();
	return SUCESSO;
}

enum Opcao menu(){
	int opc;
	do{
	printf("\t\tPOKEDEX\n");
	printf("\nEscolha uma das opções:\n\n");
	printf("1-Cadastrar \n");
	printf("2-Modificar\n");
	printf("3-Excluir\n");
	printf("4-Pesquisar\n");
	printf("5-Listar\n");
	printf("6-Sair\n");
	printf("\nDigite o código correspondente a opção desejada: ");
	fflush(stdin);
	scanf("%i",&opc);
	
	switch (opc){
    	case CADASTRAR :
			cadastrar();
			system("cls");
    		break;
      	case MODIFICAR :
      		system("cls");
 	    	printf("\nDigite o código do pokemon que deseja alterar? ");
			scanf("%i",&opc);
      		modificar(&opc);
      		system("cls");
       		break;
 	    case EXCLUIR :
 	    	system("cls");
 	    	printf("\nEscolha o método de exclusão\n\n1-Por código\n2-Por nome\n\nQual a opção desejada? ");
			scanf("%i",&opc);
    		excluir(&opc);
			system("cls");
    		break;
      	case PESQUISAR :
		  	system("cls");
      		printf("\nEscolha o método de pesquisa\n\n1-Por código\n2-Por nome\n3-Por tipo\n\nQual a opção desejada? ");
			scanf("%i",&opc);
        	pesquisar(&opc);
			system("cls");
    		break; 
    	case LISTAR :
    		listar();
    		system("cls");
    		break;
		case SAIR :
  			exit(0);
  			break;
  		default :
  			printf("\nOpção inválida, digite qualquer tecla para tentar novamente.");
  			getch();
       		system("cls");
		}
	}while(opc!=6);
	return SUCESSO;
}

void main(){
	setlocale(LC_ALL, "");
	system("COLOR 0A");
	menu();
}
