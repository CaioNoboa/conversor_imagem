#include <iostream>
#include <fstream>

using namespace std;

// Structs
struct NomeArquivos
{
  string original;
  string modificado;
};
typedef struct NomeArquivos NomeArquivos;

struct DimensoesImagem
{
  int largura;
  int altura;
};
typedef struct DimensoesImagem DimensoesImagem;

// Function prototype
DimensoesImagem obterDimensoesImagem(string nomeArquivo);
char **alocarMatriz(DimensoesImagem dimensoesImagem);
void lerEProcessarArquivo(string nomeArquivo, DimensoesImagem dimensoesImagem, char **matriz);
char converterParaASCII(int indice);
void escreverArquivo(string nomeArquivo, DimensoesImagem dimensoesImagem, char **matriz);
void deletarMatriz(char **matriz, int linhas);

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    cout << "Erro ao inicializar arquivo!" << endl;
    cout << "Tente novamente seguindo o padrao: ./a.exe img1.foo img2.foo2" << endl;
    exit(-1);
  }

  NomeArquivos nomeArquivos;
  nomeArquivos.original = argv[1];
  nomeArquivos.modificado = argv[2];
  DimensoesImagem dimensoesImagem = obterDimensoesImagem(nomeArquivos.original);

  char **matriz = NULL;
  matriz = alocarMatriz(dimensoesImagem);

  // Preencher matriz pegando valores binarios do arquivo e convertendo para ASC
  lerEProcessarArquivo(nomeArquivos.original, dimensoesImagem, matriz);

  // Gravar matriz com valores convertidos em novo arquivo
  escreverArquivo(nomeArquivos.modificado, dimensoesImagem, matriz);

  // Deletar alocações dinâmicas
  deletarMatriz(matriz, dimensoesImagem.altura);

  cout << "Arquivo " << nomeArquivos.original << " convertido com sucesso em " << nomeArquivos.modificado << '!' << endl;

  return 0;
}

DimensoesImagem obterDimensoesImagem(string nomeArquivo)
{
  DimensoesImagem dimensoesImagem;
  ifstream arquivo(nomeArquivo, ios::in);

  if (!arquivo.is_open())
  {
    cout << "Erro ao abrir o arquivo " << nomeArquivo << '.' << std::endl;
    exit(-1);
  }

  arquivo >> dimensoesImagem.largura >> dimensoesImagem.altura;
  arquivo.close();
  return dimensoesImagem;
}

char **alocarMatriz(DimensoesImagem dimensoesImagem)
{
  char **matriz;
  matriz = new char *[dimensoesImagem.altura];

  if (matriz == NULL)
  {
    cout << "Falha na alocacao de memoria!" << endl;
    exit(-1);
  }

  for (int i = 0; i < dimensoesImagem.altura; i++)
  {
    matriz[i] = new char[dimensoesImagem.largura];

    if (matriz[i] == NULL)
    {
      cout << "Falha na alocacao de memoria!" << endl;
      exit(-1);
    }
  }

  return matriz;
}

void lerEProcessarArquivo(string nomeArquivo, DimensoesImagem dimensoesImagem, char **matriz)
{
  char caractereTemporario = ' ';
  int intTemporario = 0;
  int indice = 0;
  ifstream arquivo(nomeArquivo, ios::binary);

  if (!arquivo.is_open())
  {
    cout << "Erro ao abrir o arquivo " << nomeArquivo << '.' << std::endl;
    exit(-1);
  }

  arquivo >> dimensoesImagem.largura >> dimensoesImagem.altura;

  for (int i = 0; i < dimensoesImagem.altura; i++)
  {
    for (int j = 0; j < dimensoesImagem.largura; j++)
    {
      if (arquivo.read((char *)&caractereTemporario, sizeof(char)))
      {
        intTemporario = static_cast<unsigned char>(caractereTemporario);
        indice = intTemporario / 67;
        matriz[i][j] = converterParaASCII(indice);
      }
    }
  }

  arquivo.close();
}

char converterParaASCII(int indice)
{
  char listaConversao[67] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*', 'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm', 'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't', '/', '|', '(', ')', '1', '{', '}', '[', ']', '?', '-', '_', '+', '~', '<', '>', 'i', '!', 'l', 'I', ';', ':', ',', '"', '^', '`', '.'};
  return listaConversao[indice];
}

void escreverArquivo(string nomeArquivo, DimensoesImagem dimensoesImagem, char **matriz)
{
  ofstream arquivo(nomeArquivo, ios::out);

  if (!arquivo.is_open())
  {
    cout << "Erro ao abrir o arquivo " << nomeArquivo << '.' << std::endl;
    exit(-1);
  }

  arquivo << dimensoesImagem.largura << ' ' << dimensoesImagem.altura << endl;

  for (int i = 0; i < dimensoesImagem.altura; i++)
  {
    for (int j = 0; j < dimensoesImagem.largura; j++)
    {
      arquivo << matriz[i][j];
    }
    arquivo << endl;
  }

  arquivo.close();
}

void deletarMatriz(char **matriz, int linhas)
{
  for (int i = 0; i < linhas; i++)
  {
    delete[] matriz[i];
  }

  delete[] matriz;
}