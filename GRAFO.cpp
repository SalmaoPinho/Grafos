#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <fstream>
#include <windows.h>
#include <queue>
#include <stack>
#include <climits>
#include <set>
using namespace std;
string type[] =
{
	[0] = "Indefinido",
	[1] = "Ciclo",   // C
	[2] = "Roda",    // W
	[3] = "Completo" // K
};
vector<string> colors =
{
	"red",
	"green",
	"blue",
	"orange",
	"purple",
	"gold",
	"cyan",
	"pink",
	"magenta",
	"deepskyblue"
};


#ifdef _WIN32
#include <windows.h>
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void resetColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Cinza claro padrC#o
}
#else
void setColor(int color) {
	// Mapear o nC:mero para cC3digos ANSI (apenas os 7 bC!sicos)
	const int ansiColors[] = {30, 31, 32, 33, 34, 35, 36, 37};
	if (color >= 0 && color < 8)	cout << "\033[" << ansiColors[color] << "m";
}
void resetColor()
{
	cout<<"\033[0m";
}
#endif


int c = 0; // Contador global para identificaC'C#o de grafos
int cv=0;
string fin = "graph G {\nlabel=\"Grafos\";\n";

void BronKerbosch(const vector<vector<int>>& M, vector<int> A, vector<int> PC, vector<int> EX, vector<vector<int>>& cliques)
{
	if (PC.empty() && EX.empty())
	{	//ja explorou tudo, por na matriz final
		cliques.push_back(A);
		return;
	}
	// Fazemos uma cC3pia de P para iterar enquanto alteramos o original
	vector<int> P2 = PC;
	for (int v : P2)
	{
		vector<int> P2,X2,A2 = A;//prepara novos conjuntos P e X contendo apenas os vizinhos de v, adiciona o vC)rtice v ao clique atual
		A2.push_back(v);
		for (int j:PC)	if (M[v][j]) P2.push_back(j);//vC)rtices de PC que sC#o vizinhos de v
		for (int j:EX)	if (M[v][j]) X2.push_back(j);//vC)rtices de EX que sC#o vizinhos de v
		// Chamada recursiva com v adicionado ao clique e vizinhos filtrados
		BronKerbosch(M, A2, P2, X2, cliques);
		//remover V de PC e o adicionar em EX
		PC.erase(remove(PC.begin(),PC.end(),v),PC.end());
		EX.push_back(v);
	}
};

class Grafo
{
private:
	int V; // Numero de vertices
	vector<vector<int>> M; // Matriz de adjacencia
	vector<vector<bool>> MI; // Matriz de incidC*ncia
	vector<vector<int>> L; // Lista de AdjacC*ncia
	int A; // Numero de arestas
	vector<pair <int,int>> G; // Graus/Cor dos vertices
	vector<vector<int>> cliques;
	vector<int> Q; // Quantidade de valores
	int T; // Grau total
	int QC;//Total de cores
	bool EU;//Euleriano
	int E; // Entrada
	int i, j, y; // Contadores


