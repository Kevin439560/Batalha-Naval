#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<limits>
#define TAM 10

using namespace std;


void limpa_tela();
void menu_inicial(); 
void inicia_tabu(char [TAM][TAM], char [TAM][TAM]);
void exibe_tabu(char tabuleiro[TAM][TAM], char tabu_mask[TAM][TAM], bool);
void ver_tiro(char tabuleiro[TAM][TAM], int, int);
void jogo(string);

int main(){

    char branco[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    cout << branco;
    srand((unsigned)time(NULL));

    menu_inicial();

}

void limpa_tela(){

    system("CLS");

}

void menu_inicial(){

    int opcao;

    do{
  
        limpa_tela();
        cout << "\nBem vindo ao Jogo Batalha Naval!";  
        string nome;
        cout << "\n\n[1] Jogar";
        cout << "\n[2] Sobre";
        cout << "\n[3] Sair";
        cout << "\n\nEscolha uma opcao e aperte Enter\n";

        cin >> opcao;

        switch(opcao){

            case 1:

                cout << "\nInforme seu nome, jogador\n";

                cin >> nome;

                jogo(nome);
                
                break;

            case 2:

                limpa_tela();

                cout << "Descricao:";

                cout << "O jogo consiste em escolher posicoes do tabuleiro e o seu objetivo eh acertar os barcos\n";
                cout << "para conseguir a maior quantidade de pontos possivel.";
                cout << "\n\nOs barcos pequenos ocupam um espaco enquanto os medios ocupam 3 espacos.";

                cout << "\n\nJogo criado por Kevin em 2022\n\n";
                
                system("pause");

                break;

            case 3:


                cout << "\nSaindo!!!";

                break;

            default:

                cout << "Escolha Invalida";

                exit(EXIT_FAILURE);
                break;
        }
    }while(opcao < 3);
}

void inicia_tabu(char tabuleiro[TAM][TAM], char tabu_mask[TAM][TAM]){

    int linha, coluna;

    for(linha = 0; linha < 10; linha++){

        for(coluna = 0; coluna < 10; coluna ++){

            tabuleiro[linha][coluna] = 'A';

            tabu_mask[linha][coluna] = '*';
        }
    } 

}

void exibe_tabu(char tabuleiro[TAM][TAM], char tabu_mask[TAM][TAM], bool gabarito){

    char blue[] = { 0x1b, '[', '1', ';', '3', '6', 'm', 0 };
    char cinza[] = { 0x1b, '[', '1', ';', '3', '0', 'm', 0 };
    char amarelo[] = { 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
    char branco[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    int linha, coluna;

    for(linha = 0; linha < 10; linha++){

        cout << linha << " ";

        for(coluna = 0; coluna < 10; coluna ++){

            switch(tabu_mask[linha][coluna]){

                case 'A':

                    cout << blue << " " << tabu_mask[linha][coluna] << branco;

                    break;
                case 'P':
                
                    cout << amarelo << " " << tabu_mask[linha][coluna] << branco;

                    break;
                case 'M':

                    cout << cinza << " " << tabu_mask[linha][coluna] << branco;
                    break;
                default:

                    cout << " " << tabu_mask[linha][coluna];    
                    break;
            }   


        }

        cout << "\n";
    }

    cout << "   ";
    for(int i = 0; i < coluna; i++){

        cout << i << " ";
    }

    cout << "\n\n";
    if(gabarito == true){

        for(linha = 0; linha < TAM; linha++){
            
            for(coluna = 0; coluna < TAM; coluna++){

                switch(tabuleiro[linha][coluna]){

                    case 'A':

                        cout << blue << " " << tabuleiro[linha][coluna] << branco;

                        break;
                    case 'P':
                
                        cout << amarelo << " " << tabuleiro[linha][coluna] << branco;

                        break;
                    case 'M':

                        cout << cinza << " " << tabuleiro[linha][coluna] << branco;
                        break;
                    default:

                        cout << " " << tabu_mask[linha][coluna];    
                        break;
                }   
                
            }

            cout << "\n";

        }

    }


}

void por_barcos(char tabuleiro[TAM][TAM]){

    int qtt_pos = 0, numbarcos = 10;

    while(qtt_pos < numbarcos){

        int linha = rand() % 10;

        int coluna = rand() % 10;

        if(tabuleiro[linha][coluna] == 'A'){

            tabuleiro[linha][coluna] = 'P';

            qtt_pos++;

            
        }
        
    }

    qtt_pos = 0;

    while(qtt_pos < 3){

        int linha = rand() % 10;

        int coluna = rand() % 9;


        if(coluna == 0){

            while(coluna == 0){

                coluna = rand() % 9;

            }

        }

        if(tabuleiro[linha][coluna] == 'A' && tabuleiro[linha][coluna - 1] == 'A' && tabuleiro[linha][coluna + 1] == 'A' && tabuleiro[linha - 1][coluna] == 'A' && tabuleiro[linha + 1][coluna] == 'A'){

            tabuleiro[linha][coluna] = 'M';

            tabuleiro[linha][coluna - 1] = 'M';

            tabuleiro[linha][coluna + 1] = 'M';

            qtt_pos++;

            
        }
        
    }



}

void ver_tiro(char tabuleiro[TAM][TAM], int linha, int coluna, int * pontos, string * mensagem){
 
        switch(tabuleiro[linha][coluna]){

            case 'P':
                
                *pontos += 10;

                *mensagem = "\nVoce acertou um barco pequeno!\n\n";

                break;

            case 'M':

                *pontos += 10;

                *mensagem = "\nVoce acertou um barco medio.(Se atente as laterais!)\n\n";

                break;

            case 'A':

                *mensagem = "\nVoce acertou a agua!\n\n";

                break;

        }

}

void jogo(string nome){   

    char tabuleiro[TAM][TAM], tabu_mask[TAM][TAM];

    int opcao, linha, coluna, pontos = 0, tent_feitas = 0, tent_totais = 10;

    cout << "\nJogo iniciado!!\n\n";
    
    string mensagem = "";

    inicia_tabu(tabuleiro, tabu_mask);

    por_barcos(tabuleiro);

    do{

        limpa_tela();

        exibe_tabu(tabuleiro, tabu_mask, false);

        cout << mensagem;

        linha = coluna = -1;

        while((linha < 0 || linha > TAM - 1) || (coluna < 0 || coluna > TAM - 1)){
            
            cout << "\nPontos: " << pontos;

            cout << "\nTentativas Restantes: " << tent_totais - tent_feitas;
        
            cout << "\n\n" << nome << ", digite uma linha:\n";

            cin >> linha; 

            while (cin.fail()) { 
                
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                cout << "Por favor, digite um numero valido (linha) :\n";
                cin >> linha; 
            }

            cout << "Agora digite uma coluna:\n";

            cin >> coluna;

            while(cin.fail()) { 
                
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                cout << "Por favor, digite um numero valido (coluna) :\n";
                cin >> coluna; 
            }

        }

        ver_tiro(tabuleiro, linha, coluna, &pontos, &mensagem);

        tabu_mask[linha][coluna] = tabuleiro[linha][coluna];

        tent_feitas++;

    }while(tent_totais > tent_feitas);

    limpa_tela();

    exibe_tabu(tabuleiro, tabu_mask, true);

    cout << "\nSua pontuacao: " << pontos << " pontos!\n";

    cout << "O que deseja fazer agora?\n[1]Jogar Novamente\n[2]Voltar para o Menu\n";

    cin >> opcao;

    switch(opcao){

        case 1:

            jogo(nome);

            break;
        case 2:
        
            break;

        default: 
            
            cout << "nao entendi ;-;";

            break;

    }
    

}
