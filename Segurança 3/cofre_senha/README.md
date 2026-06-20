# Cofre de Senhas Local com Criptografia em Repouso

Aplicação de linha de comando que implementa um cofre de senhas local
com autenticação por senha, hashing com salt e armazenamento
seguro em arquivo binário.

---

## Estrutura dos Arquivos

cofre_senha/
├── modulo_autenticacao.h   # Declarações de hash e salt
├── modulo_autenticacao.c   # Implementação do hash SHA-256 + salt
├── gerenciamento_arquivo.h # Declarações das estruturas e I/O
├── gerenciamento_arquivo.c # Implementação do salvamento em disco
└── main.c                  # Ponto de entrada e menu principal

---

## Requisitos

### Windows
- GCC MinGW-W64 — compilador C
- OpenSSL 3.x completo (não Light) — biblioteca de criptografia

### Instalação do OpenSSL
1. Acesse https://slproweb.com/products/Win32OpenSSL.html
2. Baixe Win64 OpenSSL v3.x.x (versão completa, ~281MB)
3. Execute o instalador e selecione "The Windows system directory"
4. Adicione ao PATH executando no PowerShell como administrador:

[System.Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\Program Files\OpenSSL-Win64\bin", "Machine")

---

## Como Compilar

Abra o terminal na pasta cofre_senha e execute:

gcc main.c modulo_autenticacao.c gerenciamento_arquivo.c -o cofre -I"C:\Program Files\OpenSSL-Win64\include" -L"C:\Program Files\OpenSSL-Win64\lib\VC\x64\MT" -lssl -lcrypto

Se compilado com sucesso, nenhuma mensagem de erro será exibida e o arquivo cofre.exe será gerado.

---

## Como Executar

.\cofre.exe

---

## Como Usar

### Primeiro acesso
Ao executar pela primeira vez, o cofre ainda não existe. O programa solicita
uma senha, gera um salt aleatório, calcula o hash SHA-256 e cria o
arquivo cofre.bin.

Cofre de Senhas
Senha Principal: senha123
Criando novo cofre

### Acessos seguintes
O programa lê o salt e o hash salvos em cofre.bin e verifica se a senha
digitada corresponde. Se incorreta, o acesso é negado.

Cofre de Senhas
Senha Principal: senha123
Cofre aberto. 2 entrada(s).

---

## Menu

1. Mostrar  → exibe todas as senhas salvas
2. Adicionar → solicita site, usuário e senha para salvar
0. Sair     → encerra o programa

---

## Conceitos Implementados

- Modulo de Autenticacao: geração de salt aleatório via RAND_bytes e hashing da senha com SHA-256. A senha nunca é armazenada diretamente
- Gerenciamento de Arquivo: estrutura de dados Entry e Vault, com funções de leitura e escrita binária em disco via fread/fwrite

---

## Observações

- A senha não pode conter espaços
- O arquivo cofre.bin é gerado na mesma pasta do executável
- Para resetar o cofre, basta apagar o arquivo cofre.bin