# Conversor Foo desenvolvido para a disciplina de Técnicas de Programação II do Centro Universitário Barão de Mauá

  - Caio Salvador Noboa - 2201926

  ## Introdução
    O presente Algoritmo contempla a leitura de um arquivo, conversão dos dados e escrita em um novo arquivo.

    O arquivo de armazenamento de uma imagem com extensão .foo segue o seguinte padrão:
      - Uma largura, formatada como caracteres ASCII em decimal.
      - Espaço em branco.
      - Uma altura, novamente em decimal ASCII.
      - Um caractere de final de linha.
      - Uma sequência de bytes representando, respectivamente, cada pixel da imagem. Obs: cada byte pode assumir valores entre 0 e 255.

    Para criar banners, é preciso converter os arquivos de extensão .foo para .foo2.
    Os arquivos com extensão .foo2 devem possuir a seguinte estrutura:
      - Uma largura, formatada como caracteres ASCII em decimal.
      - Espaço em branco.
      - Uma altura, novamente em decimal ASCII.
      - Um caractere de final de linha.
      - Uma sequência de caracteres ASCII com diferentes densidades representando, respectivamente, cada pixel da imagem conforme especificação a seguir:
        $@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,"^`.

  ## Inicialização
    No prompt de comando, na pasta que contém o arquivo driver.cpp rode:
      `g++ driver.cpp -o conversor.exe`
      `./conversor.exe nomeImagemASerConvertida.foo nomeImagemGerada.foo2`
