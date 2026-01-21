# Grafos - Graph Theory Implementation

Um projeto completo de implementação de Teoria dos Grafos em C++, incluindo múltiplos algoritmos clássicos, operações sobre grafos e visualização em formato DOT.

## 📋 Descrição

Este projeto implementa uma biblioteca robusta para manipulação e análise de grafos, oferecendo:

- **Representações múltiplas**: Matriz de adjacência, matriz de incidência e lista de adjacência
- **Algoritmos de busca**: BFS (Busca em Largura) e DFS (Busca em Profundidade)
- **Algoritmos de caminho mínimo**: Dijkstra, Bellman-Ford e Floyd-Warshall
- **Análise de propriedades**: Detecção de ciclos, verificação de conectividade, identificação de grafos eulerianos
- **Operações sobre grafos**: União, interseção, multiplicação e criação de subgrafos
- **Detecção de cliques maximais**: Algoritmo de Bron-Kerbosch
- **Coloração de grafos**: Identificação de grafos bipartidos
- **Visualização**: Exportação para formato DOT (Graphviz)

## 🚀 Funcionalidades

### Algoritmos Implementados

1. **Busca em Largura (BFS)**
   - Cálculo de distâncias
   - Verificação de conectividade
   - Encontrar menor caminho entre dois vértices

2. **Busca em Profundidade (DFS)**
   - Travessia em grafos dirigidos
   - Detecção de ciclos

3. **Algoritmos de Caminho Mínimo**
   - **Dijkstra**: Para grafos com pesos não-negativos
   - **Bellman-Ford**: Suporta pesos negativos e detecta ciclos negativos
   - **Floyd-Warshall**: Todos os pares de caminhos mínimos

4. **Análise de Grafos**
   - Identificação de tipo de grafo (Ciclo, Roda, Completo)
   - Verificação de grafo euleriano
   - Detecção de grafos bipartidos
   - Isomorfismo de grafos

5. **Cliques Maximais**
   - Algoritmo de Bron-Kerbosch para encontrar todos os cliques maximais

### Operações sobre Grafos

- **Adição/Remoção de arestas**
- **Multiplicação de grafos**
- **Criação de subgrafos**
- **Comparação de isomorfismo**

## 🛠️ Compilação e Execução

### Requisitos

- Compilador C++ com suporte a C++11 ou superior
- Sistema operacional Windows (para funcionalidades de cores no console)
- Graphviz (opcional, para visualização dos grafos)

### Compilar

```bash
g++ -std=c++11 GRAFO.cpp -o GRAFO.exe
```

### Executar

```bash
./GRAFO.exe
```

## 📊 Visualização

O programa gera automaticamente um arquivo `grafos.dot` que pode ser visualizado usando Graphviz:

```bash
dot -Tpng grafos.dot -o grafos.png
```

O arquivo DOT inclui:
- Coloração dos vértices
- Destaque do menor caminho (em vermelho)
- Agrupamento de subgrafos

## 💻 Estrutura do Código

### Classe Principal: `Grafo`

```cpp
class Grafo {
private:
    int V;                          // Número de vértices
    vector<vector<int>> M;          // Matriz de adjacência
    vector<vector<bool>> MI;        // Matriz de incidência
    vector<vector<int>> L;          // Lista de adjacência
    int A;                          // Número de arestas
    vector<pair<int,int>> G;        // Graus e cores dos vértices
    
public:
    // Métodos principais
    void read(int m);               // Ler grafo
    bool update();                  // Atualizar propriedades
    void print();                   // Imprimir informações
    
    // Algoritmos de busca
    vector<int> BFS_com_distancia(int start);
    vector<int> DFSdirigido(int start);
    vector<int> shortpathBFS(int start, int end);
    
    // Algoritmos de caminho mínimo
    vector<int> dijkstra(int start);
    vector<int> BellmanFord(int origem);
    vector<vector<int>> floydwarshall();
    
    // Análise
    bool ConexoBFS();
    bool ciclodirigido();
    bool isomorf(const Grafo& outro) const;
    
    // Operações estáticas
    static Grafo preset(int i);
    static Grafo grafop(int o, const Grafo& A, const Grafo& B);
    static Grafo subgrafo(const Grafo& A, const vector<int>& S);
};
```

## 📝 Exemplos de Uso

### Criar um Grafo Pré-definido

```cpp
Grafo G = Grafo::preset(0);  // Cria um grafo pré-definido
G.print();                    // Exibe informações
```

### Encontrar Menor Caminho

```cpp
vector<int> caminho = G.shortpathBFS(0, 4);  // Menor caminho do vértice 0 ao 4
```

### Verificar Conectividade

```cpp
bool conexo = G.ConexoBFS();  // Verifica se o grafo é conexo
```

### Executar Dijkstra

```cpp
vector<int> distancias = G.dijkstra(0);  // Distâncias a partir do vértice 0
```

## 🎨 Características Visuais

- **Cores no console**: Vértices são exibidos com cores diferentes baseadas na coloração do grafo
- **Exportação DOT**: Visualização gráfica com destaque para:
  - Coloração de vértices
  - Menor caminho destacado em vermelho
  - Agrupamento de subgrafos

## 📚 Conceitos de Teoria dos Grafos Implementados

- **Grafo Euleriano**: Todos os vértices têm grau par
- **Grafo Bipartido**: Pode ser colorido com apenas 2 cores
- **Clique Maximal**: Subgrafo completo que não pode ser estendido
- **Isomorfismo**: Dois grafos com a mesma estrutura
- **Tipos de Grafos**: Ciclo, Roda, Completo

## 🔧 Funcionalidades Avançadas

### Algoritmo de Bron-Kerbosch

Encontra todos os cliques maximais no grafo, útil para:
- Análise de redes sociais
- Detecção de comunidades
- Problemas de agrupamento

### Detecção de Ciclos

- Em grafos dirigidos: Usando DFS com pilha de recursão
- Identificação de ciclos negativos: No algoritmo de Bellman-Ford

### Múltiplas Representações

O grafo mantém simultaneamente três representações:
1. **Matriz de Adjacência**: Acesso O(1), espaço O(V²)
2. **Lista de Adjacência**: Eficiente para grafos esparsos
3. **Matriz de Incidência**: Útil para análise de arestas

## 🤝 Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para:

- Reportar bugs
- Sugerir novas funcionalidades
- Melhorar a documentação
- Adicionar novos algoritmos

## 📄 Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

## ✨ Autor

**Samuel Pinho**

## 🙏 Agradecimentos

Este projeto foi desenvolvido como parte do estudo de Teoria dos Grafos e Algoritmos, implementando conceitos clássicos da Ciência da Computação.

---

**Nota**: O código inclui grafos pré-definidos para testes e demonstrações. Execute o programa para ver exemplos de todos os algoritmos em ação!
