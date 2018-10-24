/*  Giovanni Bruno Travassos de Carvalho - 11506849
    Trabalho de SO - Substituicao de Pagina*/

#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<iomanip>
#include<cstdlib>

using namespace std;


int arRef[1000] = {0}; //Array de Referencia
int tam;
int quadros;

int main(){
    int posicao= 0;
    int QFIFO[quadros]; //quadros
    int fFIFO = 0;//faltas
    int QOTIMO[quadros];//quadros
    int fOTIMO = 0;//faltas
    int QLRU[quadros];//quadros
    int fLRU = 0;//faltas
    int QDistancia[quadros];

	ifstream file("entradasSO2.txt");
	string line;
  	cout << fixed << setprecision(1);

  	while(getline(file, line)){
  		int refe; //reference
    	stringstream linhae(line);
    	while(linhae >> refe){
        	arRef[tam] = refe;
        	tam++;
    	}
	}
    quadros = arRef[0];
    int i;
    for (i = 1; i < tam; i++){
        arRef[i-1]=arRef[i];
    }
    tam--;

// FIFO------------------------------------------------------
    for (int i = 0; i < quadros; i++){
        QFIFO[i] = -1;
    }
    for (int i = 0; i < tam; i++){
        int flag = 0;
        for (int j = 0; j < quadros; j++){
        if (QFIFO[j] == arRef[i]){
            flag++;
        }
        }

        if (!flag){
            QFIFO[posicao] = arRef[i];
            posicao++;
            fFIFO++;
        }
        if (posicao >= quadros){
            posicao = 0;
        }
    }
    cout << "FIFO " << fFIFO << endl;

//Otimo----------------------------------------------
      for (int i = 0; i < quadros; i++){
        QOTIMO[i] = -1;
      }
      for (int i = 0; i < tam; i++){
        int d = 0; //Distancia
        int q = 0; //Quadros
        int flag = 0;

        for (int j = 0; j < quadros; j++){
            if (QOTIMO[j] == arRef[i]){
                flag++;
            }
        }

        if (!flag){
            for (int j = 0; j < quadros; j++){
                for (int k = i; k < tam; k++){
                    if (QOTIMO[j] == arRef[k]){
                        if (d < k){
                            q= j;
                            d = k;
                        }
                    k= tam;
                    }
              if((k == tam-1) && (QOTIMO[j] != arRef[k])){
                q= j;
                k= tam;
                j= quadros;
              }
            }
          }
        }
        if (!flag){
          QOTIMO[q] = arRef[i];
          fOTIMO++;
        }
      }
      cout << "OTM " << fOTIMO << endl;

//LRU----------------------------------------------------

      for (int i = 0; i < quadros; i++){
        QLRU[i] = -1;
      }
      for (int i = 0; i < tam; i++){
        int q = 0;
        int flag = 0;

        for (int j = 0; j < quadros; j++){
          if (QLRU[j] == arRef[i]){
            flag++;
          }
        }

        if (!flag){
          for (int j = 0; j < quadros; j++){
            for (int k = 0; k < i; k++){
              if (QLRU[j] == arRef[k]){
                QDistancia[j] = k;
              }
            }
          }
          for (int j = 1; j < quadros; j++){
            if (QDistancia[q] > QDistancia[j]){
              q = j;
            }
          }
          for (int j = 0; j < quadros; j++){
            if (QLRU[j] == -1){
              q = j;
              j = quadros;
            }
          }
        }
        if (!flag){
          QLRU[q] = arRef[i];
          fLRU++;
        }
      }
      cout << "LRU " << fLRU << endl;
    }
