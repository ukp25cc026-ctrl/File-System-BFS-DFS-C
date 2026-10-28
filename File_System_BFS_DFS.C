
#include <stdio.h>
#include <string.h>

#define MAX 20
#define NAME_LEN 50

char names[MAX][NAME_LEN];
int adj[MAX][MAX];
int visited[MAX];
int n;

// Breadth-First Search
void BFS(int start, char target[]) {
    int queue[MAX];
    int front = 0, rear = 0;
    int found = 0;

    memset(visited, 0, sizeof(visited));

    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];

        printf("%s ", names[current]);

        if (strcmp(names[current], target) == 0)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (adj[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    if (found)
        printf("\nFile found using BFS.\n");
    else
        printf("\nFile not found using BFS.\n");
}

// Depth-First Search
void DFS(int current, char target[], int *found) {
    visited[current] = 1;

    printf("%s ", names[current]);

    if (strcmp(names[current], target) == 0)
        *found = 1;

    for (int i = 0; i < n; i++) {
        if (adj[current][i] && !visited[i]) {
            DFS(i, target, found);
        }
    }
}

int main() {
    int start;

    printf("Enter number of files/directories: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter name of node %d: ", i);
        scanf(" %49[^\n]", names[i]);
    }

    // Initialize adjacency matrix
    memset(adj, 0, sizeof(adj));

    int edges;
    printf("Enter number of connections: ");
    scanf("%d", &edges);

    if (edges < 0 || edges > n * (n - 1) / 2) {
        printf("Invalid number of connections.\n");
        return 1;
    }

    for (int i = 0; i < edges; i++) {
        int u, v;

        printf("Enter connected node numbers (u v): ");
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            printf("Invalid connection.\n");
            return 1;
        }

        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter starting node number: ");
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting node.\n");
        return 1;
    }

    char target[NAME_LEN];
    printf("Enter file/directory name to search: ");
    scanf(" %49[^\n]", target);

    BFS(start, target);

    memset(visited, 0, sizeof(visited));
    int found = 0;

    printf("\nDFS Traversal: ");
    DFS(start, target, &found);

    if (found)
        printf("\nFile found using DFS.\n");
    else
        printf("\nFile not found using DFS.\n");

    return 0;
}
