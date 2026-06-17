# SimpleOS - VSFS Simulator

Este é um simulador de sistema de arquivos baseado na arquitetura **vsfs** (Very Simple File System) para a disciplina de Sistemas Operacionais.

## 🛠️ Como Compilar e Executar
```bash
cd ./vsfs
make clean && make
./vsfs

💻 Comandos Disponíveis

- format - Inicializa o disco virtual disco.img

- write <conteudo> - Grava um arquivo alocando inodes e blocos

- read <inode_id> - Exibe o conteúdo de um arquivo específico

- help - Exibe os todos os comandos

- list - Mostra a tabela de inodes ativos

- exit - Encerra o simulador com animação de colapso
