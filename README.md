# Sistema de Gerenciamento de Funcionários e Treinamentos

## 👥 Desenvolvedor

[<img loading="lazy" src="https://avatars.githubusercontent.com/u/173844994?v=4" width="115" alt="Erick Felix de Oliveira">](https://github.com/Erick8874)  
[Erick Felix de Oliveira](https://github.com/Erick8874)

---

## 📑 Índice

- [✨ Funcionalidades](#-funcionalidades)
- [⚙️ Arquitetura](#-arquitetura)
- [🗃️ Arquivos de Dados](#-arquivos-de-dados)
- [🚀 Como Rodar a Aplicação](#-como-rodar-a-aplicação)
- [💻 Tecnologias Utilizadas](#-tecnologias-utilizadas)
- [📂 Estrutura de Diretórios](#-estrutura-de-diretórios)
- [📐 Padrões Utilizados](#-padrões-utilizados)
- [😿 Principais Dificuldades](#-principais-dificuldades)
- [📝 Licença](#-licença)

---

## ✨ Funcionalidades

- **Adicionar Funcionário:** Permite adicionar um funcionário com nome, telefone e e-mail.
- **Listar Funcionários:** Exibe a lista de funcionários cadastrados.
- **Adicionar Treinamento:** Permite adicionar um treinamento com nome e data.
- **Listar Treinamentos:** Exibe a lista de treinamentos cadastrados.
- **Notificar Novos Treinamentos:** Mostra uma notificação de todos os treinamentos.
- **Atualizar Status de Treinamentos:** Atualiza o status dos treinamentos para indicar se estão atrasados.

---

## ⚙️ Arquitetura

1. **Validação de Dados:** Inclui funções para validar nomes, telefones, e-mails e datas. As validações garantem que os dados inseridos estejam no formato correto antes de serem armazenados.
2. **Gerenciamento de Funcionários:** Funções para adicionar e listar funcionários, com dados armazenados em `funcionarios.txt`. Esta funcionalidade permite a persistência dos dados entre execuções do programa.
3. **Gerenciamento de Treinamentos:** Funções para adicionar e listar treinamentos, com informações armazenadas em `treinamentos.txt`. Inclui o nome e a data do treinamento.
4. **Notificações e Atualizações:** Utiliza threads para:
   - **Notificar Novos Treinamentos:** Uma thread que lê o arquivo de treinamentos e notifica sobre novos treinamentos.
   - **Atualizar Status dos Treinamentos:** Outra thread que atualiza o status dos treinamentos para marcar aqueles que estão atrasados.
5. **Função Principal:** Um menu interativo que permite ao usuário escolher entre adicionar funcionários, listar funcionários, adicionar treinamentos, listar treinamentos, notificar novos treinamentos e atualizar o status dos treinamentos.

---

## 🗃️ Arquivos de Dados

- **`funcionarios.txt`**: Armazena informações dos funcionários, como nome, telefone e e-mail.
- **`treinamentos.txt`**: Armazena informações sobre os treinamentos, como nome e data.

---

## 🚀 Como Rodar a Aplicação

### Ambiente Local

1. **Clone o Repositório:** Clone o repositório com o comando:

    ```bash
    git clone <URL_DO_REPOSITORIO>
    cd <NOME_DO_DIRETORIO>
    ```

2. **Instale Dependências:** Certifique-se de ter o compilador GCC e a biblioteca pthread instalados. Em sistemas baseados em Debian, você pode instalar as ferramentas necessárias com:

    ```bash
    sudo apt update
    sudo apt install build-essential
    ```

3. **Prepare os Arquivos de Dados:** Crie os arquivos `funcionarios.txt` e `treinamentos.txt` no mesmo diretório que o executável:

    ```bash
    touch funcionarios.txt
    touch treinamentos.txt
    ```

4. **Compile o Código:** Compile o código-fonte com:

    ```bash
    gcc -o gerenciador gerenciador.c -lpthread
    ```

5. **Execute o Programa:** Após a compilação, execute o programa com:

    ```bash
    ./gerenciador
    ```

6. **Configuração Adicional:** Ajuste as permissões dos arquivos se necessário:

    ```bash
    chmod 644 funcionarios.txt
    chmod 644 treinamentos.txt
    ```

---

## 💻 Tecnologias Utilizadas

- **Linguagem:** C
- **Compilador:** GCC (GNU Compiler Collection)
- **Multithreading:** pthread (Biblioteca POSIX para threads)
- **Sistema Operacional:** Linux (para compilação e execução)

---

## 📂 Estrutura de Diretórios

- **`src/`**: Código-fonte do projeto.
  - `main.c`: Arquivo principal do programa.

---

## 📐 Padrões Utilizados

- **Padrão de Codificação C:** Segue as convenções padrão de codificação em C.
- **Validação de Entrada:** Funções para validar nomes, telefones, e-mails e datas.
- **Multithreading:** Uso de threads para notificações e atualizações assíncronas.

---

## 😿 Principais Dificuldades

- **Gerenciamento de Arquivos:** Garantir a integridade e o formato correto dos dados armazenados nos arquivos.
- **Sincronização de Threads:** Manter a consistência dos dados ao utilizar threads para operações assíncronas.
- **Validação de Entrada:** Implementar validações eficazes para garantir a entrada correta dos dados do usuário.
- **Interface Gráfica:** Tentativa de adicionar uma interface gráfica foi realizada, como a biblioteca GTK, mas não foi possível implementar.

---

## 📝 Licença

Este projeto está licenciado sob uma licença própria.

---

<div align="center">
   <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C" height="30" width="40">
   <img src="https://img.shields.io/badge/GCC-9B4F2F?style=for-the-badge&logo=gcc&logoColor=white" alt="GCC" height="30" width="40">
   <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Linux" height="30" width="40">
   <img src="https://img.shields.io/badge/Threading-000000?style=for-the-badge&logo=thread&logoColor=white" alt="Threading" height="30" width="40">
</div>