	bool dfsciclo(int i, vector<bool>& visitados, vector<bool>& pilha)
	{
		visitados[i] = true;
		pilha[i] = true;

		for (int vizinho : L[i])
		{
			if (!visitados[vizinho])
			{
				if (dfsciclo(vizinho, visitados, pilha)) return true;
			}
			else if (pilha[vizinho]) return true;
		}

		pilha[i] = false;
		return false;
	}
public:
	// Construtor
	Grafo(int n) : V(n), T(0)
	{
		M.resize(n, vector<int>(n, 0));
		Q.resize(1,0);
	}
	// Atualiza as propriedades do grafo
	bool update()
	{
		T=A=QC=0;
		cliques.clear();
		L.clear();
		MI.clear();
		G.resize(V, pair<int, int>(0, 0));
		for (i = 0; i < V; i++)
		{
			vector<int> VI(i);
			for (j = i; j < V; j++)
			{
				E = M[i][j];
				// Atualiza graus e matriz de incidC*ncia
				if (E)
				{

					G[i].first++;
					G[j].first++;

					//coloracao
					if (G[j].second==G[i].second)	G[j].second++;
					if (QC<G[j].second) QC=G[j].second;
					y=0;
					for (y=0; y<E; y++)Q.push_back(0);
					Q[E]+=2;
					T += 2;
					vector<bool> T(V, false);
					T[i] = true;
					T[j] = true;
					MI.push_back(T);
					VI.push_back(j);
				}
			}
			L.push_back(VI);
		}
		A = T / 2;
		// Determina o tipo do grafo
		y = 0; // k
		bool ch = true;
		EU = true;
		for (i = 0; i < V && y == 0; i++) {
			if (G[i].first == V - 1) y = 2; // roda
			if (G[i].first != 2) ch = false;
			if (G[i].first % 2 == 1 || G[i].first == 0) EU = false;
		}
		if (ch) y = 1; // ciclo
		else if (y == 0 && EU) y = 3;


		vector<int> R, P, X;
		for (int i = 0; i < V; ++i) P.push_back(i);
		BronKerbosch(M, R, P, X, cliques);

		return true;
	}
	// FunC'C#o para ler o grafo
	void read(int m)
	{
		if (m)
		{
			printf("Insira a matriz de incidencia do grafo (somente a parte superior, incluindo diagonal principal):\n");
			for (i = 0; i < V; i++)
			{
				for (j = i; j < V; j++)
				{	//Apenas a diagonal superior
					cin >> E;
					M[i][j] = M[j][i] = E;
				}
			}
		}
		else
		{
			printf("Insira cada aresta, digite -1 quando acabar\n");
			cin>>i;
			while(i!=-1)
			{
				cin>>j;
				M[i][j]=M[j][i]=true;
				cin>>i;
			}
		}
		update();
	}
	// FunC'C#o para verificar isomorfismo
	bool isomorf(const Grafo& outro) const
	{
		if (V != outro.V) printf("Quantidade de vertices diferentes.\n");
		else if (A != outro.A) printf("Quantidade de arestas diferentes.\n");
		else if (G != outro.G) printf("Quantidade total de grau diferentes.\n");
		\
		else if (Q != outro.Q) printf("Caminhos diferentes.\n");
		else
		{
			printf("Grafos Isomorfos\n");
			return true;
		}

		return false;
	}
	// FunC'C#o para criar um grafo prC)-definido
	static Grafo preset(int i) {
		vector<vector<vector<int>>> V = {
			{
				{0, 1, 1, 0},
				{1, 0, 0, 1},
				{1, 0, 0, 1},
				{0, 1, 1, 0}
			},
			{
				{0, 0, 0, 1},
				{0, 0, 1, 0},
				{0, 1, 0, 0},
				{1, 0, 0, 0}
			},
			{
				{0, 1, 1, 1},
				{1, 0, 1, 1},
				{1, 1, 0, 1},
				{1, 1, 1, 0}
			},
			{
				{0, 0, 1, 1},
				{0, 0, 1, 1},
				{1, 1, 0, 0},
				{1, 1, 0, 0}
			},
			{	//5x5
				{0, 1, 0, 1,0},
				{1, 0, 1, 1,0},
				{0, 1, 0, 0,1},
				{1, 1, 0, 0,1},
				{0, 0, 1, 1,0}
			},
			{	//5x5
				{0, 1, 0, 1,0},
				{1, 0, 1, 0,0},
				{0, 1, 0, 1,0},
				{1, 0, 1, 0,1},
				{0, 0, 0, 1,0}
			},
			{	//5x5
				{0, 1, 1, 0,1},
				{1, 0, 0, 1,1},
				{1, 0, 0, 1,1},
				{0, 1, 1, 0,1},
				{1, 1, 1, 1,0}
			}
		};
		Grafo A(V[i][0].size());
		A.M = V[i];
		A.update();
		return A;
	}
	// FunC'C#o para operaC'C#o entre grafos
	static Grafo grafop(int o, const Grafo& A, const Grafo& B) {
		Grafo C(A.V);
		if (o==2)
		{	//MultiplicaC'C#o
			for (int i = 0; i < A.V; i++)
			{
				for (int j = i; j < B.V; j++)
				{
					for (int k = 0; k < A.V; k++) C.M[j][i]=C.M[i][j] += A.M[i][k] * B.M[k][j];
				}
			}
		}
		else
		{	//AdiC'C#o e remoC'C#o
			for (int i = 0; i < A.V; i++) {
				for (int j = i; j < A.V; j++) C.M[i][j] = C.M[j][i] = A.M[i][j] + (B.M[i][j] * o);
			}
		}
		C.update();
		return C;
	}
	// FunC'C#o para criar um subgrafo
	static Grafo subgrafo(const Grafo& A, const vector<int>& S) {
		int T = S.size();
		Grafo R(T);
		for (int i = 0; i < T; i++) {
			for (int j = i; j < T; j++) R.M[i][j] = R.M[j][i] = A.M[S[i]][S[j]];
		}
		R.update();
		return R;
	}
	vector<int> BFS_com_distancia(int start)
	{
		vector<int> dist(V, -1);
		queue<int> fila;
		dist[start] = 0;

		fila.push(start);

		while (!fila.empty())
		{
			int i = fila.front();
			fila.pop();
			for (int j:L[i])
			{
				if (dist[j] == -1)
				{
					dist[j] = dist[i] + 1;
					fila.push(j);
				}
			}
		}

		return dist;
	}
	bool ConexoBFS()
	{
		if (V == 0) return true; // Grafo vazio C) considerado conexo
		vector<bool> visitado(V, false);
		queue<int> fila;
		int countVisitados = 0;

		fila.push(0); // ComeC'a do vC)rtice 0
		visitado[0] = true;
		countVisitados++;

		while (!fila.empty()) {
			int u = fila.front();
			fila.pop();
			for (int v : L[u]) {
				if (!visitado[v]) {
					visitado[v] = true;
					countVisitados++;
					fila.push(v);
				}
			}
		}
		return (countVisitados == V);
	}
	vector<int> shortpathBFS(int start, int end)
	{
		if (start == end) return {start};
		vector<int> prev(V, -1);
		queue<int> fila;

		fila.push(start);
		prev[start] = start;

		while (!fila.empty())
		{
			int i = fila.front();
			fila.pop();

			for (int j : L[i])
			{
				if (prev[j] == -1)
				{
					prev[j] = i;
					if (j == end)
					{
						vector<int> caminho;
						int atual = end;
						while (atual != start)
						{
							caminho.push_back(atual);
							atual = prev[atual];
						}
						caminho.push_back(start);
						reverse(caminho.begin(), caminho.end());
						return caminho;
					}
					fila.push(j);
				}
			}
		}
		return {}; // Caminho nC#o encontrado
	}
	// 4) Busca em profundidade em grafos dirigidos
	vector<int> DFSdirigido(int start) {
		vector<int> visitados;
		vector<bool> marcados(V, false);
		stack<int> pilha;
		pilha.push(start);
		while (!pilha.empty())
		{
			int vertice = pilha.top();
			pilha.pop();
			if (!marcados[vertice])
			{
				marcados[vertice] = true;
				visitados.push_back(vertice);
				// Empilha na ordem inversa para manter a ordem correta
				for (auto it = L[vertice].rbegin(); it != L[vertice].rend(); ++it)
					pilha.push(*it);
			}
		}
		return visitados;
	}
	bool ciclodirigido()
	{
		vector<bool> visitados(V, false);
		vector<bool> pilha(V, false);

		for (int i = 0; i < V; ++i)
		{
			if (!visitados[i] && dfsciclo(i, visitados, pilha))
			{
				return true;
			}
		}
		return false;
	}
	// 6) Algoritmo de Dijkstra
	vector<int> dijkstra(int start)
	{
		vector<int> dist(V, INT_MAX);
		vector<bool> visitados(V, false);

		dist[start] = 0;

		for (int count = 0; count < V - 1; ++count) {
			int u = -1;
			// Encontra o vC)rtice nC#o visitado com menor distC"ncia
			for (int i = 0; i < V; ++i) {
				if (!visitados[i] && (u == -1 || dist[i] < dist[u])) {
					u = i;
				}
			}

			if (dist[u] == INT_MAX) break;

			visitados[u] = true;

			// Atualiza as distC"ncias dos vizinhos
			for (int v = 0; v < V; ++v) {
				if (M[u][v] > 0 && !visitados[v] && dist[u] + M[u][v] < dist[v])
				{
					dist[v] = dist[u] + M[u][v];
				}
			}
		}

		return dist;
	}
	// 7) Algoritmo de Bellman-Ford
	vector<int> BellmanFord(int origem)
	{
		vector<int> dist(V, INT_MAX);
		dist[origem] = 0;
		// Relaxamento das arestas
		for (int i = 0; i < V - 1; ++i)
		{
			for (int u = 0; u < V; ++u)
			{
				for (int v = 0; v < V; ++v)
				{
					if (M[u][v] != 0 && dist[u] != INT_MAX && dist[u] + M[u][v] < dist[v])	dist[v] = dist[u] + M[u][v];
				}
			}
		}

		// VerificaC'C#o de ciclos negativos
		for (int u = 0; u < V; ++u)
		{
			for (int v = 0; v < V; ++v)
			{
				if (M[u][v] != 0 && dist[u] != INT_MAX && dist[u] + M[u][v] < dist[v])
				{
					cout << "O grafo contC)m ciclo negativo" << endl;
					return {};
				}
			}
		}

		return dist;
	}
	// 8) Algoritmo de Floyd-Warshall
	vector<vector<int>> floydwarshall()
	{
		vector<vector<int>> dist(V, vector<int>(V, INT_MAX));
		// InicializaC'C#o
		for (int i = 0; i < V; ++i) {
			for (int j = 0; j < V; ++j)
			{
				if (i == j)	dist[i][j] = 0;
				else if (M[i][j] != 0)	dist[i][j] = M[i][j];
			}
		}

		// Algoritmo principal
		for (int k = 0; k < V; ++k)
		{
			for (int i = 0; i < V; ++i)
			{
				for (int j = 0; j < V; ++j)
				{
					if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}

		return dist;
	}
	// Funcao para imprimir o grafo
	void print()
	{
		cout << boolalpha;
		string nome = "Grafo_" + string(1, (char)(++c + 64));
		printf("\n%s:\n\nVertices: %d\nArestas: %d\nGrau Total: %d\nTipo de Grafo: %s\n",
		       nome.c_str(), V, A, T, type[y].c_str());

		// Matriz de AdjacC*ncia
		fin += "subgraph "+ to_string(c) + " {\nlabel =" + nome + ";\nstyle = filled;\ncolor = white;\n";
		printf("Matriz de AdjacC*ncia:\n");
		for (i = 0; i < V; i++)
		{
			fin += "  " + to_string(i+cv)+" [shape=circle, style=filled, fillcolor=" + colors[G[i].second] + "];\n";

			setColor(G[i].second+3);
			for (j = 0; j < V; j++)
			{
				printf("%d ", M[i][j]);
			}
			cout << endl;
		}
		//for (i = 0; i < V; i++)for (j = i; j < V; j++) if (M[i][j]) fin += "  " + to_string(i+cv) + " -- " + to_string(j+cv) + ";\n";
		vector<int> caminho = shortpathBFS(0,V-1);

		set<pair<int, int>> arestasCaminho;

		// Identifica as arestas que fazem parte do menor caminho
		for (int i = 1; i < (int)caminho.size(); i++)
		{
			int u = min(caminho[i-1], caminho[i]);
			int v = max(caminho[i-1], caminho[i]);
			arestasCaminho.insert({u, v});
		}

		// Gera todas as arestas do grafo
		for (int i = 0; i < V; i++)
		{
			for (int j = i; j < V; j++)
			{
				if (M[i][j])
				{
					fin += "  " + to_string(i+cv) + " -- " + to_string(j+cv);
					// Verifica se a aresta faz parte do caminho mC-nimo
					if (arestasCaminho.count({i, j}) > 0) fin += " [color=red, penwidth=2.0]";
					fin += ";\n";
				}
			}
		}



		resetColor();
		//Lista de AdjacC*ncia
		printf("Lista de AdjacC*ncia:\n");
		for (i = 0; i < V; i++)
		{
			setColor(G[i].second+3);
			printf("%d ", i);
			for (j = i; j < (int)L[i].size(); j++)printf("%d ",L[i][j]);
			cout << endl;
		}
		//volta ao normal
		resetColor();
		// Matriz de IncidC*ncia
		printf("Matriz de Incidencia:\n");

		for (int i = 0; i < (int)MI.size(); ++i)
		{
			for (int elemento : MI[i])
			{
				printf("%d ", elemento);
			}
			cout << endl;
		}
		printf("Valores e Quantidades:\n");
		for(i=0; i<(int)Q.size(); i++)
		{
			if (Q[i]!=0) printf("%d=%d\n",i,Q[i]);
		}
		cout <<"Euleriano?: "<<EU<< endl;
		printf("Quantidade de cores: %d\n",QC);
		if (QC==2) printf("Grafo bipartido\n");
		cout << "\nCliques Maximais:\n";

		for (const auto& cl : cliques) {
			cout << "{ ";
			for (int v : cl) cout << v << " ";
			cout << "}\n";
		}
		cout << "Menor caminho: ";
		for (int v : caminho) cout << v << " ";
		cout << endl;
		cout <<"Conexo?: "<<ConexoBFS()<< endl;
		fin+="}\n";
		cv+=V;
		fill_n(ostream_iterator<char>(cout), 80, '-');
	}
};
void exportDot()
{
	ofstream out("grafos.dot");
	out << fin << "}\n";
	out.close();
}
void inter()
{
	int e,v;
	printf("0=Ler 1 grafo, 1=Ler 2 grafos\nDigite o proximo comando:");
	cin>>e;
	e=1;
	printf("\nQuantidade de vertices:");
	cin>>v;
	vector<Grafo> VG;
	Grafo A(v);
	A.read(1);
	VG.push_back(A);
	if (e)//isomorfo
	{
		printf("\nComparacao:\n");
		Grafo B(v);
		B.read(1);
		VG.push_back(B);
		A.isomorf(B);
	}
	for(e=0; e<(int)VG.size(); e++)	VG[e].print();
}


int main()
{
	for (int i=0; i<7; i++)
	{
		Grafo G=Grafo::preset(i);
		G.print();
	}
	exportDot();
}
